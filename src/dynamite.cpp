#include "dynamite.h"
#include "main.h"

Dynamite::Dynamite(float x, float y, float z)
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
        0.05f, 2.3f, 0.0f,
        0.05f, 1.4f, 0.0f,
        -0.05f, 1.4f, 0.0f,

        0.05f, 2.3f, 0.0f,
        -0.05f, 2.3f, 0.0f,
        -0.05f, 1.4f, 0.0f};

    GLfloat rectangle2[] = {
        0.5f, 0.1f, 0.0f,
        0.5f, -0.1f, 0.0f,
        -0.5f, 0.1f, 0.0f,

        -0.5f, -0.1f, 0.0f,
        0.5f, -0.1f, 0.0f,
        -0.5f, 0.1f, 0.0f

    };

    GLfloat rectangle6[] = {
        0.05f, 2.3f, 0.0f,
        0.05f, 2.6f, 0.0f,
        -0.05f, 2.6f, 0.0f,

        0.05f, 2.3f, 0.0f,
        -0.05f, 2.3f, 0.0f,
        -0.05f, 2.6f, 0.0f};

    GLfloat rectangle4[] = {
        0.5f, 0.7f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.7f, 0.0f,

        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.7f, 0.0f

    };

    GLfloat rectangle5[] = {
        0.5f, -0.5f, 0.0f,
        0.5f, -0.7f, 0.0f,
        -0.5f, -0.5f, 0.0f,

        -0.5f, -0.7f, 0.0f,
        0.5f, -0.7f, 0.0f,
        -0.5f, -0.5f, 0.0f

    };
    GLfloat rectangle3[] = {
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

    for (int i = 0; i < 18; i++)
    {
        vertex_buffer_data[totlength + i] = rectangle3[i];
    }
    totlength += 18;
    int totlengthTillRed = totlength;

    for (int i = 0; i < 18; i++)
    {
        vertex_buffer_data[totlength + i] = rectangle2[i];
    }
    totlength += 18;
    for (int i = 0; i < 18; i++)
    {
        vertex_buffer_data[totlength + i] = rectangle4[i];
    }
    totlength += 18;
    for (int i = 0; i < 18; i++)
    {
        vertex_buffer_data[totlength + i] = rectangle5[i];
    }
    totlength += 18;
    int totlengthTillYellow = totlength;

    for (int i = 0; i < 18; i++)
    {
        vertex_buffer_data[totlength + i] = rectangle6[i];
    }
    totlength += 18;
    int totlengthTillOrange = totlength;
    GLfloat color[totlength];
    for (int i = 0; i < totlength / 3; i++)
    {
        if (i < totlengthTillGrey / 3)
        {
            int k = 3 * i;
            color[k] = colorGrey[0];
            color[k + 1] = colorGrey[1];
            color[k + 2] = colorGrey[2];
        }
        else if (i < totlengthTillRed / 3)
        {
            int k = 3 * i;
            color[k] = colorRed[0];
            color[k + 1] = colorRed[1];
            color[k + 2] = colorRed[2];
        }
        else if (i < totlengthTillYellow / 3)
        {
            int k = 3 * i;
            color[k] = colorYellow[0];
            color[k + 1] = colorYellow[1];
            color[k + 2] = colorYellow[2];
        }
        else
        {
            int k = 3 * i;
            color[k] = colorOrange[0];
            color[k + 1] = colorOrange[1];
            color[k + 2] = colorOrange[2];
        }
    }
    this->object = create3DObject(GL_TRIANGLES, totlength / 3, vertex_buffer_data, color, GL_FILL);
}

void Dynamite::draw(glm::mat4 VP, int flag)
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
    Matrices.model = glm::scale(Matrices.model, glm::vec3(0.18, 0.14, 1.0));

    // Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(Matrices.modelID, 1, GL_FALSE, &Matrices.model[0][0]);
    draw3DObject(this->object);
}

void Dynamite::set_position(float x, float y, float z)
{
    this->position = this->position + glm::vec3(x, y, z);
}

