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
    Food specialFood;

    Difficulty difficulty;

    bool gameOver;
    bool started;

    bool ateFood;
    bool ateSpecialFood;

    int velocity;
    int score;

    QTimer timer;

public:
    //explicit evita que c++ invente construcciones automaticas indeseadas
    //se usa sobre todo en constructores con un solo parametro
    explicit Game(QObject *parent = nullptr);
    //puntero al objeto padre, cuando un objeto tiene un padre en qt, el padre lo destruye
    //cuando el mismo se destruye, evitando errores de memoria

    //Q_INVOKABLE indica que este metodo se llamara desde QML
    Q_INVOKABLE void startGame(int difficulty);
    void resetGame();
    void increaseVelocity();

    void tick();
    void finishTick(int newHead);
    void stop();

    void handleFood(int newHead);
    void handleSpecialFood(int newHead);

    bool lost(int newHead);

    Q_INVOKABLE void setDirection(Direction direction);

    Q_INVOKABLE int getRows() const;
    Q_INVOKABLE int getColumns() const;

    Q_INVOKABLE CellType getCellType(int idx) const;

    Q_INVOKABLE bool isStarted() const;

    //signals es una seccion especial, sirve para indicar cuales son los eventos/cambios
    //que la clase u objeto emite
signals:
    void startedChanged();
    void boardChanged();
    void gameOverChanged();
    void scoreChanged();
    //cuando algo cambie dentro de estos eventos (funciones) la clase avisa para que GUI(QML)
    //pueda reaccionar automaticamente
};
