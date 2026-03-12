import QtQuick
import QtQuick.Window

Window {
    id: root
    width: 600
    height: 600
    visible: true
    color: "black"
    title: "Snake"

    property int cellSize: 25
    property var backend: game

    Grid {
        id: boardGrid
        anchors.centerIn: parent
        rows: root.backend ? root.backend.getRows() : 0
        columns: root.backend ? root.backend.getColumns() : 0
        spacing: 1

        Repeater {
            model: root.backend ? root.backend.getRows() * root.backend.getColumns() : 0

            Rectangle {
                width: root.cellSize
                height: root.cellSize

                color: {
                    if (!root.backend)
                        return "gray"

                    let cell = root.backend.getCellType(index)

                    if (cell === 1)
                        return "lime"
                    if (cell === 0)
                        return "red"
                    return "gray"
                }
            }
        }
    }
}
