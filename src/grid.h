#ifndef GRID_H
#define GRID_H
#include "main.h"
#include <stack>
#include <vector>
#include <queue>
#include "cell.h"

class Grid
{
private:
    VAO *object;

public:
    Grid() {}
    Grid(float x, float y, float z);
    int height;
    int width;
    std::vector<Cell> cells;
    std::stack<Cell *> backtrace;
    Cell *current;
    void set_position(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    int calculateIndex(int i, int j);
    std::vector<Cell *> getAvailableNeighbors();
    std::vector<Cell *> getAvailableNeighborsForPath(float Ix, float Iy, float Px, float Py);
    Cell *findNextCell();
    Cell *findNextCellForPath(float posX, float posY, float player_posX, float player_posY);
    void draw(glm::mat4 VP);
    int checkInBox(float Ix, float Iy);
    int imposterPosCell(float Ix, float Iy);
    int playerPosCell(float Px, float Py);
    void generateMaze();
    std::vector<int> followDirection(float posX, float posY, float player_posX, float player_posY);
    void getGrid();
    float checkLeftPossible(float posX, float posY);
    float checkRightPossible(float posX, float posY);
    float checkUpPossible(float posX, float posY, int fl);
    float checkDownPossible(float posX, float posY);
};

#endif
