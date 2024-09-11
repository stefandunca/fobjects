#include "Object.h"

#include "ObjectAbstract.h"

#include "FactoryAbstract.h"
#include "BridgeSingleton.h"

// TODO DEV remove me
template <class T>
class PropertyChangedForObject : public PropertyChangedCallback {
public:
    PropertyChangedForObject(T* object, std::function<void(T*)> notifyFn)
        : object(object)
        , notifyFn(notifyFn)
    {};
    virtual void changed() {
        std::cout << "@dd C+ PropertyChangedForObject::changed()" << std::endl;
        notifyFn(object);
    }
    private:
        T* object;
        std::function<void(T*)> notifyFn;
};

// TODO DEV remove me
static PropertyChangedForObject<ObjectAbstract>* gPcc;


Object::Object(QObject *parent)
    : QObject(parent)
{
    auto factory = BridgeSingleton::factory();

    assert(factory);

    _objectAbstract = factory->createObject();
    if (!gPcc) {
        gPcc = new PropertyChangedForObject<ObjectAbstract>(_objectAbstract, [](ObjectAbstract* o) {
            std::cout << "@dd C+ Property changed for object: " << o->getStringProperty() << std::endl;
        });
    }

    _objectAbstract->registerForStringPropertyChanges(gPcc);
    _objectAbstract->setStringProperty("Test Content");
}

Object::~Object() {
    delete _objectAbstract;
}

QString Object::stringProperty() const {
    return QString::fromStdString(_objectAbstract->getStringProperty());
}

void Object::setStringProperty(const QString &newVal) {
    _objectAbstract->setStringProperty(newVal.toUtf8().constData());
}