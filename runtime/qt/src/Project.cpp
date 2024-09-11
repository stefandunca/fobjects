#include "Project.h"

#include "ProjectAbstract.h"

#include "FactoryAbstract.h"
#include "BridgeSingleton.h"

Project::Project(QObject *parent)
    : QObject(parent)
{
    auto factory = BridgeSingleton::factory();

    assert(factory);

    _projectAbstract = factory->createProject();
}

Project::~Project() {
    delete _projectAbstract;
}

QQmlListProperty<QObject> Project::objects() {
    std::cout << "@dd C+ Project::objects()" << std::endl;
    return QQmlListProperty<QObject>(this, &_objects);
}

void Project::classBegin() {
    std::cout << "@dd C+ Project::classBegin()" << std::endl;
}

void Project::componentComplete() {
    std::cout << "@dd C+ Project::componentComplete()" << std::endl;
    _projectAbstract->componentComplete();
}
