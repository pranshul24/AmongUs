#include "main.h"
#ifndef CELL_H
#define CELL_H

class Cell
{

public:
    int row, column;
    int walls[4];
    bool visited;
    enum direction
    {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };
    float posX;
    float posY;

    Cell(int i, int j);

    Cell *checkNeighbors();
    void print();
    void removeWalls(Cell &);

    void setWalls();
    void setVisited(bool);
    bool isVisited();

    int getRow();
    int getColumn();
};

#endif