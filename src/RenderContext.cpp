#include "RenderContext.h"

#include <format.h>
#include <iostream>
#include <stdexcept>

/// Callback for errors logged by GLFW
static void glfwErrorCallback(int error, const char* description)
{
    fmt::print("Error {0:#x}: {1}\n", error, description);
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
        buttonStr = fmt::format("Button {0}", button);
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

    fmt::print("{0} {1} with {2} modifier key(s)\n", buttonStr, actionStr, modsStr);
}

/// Callback when the window is minimized/iconified
static void glfwWindowIconifyCallback(GLFWwindow* window, int iconified)
{
    if (iconified)
    {
        fmt::print("Window was minimized\n");
    }
    else
    {
        fmt::print("Window was restored\n");
    }
}

/// Callback when the size of the window is changed
static void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
{
    fmt::print("Window size change to {0} x {1}\n", width, height);

    glViewport(0, 0, width, height);
}

/// Callback when an debug message is sent by OpenGL (with KHR_debug extension/OpenGL 4.3)
static void glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam)
{
    fmt::print(std::cerr, "Error {0:#x}: {1}\n", id, message);
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

bool RenderContext::isCloseRequested()
{
    return glfwWindowShouldClose(window);
}

void RenderContext::makeContext()
{
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    if (parameters.IsDebugModeActive)
    {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
        destroyContext();
        throw std::runtime_error("Failed to create a window with GLFW");
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Reminder: GLAD requires a valid OpenGL context before initialization.
    if (!gladLoadGL())
    {
        destroyContext();
        throw std::runtime_error("Failed to initialize GLAD.");
    }

    if (parameters.IsDebugModeActive)
    {
        if (GLAD_GL_VERSION_4_3 || GLAD_GL_KHR_debug)
        {
            glDebugMessageCallback(glDebugCallback, nullptr);
            glEnable(GL_DEBUG_OUTPUT);
        }
        else
        {
            fmt::print(std::cerr, "Missing KHR_debug extension support for debug output\n");
        }
    }

    fmt::print("Vendor: {0}\n", glGetString(GL_VENDOR));
    fmt::print("Renderer: {0}\n", glGetString(GL_RENDERER));
    fmt::print("Version: {0}\n", glGetString(GL_VERSION));

    // Set callbacks for feedback.
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
    glfwSetWindowIconifyCallback(window, glfwWindowIconifyCallback);
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
}

// void RenderContext::initializeGlew()
// {
//     glewExperimental = GL_TRUE;
//     GLenum err = glewInit();
//     if (err != GLEW_OK)
//     {
//         destroyContext();
//         throw std::runtime_error(fmt::format("Failed to initialize GLEW: {0}", glewGetErrorString(err)));
//     }
// }


/// Destroys the window and the OpenGL context
void RenderContext::destroyContext()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
