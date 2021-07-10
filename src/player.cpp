#include "player.h"
#include "main.h"

Player::Player(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    float semiMinorAxis = 1.7;
    float semiMajorAxis = 1.5;
    float colorRed[] = {0.772f, 0.066f, 0.066f};

    float colorDarkRed[] = {0.478f, 0.031f, 0.219f};

    float colorBlue[] = {0.588f, 0.792f, 0.866f};

    float colorYellow[] = {0.960f, 0.960f, 0.341f};

    float colorBrown[] = {0.760f, 0.529f, 0.133f};

    float colorGrey[] = {0.286f, 0.388f, 0.427f};
    GLfloat ellipse1[450];

    int sides = 100;
    float angle = (2 * M_PI) / sides;

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
    }

    GLfloat rectangle1[] = {
        semiMajorAxis, 0.0f, 0.0f,
        -1 * semiMajorAxis, 0.0f, 0.0f,
        semiMajorAxis, -2.0f, 0.0f,

        -1 * semiMajorAxis, -2.0f, 0.0f,
        -1 * semiMajorAxis, 0.0f, 0.0f,
        semiMajorAxis, -2.0f, 0.0f

    };

    // right leg
    GLfloat rectangle2[] = {
        1.0f * semiMajorAxis, -2.0f, 0.0f,
        1.0f * semiMajorAxis, -3.0f, 0.0f,
        0.3f * semiMajorAxis, -3.0f, 0.0f,

        1.0f * semiMajorAxis, -2.0f, 0.0f,
        0.3f * semiMajorAxis, -2.0f, 0.0f,
        0.3f * semiMajorAxis, -3.0f, 0.0f

    };
    // left leg
    GLfloat rectangle3[] = {
        -1.0f * semiMajorAxis, -2.0f, 0.0f,
        -1.0f * semiMajorAxis, -3.0f, 0.0f,
        -0.3f * semiMajorAxis, -3.0f, 0.0f,

        -1.0f * semiMajorAxis, -2.0f, 0.0f,
        -0.3f * semiMajorAxis, -2.0f, 0.0f,
        -0.3f * semiMajorAxis, -3.0f, 0.0f

    };

    GLfloat rectangle4[] = {
        1.0f * semiMajorAxis, 0.5f, 0.0f,
        -0.3f * semiMajorAxis, 0.5f, 0.0f,
        1.0f * semiMajorAxis, -0.7f, 0.0f,

        -0.3f * semiMajorAxis, -0.7f, 0.0f,
        -0.3f * semiMajorAxis, 0.5f, 0.0f,
        1.0f * semiMajorAxis, -0.7f, 0.0f

    };
    float colorRectangle4[18];
    for (int i = 0; i < sizeof(rectangle4) / sizeof(rectangle4[0]); i++)
    {
        int k = i;
        colorRectangle4[k] = colorBlue[k % 3];
        if ((i >= 3 && i < 6) || (i >= 9 && i < 15))
        {
            colorRectangle4[k] = colorGrey[k % 3];
        }
    }

    //bag
    GLfloat rectangle5[] = {
        -1.3f * semiMajorAxis, 0.0f, 0.0f,
        -1.0f * semiMajorAxis, 0.0f, 0.0f,
        -1.3f * semiMajorAxis, -1.7f, 0.0f,

        -1.0f * semiMajorAxis, -1.7f, 0.0f,
        -1.0f * semiMajorAxis, 0.0f, 0.0f,
        -1.3f * semiMajorAxis, -1.7f, 0.0f

    };

    GLfloat ellipse2[450];

    semiMajorAxis = 0.4;
    semiMinorAxis = 0.6;
    for (int i = 0; i < sides / 2; i++)
    {
        int k = 9 * i;
        float transitionX = 1.0f * 1.5f;
        float transitionY = -0.1f;

        for (int tem = 0; tem < 3; tem++)
        {
            ellipse2[k + tem] = 0.0f;
        }
        ellipse2[k + 3] = semiMajorAxis * cos(i * angle - M_PI_2);
        ellipse2[k + 4] = semiMinorAxis * sin(i * angle - M_PI_2);
        ellipse2[k + 5] = 0.0f;
        ellipse2[k + 6] = semiMajorAxis * cos((i + 1) * angle - M_PI_2);
        ellipse2[k + 7] = semiMinorAxis * sin((i + 1) * angle - M_PI_2);
        ellipse2[k + 8] = 0.0f;
        for (int tem = 0; tem < 9; tem++)
        {
            if (tem % 3 == 0)
            {
                ellipse2[k + tem] += transitionX;
            }
            else if (tem % 3 == 1)
            {
                ellipse2[k + tem] += transitionY;
            }
        }
    }

    GLfloat colorEllipse2[450];
    for (int i = 0; i < 450; i++)
    {
        int k = i;
        colorEllipse2[k] = colorBlue[k % 3];
    }

    GLfloat ellipse3[450];

    semiMajorAxis = 0.4;
    semiMinorAxis = 0.6;
    for (int i = 0; i < sides / 2; i++)
    {
        int k = 9 * i;
        float transitionX = 1.5f * -0.3f;
        float transitionY = -0.1f;

        for (int tem = 0; tem < 3; tem++)
        {
            ellipse3[k + tem] = 0.0f;
        }
        ellipse3[k + 3] = semiMajorAxis * cos(i * angle + M_PI_2);
        ellipse3[k + 4] = semiMinorAxis * sin(i * angle + M_PI_2);
        ellipse3[k + 5] = 0.0f;
        ellipse3[k + 6] = semiMajorAxis * cos((i + 1) * angle + M_PI_2);
        ellipse3[k + 7] = semiMinorAxis * sin((i + 1) * angle + M_PI_2);
        ellipse3[k + 8] = 0.0f;
        for (int tem = 0; tem < 9; tem++)
        {
            if (tem % 3 == 0)
            {
                ellipse3[k + tem] += transitionX;
            }
            else if (tem % 3 == 1)
            {
                ellipse3[k + tem] += transitionY;
            }
        }
    }

    GLfloat ellipse4[450];

    semiMajorAxis = 0.15 * 1.5;
    semiMinorAxis = 0.15;
    for (int i = 0; i < sides / 2; i++)
    {
        int k = 9 * i;
        float transitionX = -1.5f * 1.15f;
        float transitionY = -0.5f;

        for (int tem = 0; tem < 3; tem++)
        {
            ellipse4[k + tem] = 0.0f;
        }
        ellipse4[k + 3] = semiMajorAxis * cos(i * angle);
        ellipse4[k + 4] = semiMinorAxis * sin(i * angle);
        ellipse4[k + 5] = 0.0f;
        ellipse4[k + 6] = semiMajorAxis * cos((i + 1) * angle);
        ellipse4[k + 7] = semiMinorAxis * sin((i + 1) * angle);
        ellipse4[k + 8] = 0.0f;
        for (int tem = 0; tem < 9; tem++)
        {
            if (tem % 3 == 0)
            {
                ellipse4[k + tem] += transitionX;
            }
        }
    }

    GLfloat ellipse5[225];

    semiMajorAxis = 0.3 * 1.5;
    semiMinorAxis = 0.2;
    for (int i = 0; i < sides / 4; i++)
    {
        int k = 9 * i;
        float transitionX = -1.5f * 1.0f;
        float transitionY = -1.7f;

        for (int tem = 0; tem < 3; tem++)
        {
            ellipse5[k + tem] = 0.0f;
        }
        ellipse5[k + 3] = semiMajorAxis * cos(i * angle + M_PI);
        ellipse5[k + 4] = semiMinorAxis * sin(i * angle + M_PI);
        ellipse5[k + 5] = 0.0f;
        ellipse5[k + 6] = semiMajorAxis * cos((i + 1) * angle + M_PI);
        ellipse5[k + 7] = semiMinorAxis * sin((i + 1) * angle + M_PI);
        ellipse5[k + 8] = 0.0f;
        for (int tem = 0; tem < 9; tem++)
        {
            if (tem % 3 == 0)
            {
                ellipse5[k + tem] += transitionX;
            }
            else if (tem % 3 == 1)
            {
                ellipse5[k + tem] += transitionY;
            }
        }
    }

    GLfloat vertex_buffer_data[450 + 5 * 2 * 9 + 450 + 450 + 450 + 225]; //5 rectangles
    for (int i = 0; i < 450; i++)
    {
        vertex_buffer_data[i] = ellipse1[i];
    }
    GLfloat colorEllipse1[450];
    for (int i = 0; i < 450; i++)
    {
        int k = i;
        colorEllipse1[k] = colorYellow[k % 3];
    }

    int totlength = 450;
    for (int i = 0; i < sizeof(rectangle1) / sizeof(rectangle1[0]); i++)
    {
        vertex_buffer_data[totlength + i] = rectangle1[i];
    }
    totlength += sizeof(rectangle1) / sizeof(rectangle1[0]);
    GLfloat colorRectangle1[18];
    for (int i = 0; i < sizeof(rectangle1) / sizeof(rectangle1[0]); i++)
    {
        int k = i;
        colorRectangle1[k] = colorYellow[k % 3];
        if (i >= 9 && i < 12)
        {
            colorRectangle1[k] = colorBrown[k % 3];
        }
    }

    int totlengthTillYellow = totlength;
    // bag and legs
    for (int i = 0; i < 450; i++)
    {
        vertex_buffer_data[totlength + i] = ellipse4[i];
    }
    totlength += 450;
    for (int i = 0; i < 225; i++)
    {
        vertex_buffer_data[totlength + i] = ellipse5[i];
    }
    totlength += 225;
    for (int i = 0; i < sizeof(rectangle2) / sizeof(rectangle2[0]); i++)
    {
        vertex_buffer_data[totlength + i] = rectangle2[i];
    }
    totlength += sizeof(rectangle2) / sizeof(rectangle2[0]);
    for (int i = 0; i < sizeof(rectangle3) / sizeof(rectangle3[0]); i++)
    {
        vertex_buffer_data[totlength + i] = rectangle3[i];
    }
    totlength += sizeof(rectangle3) / sizeof(rectangle3[0]);

    for (int i = 0; i < sizeof(rectangle5) / sizeof(rectangle5[0]); i++)
    {
        vertex_buffer_data[totlength + i] = rectangle5[i];
    }
    totlength += sizeof(rectangle5) / sizeof(rectangle5[0]);
    int totlengthTillBrownish = totlength;
    //helmet
    for (int i = 0; i < sizeof(rectangle4) / sizeof(rectangle4[0]); i++)
    {
        vertex_buffer_data[totlength + i] = rectangle4[i];
    }
    totlength += sizeof(rectangle4) / sizeof(rectangle4[0]);
    for (int i = 0; i < 450; i++)
    {
        vertex_buffer_data[totlength + i] = ellipse2[i];
    }
    totlength += 450;
    for (int i = 0; i < 450; i++)
    {
        vertex_buffer_data[totlength + i] = ellipse3[i];
    }
    totlength += 450;
    int totlengthTillGreyish = totlength;
    GLfloat color[totlength];
    for (int i = 0; i < totlength / 3; i++)
    {
        if (i < totlengthTillYellow / 3)
        {
            int k = 3 * i;
            color[k] = 0.960f;
            color[k + 1] = 0.960f;
            color[k + 2] = 0.341f;
        }
        else if (i < totlengthTillBrownish / 3)
        {
            int k = 3 * i;
            color[k] = 0.760f;
            color[k + 1] = 0.529f;
            color[k + 2] = 0.133f;
        }
        else
        {
            int k = 3 * i;
            color[k] = 0.286f;
            color[k + 1] = 0.388f;
            color[k + 2] = 0.427f;
        }
    }
    for (int i = 450; i < 450 + 18; i++)
    {
        color[i] = colorRectangle1[i - 450];
    }
    int indblue = totlength - (sizeof(rectangle4) / sizeof(rectangle4[0]) + 900);
    for (int i = indblue; i < indblue + 18; i++)
    {
        color[i] = colorRectangle4[i - indblue];
    }
    indblue += 18;
    for (int i = indblue; i < indblue + 450; i++)
    {
        color[i] = colorEllipse2[i - indblue];
    }
    this->object = create3DObject(GL_TRIANGLES, totlength / 3, vertex_buffer_data, color, GL_FILL);
}

void Player::draw(glm::mat4 VP, int flag)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate(this->rotation, glm::vec3(0, 1, 0));
    glm::mat4 rotate3 = glm::rotate(this->rotationAlongX, glm::vec3(1, 0, 0));

    glm::mat4 rotate2 = glm::rotate(((float)glfwGetTime() - this->elapsedTime), glm::vec3(1, 0, 0));
    if (flag == 1)
    {
        Matrices.model *= (translate * rotate2 * rotate3 * rotate);
    }
    else
    {
        Matrices.model *= (translate * rotate3 * rotate);
    }
    Matrices.model = glm::scale(Matrices.model, glm::vec3(0.128, 0.145, 1.0));

    // Matrices.model *= translate;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(Matrices.modelID, 1, GL_FALSE, &Matrices.model[0][0]);

    draw3DObject(this->object);
}

void Player::set_position(float x, float y, float z)
{
    this->position = this->position + glm::vec3(x, y, z);
}

