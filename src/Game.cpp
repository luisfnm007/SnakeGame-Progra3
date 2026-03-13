#include "src/Game.h"
#include <iostream>

Game::Game(QObject *parent): QObject(parent), board(20, 20),  snake(9, 2), started(false),
    food(189), gameOver(false), velocity(150), score(0), difficulty(Difficulty::EASY)
{
    //cuando el timer termine su tiempo, emite timeout y ejecuta tick
    connect(&timer, &QTimer::timeout, this, &Game::tick);
    resetGame();
}

void Game::resetGame()
{
    snake.reset(board.getColumns());
    food.generate(board.getSize(), snake, difficulty);

    gameOver=false;
    score = 0;

    //emitimos las signals para QML
    emit boardChanged();
    emit gameOverChanged();
    emit scoreChanged();
}

void Game::startGame(int difficulty)
{
    switch(difficulty)
    {
    case 1:  this->difficulty = Difficulty::EASY; break;
    case 2:  this->difficulty = Difficulty::MEDIUM; break;
    case 3:  this->difficulty = Difficulty::HARD; break;
    default: this->difficulty = Difficulty::EASY; break;
    }

    velocity = 150;
    started = true;
    resetGame();
    timer.start(velocity);

    emit startedChanged();
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
        started = false;

        timer.stop();
        std::cout <<"==========GAME OVER============" << std::endl;

        emit gameOverChanged();
        emit startedChanged();

        return;
    }

    if(food.getPosition() == newHead)
    {
        score++;
        snake.grow();
        food.generate(board.getSize(), snake, difficulty);

        increaseVelocity();
        std::cout <<"==========COMIO============" << std::endl;

        emit scoreChanged();
    }

    snake.moveHead(newHead);

    emit boardChanged();
}

void Game::increaseVelocity()
{
    if(difficulty != Difficulty::MEDIUM)
        return;

    if(velocity <= 40)
        return;

    velocity -=2;
    timer.setInterval(velocity);
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

bool Game::isStarted() const
{
    return started;
}
