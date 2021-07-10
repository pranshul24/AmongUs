#include "hudBox.h"
#include "main.h"

HudBox::HudBox(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = glm::radians(24.0f);
    this->elapsedTime = 0;
    this->rotationAlongX = 0.0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float colorRed[] = {0.772f, 0.066f, 0.066f};

    float colorDarkRed[] = {0.478f, 0.031f, 0.219f};

    float colorBlue[] = {0.588f, 0.792f, 0.866f};

    float colorYellow[] = {0.960f, 0.960f, 0.341f};

    float colorBrown[] = {0.760f, 0.529f, 0.133f};
    float colorGrey[] = {0.835f, 0.831f, 0.827f};
    float colorOrange[] = {0.984f, 0.635f, 0.215f};

    float colorGold[] = {0.866f, 0.698f, 0.192f};
    GLfloat ellipse1[900], ellipse2[900];

    int sides = 100;
    float angle = (2 * M_PI) / sides;
    float semiMinorAxis = 1.5;
    float semiMajorAxis = 1.5;

    GLfloat vertex_buffer_data[18 * 6]; //5 rectangles
    int totlength = 0;

    GLfloat rectangle1[] = {
        0.5f, 1.5f, 0.0f,
        0.5f, -1.5f, 0.0f,
        -0.5f, -1.5f, 0.0f,

        0.5f, 1.5f, 0.0f,
        -0.5f, 1.5f, 0.0f,
        -0.5f, -1.5f, 0.0f};

    for (int i = 0; i < 18; i++)
    {
        vertex_buffer_data[totlength + i] = rectangle1[i];
    }
    totlength += 18;
    int totlengthTillGrey = totlength;

    GLfloat color[totlength];
    for (int i = 0; i < totlength / 3; i++)
    {
        if (i < totlengthTillGrey / 3)
        {
            int k = 3 * i;
            color[k] = 0.2;
            color[k + 1] = 0.2;
            color[k + 2] = 0.166;
        }
    }
    this->object = create3DObject(GL_TRIANGLES, totlength / 3, vertex_buffer_data, color, GL_FILL);
}

void HudBox::draw(glm::mat4 VP, int flag)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef

    glm::mat4 rotate2 = glm::rotate(((float)glfwGetTime() - this->elapsedTime), glm::vec3(1, 0, 0));

    if (flag == 1)
    {
        Matrices.model *= (translate * rotate2);
    }
    else
    {
        Matrices.model *= (translate);
    }
    Matrices.model = glm::scale(Matrices.model, glm::vec3(3.9, 1.0, 1.0));

    // Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void HudBox::set_position(float x, float y, float z)
{
    this->position = this->position + glm::vec3(x, y, z);
}
