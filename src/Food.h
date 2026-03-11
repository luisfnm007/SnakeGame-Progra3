#pragma once
#include <src/ENUMS.h>
#include <src/Snake.h>

class Food
{
private:
    FoodType type;

    int position;

public:
    Food(int pos);

    void generate(int boardSize, const Snake& snake, Difficulty difficulty);

    int randomPos(int boardSize, const Snake& snake) const;
    int getPosition() const;

    FoodType getType()const;
};
