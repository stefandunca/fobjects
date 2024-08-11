#include "BridgeSingleton.h"

#include "FactoryAbstract.h"

#include <cassert>

FactoryAbstract *BridgeSingleton::_factory = nullptr;

// Force check of return value
bool
BridgeSingleton::setFactory(FactoryAbstract *factory) {
    if (_factory) {
        return false;
    }
    _factory = factory;
    return true;
}

FactoryAbstract *
BridgeSingleton::factory() {
    assert(_factory);
    return _factory;
}