#include "RuntimeController.h"

RuntimeController::RuntimeController(QObject *parent)
    : QObject(parent)
{
}

void RuntimeController::publishJsonMessage(const QString &json)
{
    auto ptr = Runtime::instance().lock();
    if (!ptr) {
        qCritical() << "Runtime instance is null";
        return;
    }

    ptr->sendData(json.toUtf8().data());
}

void RuntimeController::componentComplete()
{
}
