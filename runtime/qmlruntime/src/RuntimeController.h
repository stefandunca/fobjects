#pragma once

#include "Runtime.h"

#include <QObject>
#include <QQmlParserStatus>
#include <QDebug>
#include <QQmlEngine>

#include <memory>

class RuntimeController : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    QML_ELEMENT
    Q_INTERFACES(QQmlParserStatus)

public:
    RuntimeController(QObject *parent = nullptr);

    // QML interface
    Q_INVOKABLE void publishJsonMessage(const QString &json);

    // QQmlParserStatus interface
    void classBegin() override{};
    void componentComplete() override;

    // TODO
    // signals:
    //    void jsonMessageReceived(const QString &text);

private:
    std::shared_ptr<Runtime> controller;
};
