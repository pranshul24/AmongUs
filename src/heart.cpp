#include "heart.h"
#include "main.h"

Heart::Heart(float x, float y, float z)
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

    float colorGrey[] = {0.286f, 0.388f, 0.427f};
    float colorGold[] = {0.866f, 0.698f, 0.192f};
    float colorHeart[] = {0.890f, 0.105f, 0.137f};

    GLfloat vertex_buffer_data[9 + 450 * 2]; //5 rectangles
    int totlength = 0;

    GLfloat triangle1[] = {
        1.0f, 0.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f * -2.5 * cos(M_PI / 3), 0.0f};

    int sides = 100;
    float angle = (2 * M_PI) / sides;
    GLfloat ellipse1[450];

    float semiMinorAxis = 0.55;
    float semiMajorAxis = 0.55;

    for (int i = 0; i < sides / 2; i++)
    {
        int k = 9 * i;
        for (int tem = 0; tem < 3; tem++)
        {
            ellipse1[k + tem] = 0.0f;
        }
        ellipse1[k + 3] = semiMajorAxis * cos(i * angle);
        ellipse1[k + 4] = semiMinorAxis * sin(i * angle);
        ellipse1[k + 5] = 0.0f;
        ellipse1[k + 6] = semiMajorAxis * cos((i + 1) * angle);
        ellipse1[k + 7] = semiMinorAxis * sin((i + 1) * angle);
        ellipse1[k + 8] = 0.0f;
        for (int tem = 0; tem < 9; tem++)
        {
            if (tem % 3 == 0)
                ellipse1[k + tem] += -0.45f;
        }
    }
    GLfloat ellipse2[450];

    for (int i = 0; i < sides / 2; i++)
    {
        int k = 9 * i;
        for (int tem = 0; tem < 3; tem++)
        {
            ellipse2[k + tem] = 0.0f;
        }
        ellipse2[k + 3] = semiMajorAxis * cos(i * angle);
        ellipse2[k + 4] = semiMinorAxis * sin(i * angle);
        ellipse2[k + 5] = 0.0f;
        ellipse2[k + 6] = semiMajorAxis * cos((i + 1) * angle);
        ellipse2[k + 7] = semiMinorAxis * sin((i + 1) * angle);
        ellipse2[k + 8] = 0.0f;
        for (int tem = 0; tem < 9; tem++)
        {
            if (tem % 3 == 0)
                ellipse2[k + tem] += 0.45f;
        }
    }

    for (int i = 0; i < 9; i++)
    {
        vertex_buffer_data[totlength + i] = triangle1[i];
    }
    totlength += 9;
    for (int i = 0; i < 450; i++)
    {
        vertex_buffer_data[totlength + i] = ellipse1[i];
    }
    totlength += 450;
    for (int i = 0; i < 450; i++)
    {
        vertex_buffer_data[totlength + i] = ellipse2[i];
    }
    totlength += 450;
    int totlengthTillHeart = totlength;
    GLfloat color[totlength];
    for (int i = 0; i < totlength / 3; i++)
    {
        if (i < totlengthTillHeart / 3)
        {
            int k = 3 * i;
            color[k] = colorHeart[0];
            color[k + 1] = colorHeart[1];
            color[k + 2] = colorHeart[2];
        }
    }
    this->object = create3DObject(GL_TRIANGLES, totlength / 3, vertex_buffer_data, color, GL_FILL);
}

void Heart::draw(glm::mat4 VP, int flag)
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
        // int totlengthTillBlack = totlength;
        Matrices.model *= (translate);
    }
    Matrices.model = glm::scale(Matrices.model, glm::vec3(0.23, 0.23, 1.0));

    // Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(Matrices.modelID, 1, GL_FALSE, &Matrices.model[0][0]);
    draw3DObject(this->object);
}

void Heart::set_position(float x, float y, float z)
{
    this->position = this->position + glm::vec3(x, y, z);
}
