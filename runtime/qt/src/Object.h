#pragma once

#include "ObjectAbstract.h"

#include <QObject>
#include <QtQml/qqmlregistration.h>

// TODO: namespace

class Object: public QObject {
    Q_OBJECT

    Q_PROPERTY(QString stringProperty READ stringProperty WRITE setStringProperty NOTIFY onStringPropertyChanged)

    QML_ELEMENT

public:
    Object(QObject *parent = nullptr);
    virtual ~Object();

    QString stringProperty() const;
    void setStringProperty(const QString &newVal);

signals:
    void onStringPropertyChanged();

private:
    ObjectAbstract* _objectAbstract;
};
