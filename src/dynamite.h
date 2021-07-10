#include "main.h"
#ifndef DYNAMITE_H
#define DYNAMITE_H

class Dynamite
{
public:
    Dynamite() {}
    Dynamite(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y, float z);

private:
    VAO *object;
};

#endif // Dynamite_H
