#include "Runtime.h"

#include "qt/include/BridgeSingleton.h"

#include <functional>

// TODO DEV remove me
#include <iostream>

Runtime::Runtime(const char* jsonArgs)
{
    std::cout << "@dd C+ Runtime::Runtime()" << jsonArgs << std::endl;
    _qmlRuntime = QmlRuntime::initWithJson(jsonArgs, [](const char* data) {
        std::cout << "@dd C+ Runtime::Runtime() data: " << data << std::endl;
    });
}

Runtime::~Runtime()
{
    std::cout << "@dd C+ Runtime::~Runtime()" << std::endl;
}

int Runtime::run(const FactoryAbstract* factory, const char* mainQml)
{
    std::cout << "@dd C+ Runtime::run()" << std::endl;

    auto ok = BridgeSingleton::setFactory(factory);
    if (!ok) {
        std::cout << "@dd C+ Runtime::run() failed to set factory" << std::endl;
        return -1;
    }

    return _qmlRuntime->run(mainQml);
}