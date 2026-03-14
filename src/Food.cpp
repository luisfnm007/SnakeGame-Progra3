#include "src/Food.h"
#include <cstdlib>

Food::Food(int pos) : type(FoodType::NORMAL) , position(pos)
{
}

void Food::generate(int boardSize, const Snake& snake, Difficulty difficulty)
{
    int idx = randomPos(boardSize, snake);

    type = FoodType::NORMAL;

    position = idx;
}

void Food::generateSpecialFruit(int boardSize, const Snake &snake, Difficulty difficulty)
{
    int idx = randomPos(boardSize, snake);

    if(type == FoodType::INCREASEV)
        type = FoodType::LOWERV;
    else
        type = FoodType::INCREASEV;

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

void Food::setPosition(int pos)
{
    this->position = pos;
}

FoodType Food::getType() const
{
    return type;
}

int Food::getPosition() const
{
    return position;
}


