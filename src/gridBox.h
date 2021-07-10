#ifndef GRIDBOX_H
#define GRIDBOX_H
#include "main.h"
#include <stack>
#include <vector>
#include <queue>
#include "cell.h"

class GridBox
{
private:
    VAO *object;

public:
    GridBox() {}
    GridBox(float x, float y, float z);
    int height;
    int width;
    std::vector<Cell> cells;
    std::stack<Cell *> backtrace;
    Cell *current;
    void set_position(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP);
};

#endif
