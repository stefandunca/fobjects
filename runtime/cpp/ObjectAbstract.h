#pragma once

#include "helpers.h"

// TODO DEV remove me
#include <iostream>
#include <string>

class ObjectAbstract {
public:
    virtual ~ObjectAbstract() {
        std::cout << "@dd C+ ObjectAbstract::~ObjectAbstract()" << std::endl;
    };
    virtual void setStringProperty(const char*) = 0;
    virtual std::string getStringProperty() = 0;
    // TODO DEV check if I can return a notify function to be used in GO
    virtual void registerForStringPropertyChanges(const PropertyChangedCallback*) = 0;
};
