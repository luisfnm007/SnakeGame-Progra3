#pragma once
#include "src/Board.h"
#include "src/Snake.h"
#include "src/Food.h"
#include "src/ENUMS.h"
#include <QObject>
#include <QTimer>

//QObject es una clase base que sirve para implementar muchisimas ayudas o
//nuevas caracteristicas propias de Qt, por ejemplo: signals
class Game : public QObject
{
    //esto activa las funciones especiales de QObject dentro de la clase
    Q_OBJECT

private:
    Board board;
    Snake snake;
    Food food;

    bool gameOver;

    int velocity;
    int score;

    QTimer timer;

public:
    //explicit evita que c++ invente construcciones automaticas indeseadas
    //se usa sobre todo en constructores con un solo parametro
    explicit Game(QObject *parent = nullptr);
    //puntero al objeto padre, cuando un objeto tiene un padre en qt, el padre lo destruye
    //cuando el mismo se destruye, evitando errores de memoria

    void startGame();
    void resetGame();

    void tick();

    void setDirection(Direction direction);

    int getRows() const;
    int getColumns() const;

    CellType getCellType(int idx) const;

    //signals es una seccion especial, sirve para indicar cuales son los eventos/cambios
    //que la clase u objeto emite
signals:
    void boardChanged();
    void gameOverChanged();
    void scoreChanged();
    //cuando algo cambie dentro de estos eventos (funciones) la clase avisa para que GUI(QML)
    //pueda reaccionar automaticamente
};
