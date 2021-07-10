#include "main.h"
#ifndef HUDBOX_H
#define HudBox_H

class HudBox
{
public:
    HudBox() {}
    HudBox(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y, float z);

private:
    VAO *object;
};

#endif // HUDBOX_H
