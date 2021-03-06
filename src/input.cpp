#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "main.h"

bool cannon_keyboard_input = true;
bool drag_pan = false, old_cki;
double drag_oldx = -1, drag_oldy = -1;

using namespace std;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // Function is called first on GLFW_PRESS.
    if (action == GLFW_PRESS)
    {
        switch (key)
        {
        case GLFW_KEY_ESCAPE:
            quit(window);
            break;
        default:
            break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar(GLFWwindow *window, unsigned int key)
{
    switch (key)
    {
    case 'Q':
    case 'q':
        quit(window);
        break;
    default:
        break;
    }
}
