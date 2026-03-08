#pragma once

#include <vector>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake
{
private:

    std::vector<int> body;

    int initialRow;
    int initialColumn;

    Direction direction;
    Direction nextDirection;

    bool growPending;

public:

    Snake();

    int getHead() const;
    int nextHeadPos(int columns) const;
    int getSize() const;

    void init(int columns);
    void moveHead(int newHead);
    void grow();
    void setDirection(Direction newDirection);
    void reset(int columns);

    bool hasSelfCollision(int columns) const;
    bool contains(int idx) const;
    bool is180Turn(Direction newDirection) const;

    const std::vector<int>& getBody() const;

private:
    void removeTail();

};
