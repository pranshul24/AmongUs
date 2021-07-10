#include "main.h"

#ifndef BUTTONTHINGS_H
#define BUTTONTHINGS_H

class ButtonThings
{
public:
    ButtonThings() {}
    ButtonThings(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y, float z);

private:
    VAO *object;
};

#endif // ButtonThings_H
