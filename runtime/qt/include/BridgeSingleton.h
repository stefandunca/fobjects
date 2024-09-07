#pragma once

class FactoryAbstract;

class BridgeSingleton {
public:
    [[nodiscard]] static bool setFactory(const FactoryAbstract *factory);
    [[nodiscard]] static const FactoryAbstract *factory();

private:
    static const FactoryAbstract *_factory;
};