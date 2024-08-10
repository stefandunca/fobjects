
#pragma once

// TODO DEV
#include <iostream>

class PropertyChangedCallback{
public:
    virtual ~PropertyChangedCallback() {
        std::cout << "@dd cpp.PropertyChangedCallback::~PropertyChangedCallback()" << std::endl;
    };
    virtual void changed() = 0;
};
