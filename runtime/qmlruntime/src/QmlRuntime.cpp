#include "QmlRuntime.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QTimer>

#include <QDebug>

#include <nlohmann/json.hpp>

#include <iostream>
#include <string>

using json = nlohmann::json;

namespace fs = std::filesystem;

QmlRuntimeWeak QmlRuntime::globalRuntime;

QmlRuntimePtr QmlRuntime::init(int argc, char** argv, DataReceivedCallback callback)
{
    if (globalRuntime.lock()) {
        throw std::runtime_error("QmlRuntime already initialized");
    }
    auto ptr = std::shared_ptr<QmlRuntime>(new QmlRuntime(argc, argv, callback));
    globalRuntime = ptr;
    return ptr;
}

QmlRuntimePtr QmlRuntime::initWithJson(const char* argsJsonArray, DataReceivedCallback callback)
{
    auto json = json::parse(argsJsonArray);
    auto args = json.get<std::vector<std::string>>();
    int argsCount = args.size();

    std::vector<char*> cstrVecArgs;
    for (auto& str : args) {
        cstrVecArgs.push_back(args[0].data());
    }

    char** argv = cstrVecArgs.data();

    return init(argsCount, argv, callback);
}

QmlRuntimeWeak QmlRuntime::instance() { return globalRuntime; }

QmlRuntime::~QmlRuntime() { std::cout << "@dd cpp.QmlRuntime::~QmlRuntime" << std::endl; }

int QmlRuntime::run(fs::path mainViewQmlComponent)
{
    // Ensure we load QML after the event loop has started
    QTimer::singleShot(0, [this, &mainViewQmlComponent]() {
        engine->load(mainViewQmlComponent.c_str());

        if (engine->rootObjects().isEmpty()) {
            QCoreApplication::exit(-1);
        }
    });
    return app->exec();
}

void QmlRuntime::quit() { app->quit(); }

void QmlRuntime::sendData(const char* data)
{
    if (callback) {
        callback(data);
    }
};

QmlRuntime::QmlRuntime(int argc, char** argv, DataReceivedCallback callback)
    : app(std::make_unique<QGuiApplication>(argc, argv))
    , callback(callback)
{
    engine = new QQmlApplicationEngine(app.get());
}
