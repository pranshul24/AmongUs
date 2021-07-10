#include "main.h"

#ifndef BOMB_H
#define BOMB_H

class Bomb
{
public:
    Bomb() {}
    Bomb(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y, float z);

private:
    VAO *object;
};

#endif // Bomb_H
