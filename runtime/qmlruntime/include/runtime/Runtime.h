#pragma once

#include <filesystem>
#include <memory>
#include <set>

class QGuiApplication;
class QQmlApplicationEngine;

// TODO: namespace

using RuntimePtr = std::shared_ptr<class Runtime>;
using RuntimeWeak = std::weak_ptr<class Runtime>;
using DataReceivedCallback = std::function<void(const char *)>;

class Runtime
{
public:
    virtual ~Runtime();

    /// callback must be valid for the lifetime of the Runtime instance
    static RuntimePtr init(int argc, char **argv, DataReceivedCallback callback);
    /// @see init
    static RuntimePtr initWithJson(const char *argsJsonArray, DataReceivedCallback callback);
    /// @see init
    static RuntimeWeak instance();

    int run(std::filesystem::path mainViewQmlComponent);
    void quit();

    void sendData(const char *data);

private:
    Runtime(int argc, char **argv, DataReceivedCallback callback);

    static RuntimeWeak globalRuntime;

    std::unique_ptr<QGuiApplication> app;
    QQmlApplicationEngine *engine;

    DataReceivedCallback callback;
};