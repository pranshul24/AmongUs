#include "gridBox.h"
#include <stdlib.h>
#include <iostream>
#include "cell.h"

GridBox::GridBox(float x, float y, float z)
{

    this->position = glm::vec3(0, 0, -11);
    this->rotation = glm::radians(24.0f);
    this->elapsedTime = 0;
    this->rotationAlongX = 0.0;
    this->width = 17;
    this->height = 12;

    float colorRed[] = {0.772f, 0.066f, 0.066f};

    float colorDarkRed[] = {0.478f, 0.031f, 0.219f};

    float colorBlue[] = {0.588f, 0.792f, 0.866f};

    float colorYellow[] = {0.960f, 0.960f, 0.341f};

    float colorBrown[] = {0.760f, 0.529f, 0.133f};

    float colorGrey[] = {0.286f, 0.388f, 0.427f};
    float colorGold[] = {0.866f, 0.698f, 0.192f};
    float colorHeart[] = {0.890f, 0.105f, 0.137f};
    float colorBlack[] = {0.0f, 0.0f, 0.0f};

    int totlength = 0;

    GLfloat grid1[] = {
        -4.0f, 4.2f, 0.0f,
        (-4.0f + width * 0.7f), 4.2f, 0.0f,
        (-4.0f + width * 0.7f), (4.2f - height * 0.7f), 0.0f,

        -4.0f, 4.2f, 0.0f,
        (-4.0f), (4.2f - height * 0.7f), 0.0f,
        (-4.0f + width * 0.7f), (4.2f - height * 0.7f), 0.0f

    };
    // std::cout << "hi";
    int cnt = 18;
    GLfloat vertex_buffer_data[cnt];
    for (int i = 0; i < cnt; i++)
    {
        vertex_buffer_data[i] = grid1[i];
    }
    totlength += cnt;
    int totlengthTillBlack = totlength;
    GLfloat color[totlength];
    for (int i = 0; i < totlength / 3; i++)
    {
        if (i < totlengthTillBlack / 3)
        {
            int k = 3 * i;
            color[k] = 0.6;
            color[k + 1] = 0.6;
            color[k + 2] = 0.5;
        }
    }

    this->object = create3DObject(GL_TRIANGLES, totlength / 3, vertex_buffer_data, color, GL_FILL);
}

void GridBox::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef

    Matrices.model *= (translate);
    // Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glm::mat4 modelMAt = glm::mat4(1.0f);
    glUniformMatrix4fv(Matrices.modelID, 1, GL_FALSE, &Matrices.model[0][0]);
    draw3DObject(this->object);
}
