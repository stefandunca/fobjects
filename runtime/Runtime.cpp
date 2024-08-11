#include "Runtime.h"

#include "cpp/ObjectAbstract.h"

#include <functional>

// TODO DEV
#include <iostream>

Runtime::Runtime(const char* jsonArgs)
{
    std::cout << "@dd cpp.Runtime::Runtime()" << jsonArgs << std::endl;
}

Runtime::~Runtime()
{
    std::cout << "@dd cpp.Runtime::~Runtime()" << std::endl;
}

// Identify with an ID the template instance
template <class T>
class PropertyChangedForObject : public PropertyChangedCallback {
public:
    PropertyChangedForObject(T* object, std::function<void(T*)> notifyFn)
        : object(object)
        , notifyFn(notifyFn)
    {};
    virtual void changed() {
        std::cout << "@dd cpp.PropertyChangedForObject::changed()" << std::endl;
        notifyFn(object);
    }
    private:
        T* object;
        std::function<void(T*)> notifyFn;
};

int Runtime::run(const FactoryAbstract* factory)
{
    std::cout << "@dd cpp.Runtime::run()" << std::endl;
    auto obj = factory->createObject();
    PropertyChangedForObject<ObjectAbstract> pcc(obj, [](ObjectAbstract* o) {
        std::cout << "@dd Property changed for object: " << o->getStringProperty() << std::endl;
    });
    obj->registerForStringPropertyChanges(&pcc);
    obj->setStringProperty("Test Content");
    delete obj;
    return 0;
}