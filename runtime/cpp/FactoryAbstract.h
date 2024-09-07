#pragma once

#include "ObjectAbstract.h"

// TODO DEV remove me
#include <iostream>

class FactoryAbstract {
public:
    virtual ~FactoryAbstract() {
        std::cout << "@dd C+ FactoryAbstract::~FactoryAbstract()" << std::endl;
    };
    virtual ObjectAbstract* createObject() const = 0;
};
