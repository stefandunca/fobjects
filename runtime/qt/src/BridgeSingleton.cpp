#include "BridgeSingleton.h"

#include "FactoryAbstract.h"

#include <cassert>

const FactoryAbstract *BridgeSingleton::_factory = nullptr;

// Force check of return value
bool
BridgeSingleton::setFactory(const FactoryAbstract *factory) {
    if (_factory) {
        return false;
    }
    _factory = factory;
    return true;
}

const FactoryAbstract *
BridgeSingleton::factory() {
    assert(_factory);
    return _factory;
}