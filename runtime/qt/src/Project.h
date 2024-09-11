#pragma once

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QQmlParserStatus>
#include <QQmlListProperty>

// TODO: namespace

class ProjectAbstract;

class Project: public QObject, public QQmlParserStatus {
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QQmlListProperty<QObject> objects READ objects)
    Q_CLASSINFO("DefaultProperty", "objects")

    QML_ELEMENT

public:
    Project(QObject *parent = nullptr);
    virtual ~Project();

    QQmlListProperty<QObject> objects();

    void classBegin() override;
    void componentComplete() override;

private:
    ProjectAbstract* _projectAbstract;

    QList<QObject*> _objects;
};
