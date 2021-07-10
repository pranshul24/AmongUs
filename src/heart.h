#include "main.h"
#ifndef HEART_H
#define HEART_H

class Heart
{
public:
    Heart() {}
    Heart(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y, float z);

private:
    VAO *object;
};

#endif // Heart_H
