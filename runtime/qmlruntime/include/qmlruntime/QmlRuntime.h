#pragma once

#include <filesystem>
#include <memory>
#include <set>

class QGuiApplication;
class QQmlApplicationEngine;

// TODO: namespace

using QmlRuntimePtr = std::shared_ptr<class QmlRuntime>;
using QmlRuntimeWeak = std::weak_ptr<class QmlRuntime>;
using DataReceivedCallback = std::function<void(const char *)>;

class QmlRuntime
{
public:
    virtual ~QmlRuntime();

    /// callback must be valid for the lifetime of the QmlRuntime instance
    static QmlRuntimePtr init(int argc, char **argv, DataReceivedCallback callback);
    /// @see init
    static QmlRuntimePtr initWithJson(const char *argsJsonArray, DataReceivedCallback callback);
    /// @see init
    static QmlRuntimeWeak instance();

    int run(std::filesystem::path mainViewQmlComponent);
    void quit();

    void sendData(const char *data);

private:
    QmlRuntime(int argc, char **argv, DataReceivedCallback callback);

    static QmlRuntimeWeak globalRuntime;

    std::unique_ptr<QGuiApplication> app;
    QQmlApplicationEngine *engine;

    DataReceivedCallback callback;
};