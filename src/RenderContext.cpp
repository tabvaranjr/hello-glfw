#include "RenderContext.h"

#include <iostream>
#include <cstdlib>
#include <boost/format.hpp>

/// Callback for errors logged by GLFW
static void glfwErrorCallback(int error, const char* description)
{
    std::cerr << boost::format("Error %1%: %2%") % error % description << std::endl;
}


/// Callback for keys logged by GLFW
static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


/// Callback for mouse press/releases logged by GLFW
static void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    std::string buttonStr;
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        buttonStr = "Left button";
        break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
        buttonStr = "Middle button";
        break;

    case GLFW_MOUSE_BUTTON_RIGHT:
        buttonStr = "Right button";
        break;

    default:
        buttonStr = (boost::format("Button %1%") % button).str();
        break;
    }

    std::string actionStr;
    switch (action)
    {
    case GLFW_PRESS:
        actionStr = "pressed";
        break;

    case GLFW_RELEASE:
        actionStr = "released";
        break;
    }

    std::string modsStr;
    if (mods != 0)
    {
        if (mods & GLFW_MOD_SHIFT)
        {
            modsStr += "SHIFT";
        }

        if (mods & GLFW_MOD_CONTROL)
        {
            if (!modsStr.empty())
            {
                modsStr += "+";
            }

            modsStr += "CTRL";
        }

        if (mods & GLFW_MOD_ALT)
        {
            if (!modsStr.empty())
            {
                modsStr += "+";
            }

            modsStr += "ALT";
        }

        if (mods & GLFW_MOD_SUPER)
        {
            if (!modsStr.empty())
            {
                modsStr += "+";
            }

            modsStr += "SUPER";
        }
    }
    else
    {
        modsStr = "None";
    }

    std::cout << boost::format("%1% %2% with %3% modifier keys") % buttonStr % actionStr % modsStr << std::endl;
}


/// Callback when the window is minimized/iconified
static void glfwWindowIconifyCallback(GLFWwindow* window, int iconified)
{
    if (iconified)
    {
        std::cout << "Window was minimized." << std::endl;
    }
    else
    {
        std::cout << "Window was restored." << std::endl;
    }
}


/// Callback when the size of the window is changed
static void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    std::cout << boost::format("Window size changed to %1% x %2%") % width % height << std::endl;

    glViewport(0, 0, width, height);
}


/// Callback when an debug message is sent by OpenGL (with KHR_debug extension/OpenGL 4.3)
static void glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, void* userParam)
{
    std::cerr << boost::format("Error %1%: %2%") % id % message << std::endl;
}

RenderContext::RenderContext(const ApplicationParameters& cliParameters) :
    window(nullptr),
    parameters(cliParameters)
{
    makeContext();
}

RenderContext::~RenderContext()
{
    destroyContext();
}


void RenderContext::swapBuffers()
{
    glfwSwapBuffers(window);

}

void RenderContext::poolEvents()
{
    glfwPollEvents();
}

bool RenderContext::isCloseFlagged()
{
    return glfwWindowShouldClose(window);
}

void RenderContext::makeContext()
{
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return;
    }

    if (parameters.IsDebugModeActive)
    {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    window = nullptr;
    if (parameters.IsFullScreen)
    {
        auto monitor = glfwGetPrimaryMonitor();
        auto mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        window = glfwCreateWindow(mode->width, mode->height, "Hello GLFW3", monitor, nullptr);
    }
    else
    {
        window = glfwCreateWindow(800, 800, "Hello GLFW3", nullptr, nullptr);
    }

    if (window == nullptr)
    {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Reminder: GLEW requires a valid OpenGL context before initialization.
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << boost::format("Failed to initialize GLEW: %1%") % glewGetErrorString(err) << std::endl;

        glfwTerminate();
        return;
    }

    if (parameters.IsDebugModeActive)
    {
        if (GLEW_VERSION_4_3 || GLEW_KHR_debug)
        {
            glDebugMessageCallback(glDebugCallback, nullptr);
            glEnable(GL_DEBUG_OUTPUT);
        }
        else
        {
            std::cerr << "Missing KHR_debug extension support for debug output." << std::endl;
        }
    }

    std::cout << boost::format("Vendor: %1%") % glGetString(GL_VENDOR) << std::endl;
    std::cout << boost::format("Renderer: %1%") % glGetString(GL_RENDERER) << std::endl;
    std::cout << boost::format("Version: %1%") % glGetString(GL_VERSION)  << std::endl;

    // Set callbacks for feedback.
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
    glfwSetWindowIconifyCallback(window, glfwWindowIconifyCallback);
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
}


/// Destroys the window and the OpenGL context
void RenderContext::destroyContext()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
