#pragma once

#include "src/ENUMS.h"
#include <vector>
#include <deque>

class Snake
{
private:

    std::vector<int> body;

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

    const std::vector<int>& getBody() const;

private:
    void removeTail();

};
