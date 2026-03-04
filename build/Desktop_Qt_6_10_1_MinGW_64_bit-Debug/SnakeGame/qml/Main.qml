import QtQuick

Window {

    width: 400
    height: 400
    visible: true
    color: "black"
    title: qsTr("Hello World")

    Rectangle {
        width: 50
        height: 50
        anchors.centerIn: parent
        color: "blue"
    }
}
