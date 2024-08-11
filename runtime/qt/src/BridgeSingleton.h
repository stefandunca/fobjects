#pragma once

// TODO DEV
#include <iostream>

class FactoryAbstract;

class BridgeSingleton {
public:
    [[nodiscard]] static bool setFactory(FactoryAbstract *factory);
    [[nodiscard]] static FactoryAbstract *factory();

private:
    static FactoryAbstract *_factory;
};