#include "Runtime.h"

#include "cpp/ObjectAbstract.h"

#include <iostream>

Runtime::Runtime(const char* jsonArgs)
{
    std::cout << "@dd cpp.Runtime::Runtime()" << jsonArgs << std::endl;
}

// Identify with an ID the template instance
template <class T>
class PropertyChangedForObject : public PropertyChangedCallback {
public:
    PropertyChangedForObject(T* object) : object(object) {};
    virtual void changed() {
        std::cout << "@dd cpp.PropertyChangedForObject::changed()" << std::endl;
    }
    private:
        T* object;
};

int Runtime::run(const FactoryAbstract* factory)
{
    std::cout << "@dd cpp.Runtime::run()" << std::endl;
    auto obj = factory->createObject();
    PropertyChangedForObject<ObjectAbstract> pcc(obj);
    obj->registerForStringPropertyChanges(&pcc);
    obj->setStringProperty("Test Content");
    delete obj;
    return 0;
}

Runtime::~Runtime()
{
    std::cout << "@dd cpp.Runtime::~Runtime()" << std::endl;
}