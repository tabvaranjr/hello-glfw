///
/// \brief  Main program file
/// \author Patrick Clément-Bonhomme <patrick.cb@gmail.com>
///

#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

/// Callback for errors logged by GLFW
static void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "Error " << error << ": " << *description << std::endl;
}

/// Callback for keys logged by GLFW
static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);    
    }
}

/// Program entry point
int main(int argc, char* argv[])
{
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        return EXIT_FAILURE;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello GLFW3", nullptr, nullptr);

    if (window == nullptr)
    {
        glfwTerminate();    
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    

    glfwSetKeyCallback(window, glfwKeyCallback);
    
    while (!glfwWindowShouldClose(window))
    {

    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}

