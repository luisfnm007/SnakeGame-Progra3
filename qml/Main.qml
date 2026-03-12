import QtQuick
import QtQuick.Window

Window {
    id: mainWindow
    width: 600
    height: 600
    visible: true
    color: "black"
    title: "Snake"

    //tamanio de casiila
    property int cellSize: 20
    //contador que nos servira para repintado
    property int boardVersionCounter: 0
    //guardamos todo nuestra logica en backend (para despues utilizar los metodos implementados)
    property var backend: game

    //Connections es un objeto que sirve para escuchar seniales de otro objeto
    Connections {
        //target es el objeto que se escuchara, o sea nuestra logica
        target: mainWindow.backend

        //si el objeto emite alguna senial, entonces ejecuto onBoardChanged
        function onBoardChanged() {
            //incremento boardVersionCounter para indicar actualizacion a QML
            mainWindow.boardVersionCounter++
        }
    }

    Item {
        id: inputManager
        anchors.fill: parent
        //focus:foco indicamos que queremos escuchar teclado
        focus: true

        //importante
        //este bloque se ejecetura cuando Component (objeto QML) se termine de crear
        Component.onCompleted: {
            //una vez se cree, activamos la ventana principal con requestActivate(), o sea que sepa que habra interaccion
            requestActivate()
            //forzamos el foco en inputManager para que escuche teclado (si por alguna razon no se activa)
            inputManager.forceActiveFocus()
        }

        //escuchamos el teclado
        Keys.onPressed: function(event) {
            if (!mainWindow.backend)
                return

            if (event.key === Qt.Key_Up)
                mainWindow.backend.setDirection(0)
            else if (event.key === Qt.Key_Down)
                mainWindow.backend.setDirection(1)
            else if (event.key === Qt.Key_Left)
                mainWindow.backend.setDirection(2)
            else if (event.key === Qt.Key_Right)
                mainWindow.backend.setDirection(3)
        }
    }

    Grid {
        id: boardGrid
        anchors.centerIn: parent
        //extraemos tamanio de grid desde backend(game)
        rows: mainWindow.backend ? mainWindow.backend.getRows() : 0
        columns: mainWindow.backend ? mainWindow.backend.getColumns() : 0
        spacing: 1

        Repeater {
            model: mainWindow.backend ? mainWindow.backend.getRows() * mainWindow.backend.getColumns() : 0

            Rectangle {
                width: mainWindow.backend ? mainWindow.cellSize : 0
                height: mainWindow.backend ? mainWindow.cellSize : 0

                color: {
                    if (!mainWindow.backend)
                        return "gray"

                    //let es un tipo de variable generico, almacenara cualquier dato
                    //parecido a var pero menos confuso y mas moderno
                    //palabra de JS

                    //guardamos en repaint nuestro contador que actualiza, porque?
                    // porque si detecta cambios en esa variable, entonces este bloque de color se volvera a ejecutar (osea se actualizara)
                    let repaint = mainWindow.boardVersionCounter

                    //otro leto para guardar el tipo de casilla
                    let cellType = mainWindow.backend ? mainWindow.backend.getCellType(index) : 0

                    //0 = food
                    if (cellType === 0)
                        return "red"
                    //1 = snake
                    if (cellType === 1)
                        return "lime"
                    return "gray"
                }
            }
        }
    }
}
