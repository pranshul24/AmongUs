#include "cell.h"
#include <stdlib.h>
#include <iostream>

Cell::Cell(int row, int column)
{
    this->row = row;
    this->column = column;
    this->visited = false;
    setWalls();
}

void Cell::setWalls()
{
    for (int i = 0; i < 4; i++)
        this->walls[i] = 1;
}

void Cell::setVisited(bool b)
{
    this->visited = b;
}
bool Cell::isVisited() 
{ 
    return this->visited; 
}

int Cell::getRow() { return this->row; }
int Cell::getColumn() { return this->column; }

void Cell::removeWalls(Cell &next)
{
    int x = column - next.column;
    int y = row - next.row;

    if (x == 1)
    {
        walls[LEFT] = 0;
        next.walls[RIGHT] = 0;
    }
    else if (x == -1)
    {
        walls[RIGHT] = 0;
        next.walls[LEFT] = 0;
    }
    else if (y == 1)
    {
        walls[TOP] = 0;
        next.walls[BOTTOM] = 0;
    }
    else if (y == -1)
    {
        walls[BOTTOM] = 0;
        next.walls[TOP] = 0;
    }
}

void Cell::print()
{
    std::cout << "row : " << row << " | ";
    std::cout << "column : " << column << std::endl;
}