import QtQuick
import QtQuick.Controls

import runtime

ApplicationWindow {
    visible: true

    width: 640
    height: 480

    title: "Test Window"

    QtObject {
        id: allDonePayload

        property bool ok: true
    }

    Component.onCompleted: runtimeController.publishJsonMessage(JSON.stringify(allDonePayload))

    QmlRuntimeController {
        id: runtimeController
    }
}
