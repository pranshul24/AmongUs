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

using namespace std;

void error_callback(int error, const char *description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void quit(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow(GLFWwindow *window, int width, int height)
{
    int fbwidth = width, fbheight = height;
    /* With Retina display on Mac OS X, GLFW's FramebufferSize
       is different from WindowSize */
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

    // GLfloat fov = 90.0f;

    // sets the viewport of openGL renderer
    glViewport(0, 0, (GLsizei)fbwidth, (GLsizei)fbheight);

    // Creates perspective projection matrix
    reset_screen(fbwidth, fbheight);
}
