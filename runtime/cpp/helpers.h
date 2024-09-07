
#pragma once

// TODO DEV remove me
#include <iostream>

class PropertyChangedCallback{
public:
    virtual ~PropertyChangedCallback() {
        std::cout << "@dd C+ PropertyChangedCallback::~PropertyChangedCallback()" << std::endl;
    };
    virtual void changed() = 0;
};
