#pragma once

#include "ObjectAbstract.h"
#include "ProjectAbstract.h"

// TODO DEV remove me
#include <iostream>

class FactoryAbstract {
public:
    virtual ~FactoryAbstract() {
        std::cout << "@dd C+ FactoryAbstract::~FactoryAbstract()" << std::endl;
    };
    virtual ObjectAbstract* createObject() const = 0;
    virtual ProjectAbstract* createProject() const = 0;
};
