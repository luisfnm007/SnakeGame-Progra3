#include "src/Board.h"

Board::Board(int rows, int columns) : rows(rows), columns(columns)
{
}

bool Board::inBounds(int idx) const
{
    int row1 = idx / columns;
    int column1 = idx % columns;

    if(row1 < 0 || row1 >= rows || column1 < 0 || column1 >= columns)
        return false;

    return true;
}

bool Board::inBoundsRowCol(int row, int col) const
{
    if(row < 0 || row >= rows || col < 0 || col >= columns)
        return false;

    return true;
}

int Board::getSize() const
{
    return rows*columns;
}

int Board::getColumns() const
{
    return columns;
}

int Board::getRows() const
{
    return rows;
}
