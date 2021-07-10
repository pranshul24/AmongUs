#include "main.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Player() {}
    Player(float x, float y, float z);
    glm::vec3 position;
    float rotation, elapsedTime, rotationAlongX;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y, float z);

private:
    VAO *object;
};

#endif // Player_H
