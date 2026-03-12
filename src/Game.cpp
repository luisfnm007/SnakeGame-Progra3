#include "src/Game.h"
#include <iostream>

Game::Game(QObject *parent): QObject(parent), board(20, 20),
    snake(9, 2), food(189), gameOver(false), velocity(150), score(0)
{
    //cuando el timer termine su tiempo, emite timeout y ejecuta tick
    connect(&timer, &QTimer::timeout, this, &Game::tick);
    resetGame();
}

void Game::resetGame()
{
    snake.reset(board.getColumns());
    food.generate(board.getSize(), snake, Difficulty::EASY);

    gameOver=false;
    score = 0;

    //emitimos las signals para QML
    emit boardChanged();
    emit gameOverChanged();
    emit scoreChanged();
}

void Game::startGame()
{
    resetGame();
    timer.start(velocity);
}

void Game::tick()
{
    if(gameOver)
        return;

    int newHead = snake.nextHeadPos(board.getColumns());

    if(snake.hasSelfCollision(newHead) ||
        !board.inBounds(newHead) ||
        board.isHorizontalJump(snake.getHead(), newHead))
    {
        gameOver = true;
        timer.stop();
        emit gameOverChanged();
        std::cout <<"==========GAME OVER============" << std::endl;
        return;
    }

    if(food.getPosition() == newHead)
    {
        score++;
        snake.grow();
        food.generate(board.getSize(), snake, Difficulty::EASY);
        std::cout <<"==========COMIO============" << std::endl;
        emit scoreChanged();
    }

    snake.moveHead(newHead);

    emit boardChanged();
}

void Game::setDirection(Direction direction)
{
    snake.setDirection(direction);
}

int Game::getRows() const
{
    return board.getRows();
}

int Game::getColumns() const
{
    return board.getColumns();
}

CellType Game::getCellType(int idx) const
{
    if(snake.contains(idx))
        return CellType::SNAKE;

    if(food.getPosition() == idx)
        return CellType::FOOD;

    return CellType::EMPTY;
}
