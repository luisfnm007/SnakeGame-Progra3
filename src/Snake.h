#pragma once

#include "src/ENUMS.h"
#include <deque>

class Snake
{
private:

    std::deque<int> body;

    int initialRow;
    int initialColumn;

    Direction direction;
    std::deque<Direction> pendingDirections;

    bool growPending;

public:

    Snake(int initRow, int initColumn);

    int getHead() const;
    int nextHeadPos(int columns) const;
    int getSize() const;

    void moveHead(int newHead);
    void grow();
    void setDirection(Direction newDirection);
    void reset(int columns);

    bool hasSelfCollision(int nextHead) const;
    bool contains(int idx) const;
    bool is180Turn(Direction newDirection) const;

    const std::deque<int>& getBody() const;

private:
    void removeTail();

};
