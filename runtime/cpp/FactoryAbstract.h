#pragma once

#include "ObjectAbstract.h"

// TODO DEV
#include <iostream>

class FactoryAbstract {
public:
    virtual ~FactoryAbstract() {
        std::cout << "@dd cpp.FactoryAbstract::~FactoryAbstract()" << std::endl;
    };
    virtual ObjectAbstract* createObject() const = 0;
};
