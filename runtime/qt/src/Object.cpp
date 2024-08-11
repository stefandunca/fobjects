#include "Object.h"

#include "FactoryAbstract.h"

#include "BridgeSingleton.h"

Object::Object(QObject *parent)
    : QObject(parent)
{
    auto factory = BridgeSingleton::factory();

    assert(factory);

    _objectAbstract = factory->createObject();
}

Object::~Object() {}

QString Object::stringProperty() const {
    return QString::fromStdString(_objectAbstract->getStringProperty());
}

void Object::setStringProperty(const QString &newVal) {
    _objectAbstract->setStringProperty(newVal.toUtf8().constData());
}