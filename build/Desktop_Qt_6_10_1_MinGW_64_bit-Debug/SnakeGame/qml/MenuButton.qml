import QtQuick

Rectangle
{
    id: btn
    color: "lime"

    width: 220
    height: 50

    property string textBtn

    signal click

    Text
    {
        id: title
        anchors.centerIn: parent
        text: textBtn
        color: "black"
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked: click()
    }
}
