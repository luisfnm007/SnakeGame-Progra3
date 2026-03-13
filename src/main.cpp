#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "src/Game.h"
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(0));
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Game game;
    engine.rootContext()->setContextProperty("game", &game);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("SnakeGame", "Main");

    //game.startGame(2);

    return app.exec();
}
