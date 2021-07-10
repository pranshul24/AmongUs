#include "main.h"

#ifndef COIN_H
#define COIN_H

class Coin
{
public:
    Coin() {}
    Coin(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y, float z);

private:
    VAO *object;
};

#endif // Coin_H
