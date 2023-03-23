import QtQuick 2.0
import QtQuick.Window 2.0

Window {
    width: 400
    height: 400
    visible: true
    title: "Hello World"

    Text {
        text: "Hello World"
        color: "red"
        font.pointSize: 24
        anchors.centerIn: parent
    }

    Rectangle {
        color: "black"
        anchors.fill: parent
        z: -1
    }
}
