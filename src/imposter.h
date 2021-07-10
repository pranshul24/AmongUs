#include "main.h"

#ifndef IMPOSTER_H
#define IMPOSTER_H

class Imposter
{
public:
    Imposter() {}
    Imposter(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y, float z);

private:
    VAO *object;
};

#endif
