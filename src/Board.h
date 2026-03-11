#pragma once

class Board
{
private:
    int rows;
    int columns;

public:
    Board(int rows, int columns);

    bool inBounds(int idx) const;
    bool inBoundsRowCol(int row, int col) const;

    int getSize() const;

    int getRows() const;
    int getColumns() const;
};
