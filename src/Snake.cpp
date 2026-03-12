#include "src/Snake.h"
#include <iostream>

Snake::Snake(int initRow, int initColumn) :
    initialRow(initRow), initialColumn(initColumn),
    direction(Direction::RIGHT), growPending(false)
{
}

int Snake::nextHeadPos(int columns) const
{
    int head = getHead();

    int row = head/columns;
    int column = head%columns;

    Direction nxtDir;

    if(pendingDirections.empty())
        nxtDir = direction;
    else
        nxtDir = pendingDirections.front();

    switch(nxtDir)
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

    if(!pendingDirections.empty())
    {
        direction = pendingDirections.front();
        pendingDirections.pop_front();
    }

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
    pendingDirections.clear();

    for(int column = initialColumn; column < initialColumn + 3; column++)
    {
        int index = initialRow * columns + column;
        body.push_back(index);
    }

    direction = Direction::RIGHT;
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
    body.pop_front();
}

void Snake::grow()
{
    growPending = true;
}

void Snake::setDirection(Direction newDirection)
{

    if(pendingDirections.empty())
    {
        if(direction == newDirection)
            return;
    }
    else
    {
        if(pendingDirections.back() == newDirection)
            return;
    }

    if(pendingDirections.size() > 1)
        return;

    if(is180Turn(newDirection))
        return;

   pendingDirections.push_back(newDirection);
}

bool Snake::is180Turn(Direction newDirection) const
{
    Direction currentDir = direction;

    if(!pendingDirections.empty())
        currentDir = pendingDirections.back();

    switch(newDirection)
    {
    case Direction::LEFT:
        if(currentDir == Direction::RIGHT)
            return true;
        break;

    case Direction::RIGHT:
        if(currentDir == Direction::LEFT)
            return true;
        break;

    case Direction::DOWN:
        if(currentDir == Direction::UP)
            return true;
        break;

    case Direction::UP:
        if(currentDir == Direction::DOWN)
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

const std::deque<int>& Snake::getBody() const
{
    return body;
}

