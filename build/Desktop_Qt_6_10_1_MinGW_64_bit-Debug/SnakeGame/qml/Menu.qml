import QtQuick

Rectangle
{
    id: menu
    color: "black"

    Column
    {
        anchors.centerIn: parent
        spacing: 12
        width: 220

        Text {
            text: qsTr("Selecciona un nivel")
            color: "white"
            width: parent.width
        }
    }
}
