#pragma once

#include "QmlRuntime.h"

#include <QObject>
#include <QQmlParserStatus>
#include <QDebug>
#include <QQmlEngine>

#include <memory>

class QmlRuntimeController : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    QML_ELEMENT
    Q_INTERFACES(QQmlParserStatus)

public:
    QmlRuntimeController(QObject *parent = nullptr);

    // QML interface
    Q_INVOKABLE void publishJsonMessage(const QString &json);

    // QQmlParserStatus interface
    void classBegin() override{};
    void componentComplete() override;

    // TODO fixme
    // signals:
    //    void jsonMessageReceived(const QString &text);

private:
    std::shared_ptr<QmlRuntime> controller;
};
