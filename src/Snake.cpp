#include "src/Snake.h"

Snake::Snake(int initRow, int initColumn) : initialRow(initRow),
    initialColumn(initColumn), direction(Direction::RIGHT),
    nextDirection(Direction::RIGHT), growPending(false)
{
}

int Snake::nextHeadPos(int columns) const
{
    int head = getHead();

    int row = head/columns;
    int column = head%columns;

    switch(nextDirection)
    {
    case Direction::UP:
        row--;
        break;

    case Direction::DOWN:
        row++;
        break;

    case Direction::RIGHT:
        column++;
        break;

    case Direction::LEFT:
        column--;
        break;
    }

    return row * columns + column;
}

void Snake::moveHead(int newHead)
{
    body.push_back(newHead);
    direction = nextDirection;

    if(!growPending)
    {
        removeTail();
        return;
    }
    growPending = false;
}

void Snake::reset(int columns)
{
    body.clear();

    for(int column = initialColumn; column < initialColumn + 3; column++)
    {
        int index = initialRow * columns + column;
        body.push_back(index);
    }

    direction = Direction::RIGHT;
    nextDirection = direction;
    growPending = false;
}

bool Snake::hasSelfCollision(int newHead) const
{
    if(growPending)
    {
        for(const int& pos : body)
        {
            if(newHead == pos)
                return true;
        }
        return false;
    }

    for(const int& pos : body)
    {
        if(pos == body.front())
            continue;

        if(newHead == pos)
            return true;
    }

    return false;
}

bool Snake::contains(int idx) const
{
    for(const int& pos : body)
    {
        if(pos == idx)
            return true;
    }
    return false;
}

void Snake::removeTail()
{
    body.erase(body.begin());
}

void Snake::grow()
{
    growPending = true;
}

void Snake::setDirection(Direction newDirection)
{
    if(is180Turn(newDirection))
        return;

    nextDirection = newDirection;
}

bool Snake::is180Turn(Direction newDirection) const
{
    switch(newDirection)
    {
    case Direction::LEFT:
        if(direction == Direction::RIGHT)
            return true;
        break;

    case Direction::RIGHT:
        if(direction == Direction::LEFT)
            return true;
        break;

    case Direction::DOWN:
        if(direction == Direction::UP)
            return true;
        break;

    case Direction::UP:
        if(direction == Direction::DOWN)
            return true;
        break;
    }
    return false;
}

int Snake::getHead() const
{
    return body.back();
}

int Snake::getSize() const
{
    return (int)body.size();
}

const std::vector<int>& Snake::getBody() const
{
    return body;
}
