#pragma once

#include "helpers.h"

#include <iostream>

class ObjectAbstract {
public:
    virtual ~ObjectAbstract() {
        std::cout << "@dd cpp.ObjectAbstract::~ObjectAbstract()" << std::endl;
    };
    virtual void setStringProperty(const char*) = 0;
    virtual const std::string getStringProperty() = 0;
    virtual void registerForStringPropertyChanges(const PropertyChangedCallback*) = 0;
};
