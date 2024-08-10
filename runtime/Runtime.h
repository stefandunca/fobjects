#pragma once

#include "cpp/FactoryAbstract.h"

// TODO DEV
#include <iostream>

class Runtime {
public:
    explicit Runtime(const char* jsonArgs);

    virtual ~Runtime();

    int run(const FactoryAbstract* factory);
};
