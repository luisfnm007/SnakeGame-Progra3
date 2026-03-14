#include "src/Game.h"
#include <iostream>

Game::Game(QObject *parent): QObject(parent), board(20, 20),  snake(9, 2), started(false), ateFood(false),
    ateSpecialFood(false),food(0), specialFood(-1), gameOver(false), velocity(150), score(0), difficulty(Difficulty::EASY)
{
    //cuando el timer termine su tiempo, emite timeout y ejecuta tick
    connect(&timer, &QTimer::timeout, this, &Game::tick);
    resetGame();
}

void Game::resetGame()
{
    snake.reset(board.getColumns());
    food.generate(board.getSize(), snake, difficulty);

    specialFood.setPosition(-1);

    if(difficulty == Difficulty::HARD)
        specialFood.generateSpecialFruit(board.getSize(), snake, difficulty);

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

    if(lost(newHead))
    {
        stop();
        return;
    }

    handleFood(newHead);

    handleSpecialFood(newHead);

    finishTick(newHead);

    emit boardChanged();
}

void Game::finishTick(int newHead)
{
    snake.moveHead(newHead);

    if(difficulty == Difficulty::HARD && ateSpecialFood)
        specialFood.generateSpecialFruit(board.getSize(), snake, difficulty);

    if(ateFood)
        food.generate(board.getSize(), snake, difficulty);

    ateFood = false;
    ateSpecialFood = false;
}

void Game::handleFood(int newHead)
{
    if(food.getPosition() == newHead)
    {
        score++;
        snake.grow();

        if(difficulty ==  Difficulty::MEDIUM)
            increaseVelocity();

        std::cout <<"==========COMIO============" << std::endl;
        std::cout <<"\n" << score << "\n";

        ateFood = true;

        emit scoreChanged();
    }
}

void Game::handleSpecialFood(int newHead)
{
    if(specialFood.getPosition() == newHead)
    {
        switch(difficulty)
        {
        case Difficulty::EASY: return;
        case Difficulty::MEDIUM: return;
        case Difficulty::HARD:
            if(specialFood.getType() == FoodType::INCREASEV)
                velocity = 80;
            else
                velocity = 220;

            ateSpecialFood = true;
            timer.setInterval(velocity);
        }
    }
}

bool Game::lost(int newHead)
{
    if(snake.hasSelfCollision(newHead) ||
        !board.inBounds(newHead) ||
        board.isHorizontalJump(snake.getHead(), newHead))
    {
        return true;
    }
    return false;
}

void Game::stop()
{
    gameOver = true;
    started = false;

    timer.stop();
    std::cout <<"==========GAME OVER============" << std::endl;

    emit gameOverChanged();
    emit startedChanged();
}

void Game::increaseVelocity()
{
    if(velocity <= 40)
        return;

    velocity -=3;
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

    if(specialFood.getPosition() == idx)
        return CellType::SPECIAL_FOOD;

    return CellType::EMPTY;
}

bool Game::isStarted() const
{
    return started;
}
