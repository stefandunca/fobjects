#pragma once

#include "helpers.h"

// TODO DEV remove me
#include <iostream>
#include <string>

class ProjectAbstract {
public:
    virtual ~ProjectAbstract() {
        std::cout << "@dd C+ ProjectAbstract::~ProjectAbstract()" << std::endl;
    };

    virtual void componentComplete() = 0;
};
