#include "QmlRuntimeController.h"

QmlRuntimeController::QmlRuntimeController(QObject *parent)
    : QObject(parent)
{
}

void QmlRuntimeController::publishJsonMessage(const QString &json)
{
    auto ptr = QmlRuntime::instance().lock();
    if (!ptr) {
        qCritical() << "QmlRuntime instance is null";
        return;
    }

    ptr->sendData(json.toUtf8().data());
}

void QmlRuntimeController::componentComplete()
{
}
