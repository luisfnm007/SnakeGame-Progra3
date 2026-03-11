#include "src/Food.h"
#include <cstdlib>

Food::Food(int pos) : type(FoodType::NORMAL) , position(pos)
{
}

void Food::generate(int boardSize, const Snake& snake, Difficulty difficulty)
{
    int idx = randomPos(boardSize, snake);

    switch(difficulty)
    {
    case Difficulty::HARD:
        if(idx % 2 == 0)
            type = FoodType::LOWERV;
        else
            type = FoodType::INCREASEV;

        break;

    default:
        type = FoodType::NORMAL;
    }

    position = idx;
}

int Food::randomPos(int boardSize, const Snake& snake) const
{
    int idx = rand() % boardSize;

    while(snake.contains(idx) || idx == position)
    {
        idx = rand() % boardSize;
    }

    return idx;
}

int Food::getPosition() const
{
    return position;
}
