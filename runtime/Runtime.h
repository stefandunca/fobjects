#pragma once

#include "qmlruntime/include/qmlruntime/QmlRuntime.h"

#include "cpp/FactoryAbstract.h"

// TODO DEV remove me
#include <iostream>

class Runtime {
public:
    explicit Runtime(const char* jsonArgs);

    virtual ~Runtime();

    int run(const FactoryAbstract* factory, const char* mainQml);
    
    bool listProperties(void* bridgeObject) const;

private:
    QmlRuntimePtr _qmlRuntime;
};
