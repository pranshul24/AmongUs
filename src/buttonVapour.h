#include "main.h"

#ifndef BUTTONVAPOUR_H
#define BUTTONVAPOUR_H

class ButtonVapour
{
public:
    ButtonVapour() {}
    ButtonVapour(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y, float z);

private:
    VAO *object;
};

#endif // ButtonVapour_H
