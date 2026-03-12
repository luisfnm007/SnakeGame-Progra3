#pragma once

enum class CellType
{
    FOOD,
    SNAKE,
    OBSTACLE,
    EMPTY
};

enum class Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum class Difficulty
{
    EASY,
    MEDIUM,
    HARD
};

enum class FoodType
{
    NORMAL,
    LOWERV,
    INCREASEV
};
