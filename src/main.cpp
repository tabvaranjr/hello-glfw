///
/// \brief  Main program file
/// \author Patrick Clément-Bonhomme <patrick.cb@gmail.com>
///

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <boost/format.hpp>
#include <cmath>

#include "File.h"
#include "Shader.h"
#include "ShaderProgram.h"

/// Activates KHR_debug extension in OpenGL.
static bool IsDebugEnabled = false;


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
static void glDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cerr << boost::format("Error %1%: %2%") % id % message << std::endl;
}


/// Create a triangle.
GLuint createTriangle()
{
    GLfloat triangleVertices[] = 
    {
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f
    };

    GLfloat triangleColors[] =
    {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };

    GLfloat triangleNormals[] =
    {
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

    // Create a VBO for the triangle.
    GLuint triangleVbo[3];
    glGenBuffers(3, triangleVbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleColors), triangleColors, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleNormals), triangleNormals, GL_STATIC_DRAW);

    // Create a VAO for the triangle.
    GLuint triangleVao;
    glGenVertexArrays(1, &triangleVao);
    glBindVertexArray(triangleVao);
   
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVbo[2]);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    return triangleVao;
}


/// Create the shader program.
GLuint createShaderProgram(const std::string& program)
{
    boost::format file("shaders/%1%.%2%");

    std::string&& vertexShaderFile = File::readTextFile((file % program % "vert").str());
    auto vertexShaderFilePtr = vertexShaderFile.c_str();
    GLuint triangleVs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(triangleVs, 1, &vertexShaderFilePtr, nullptr);
    glCompileShader(triangleVs);

    std::string&& geometryShaderFile = File::readTextFile((file % program % "geom").str());
    auto geometryShaderFilePtr = geometryShaderFile.c_str();
    GLuint triangleGs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(triangleGs, 1, &geometryShaderFilePtr, nullptr);
    glCompileShader(triangleGs);

    std::string&& fragmentShaderFile = File::readTextFile((file % program % "frag").str());
    auto fragmentShaderFilePtr = fragmentShaderFile.c_str();
    GLuint triangleFs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(triangleFs, 1, &fragmentShaderFilePtr, nullptr);
    glCompileShader(triangleFs);

    // Create the shader program object.
    GLuint sp = glCreateProgram();
    glAttachShader(sp, triangleVs);
    glAttachShader(sp, triangleGs);
    glAttachShader(sp, triangleFs);

    glBindAttribLocation(sp, 0, "pos");
    glBindAttribLocation(sp, 1, "color");
    glBindAttribLocation(sp, 2, "normal");

    glLinkProgram(sp);

    // Free the resources taken by the shader stage
    // It will be done once the program is deleted; otherwise, they will continue to exist!
    glDetachShader(sp, triangleVs);
    glDetachShader(sp, triangleGs);
    glDetachShader(sp, triangleFs);

    glDeleteShader(triangleVs);
    glDeleteShader(triangleGs);
    glDeleteShader(triangleFs);

    return sp;
}


/// Parses the command line
void parseCommandLine(int argc, char* argv[])
{
    for (int i = 0; i < argc; ++i)
    {
        if (std::string(argv[i]) == "-d") 
        {
            std::cout << "Debug mode is enabled." << std::endl;            
            IsDebugEnabled = true;
        }    
    }
}


/// Makes an OpenGL context with a window
GLFWwindow* makeContext()
{
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return nullptr;
    }

    if (IsDebugEnabled)
    {
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    }

    auto window = glfwCreateWindow(800, 800, "Hello GLFW3", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    

    // Reminder: GLEW requires a valid OpenGL context before initialization.
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << boost::format("Failed to initialize GLEW: %1%") % glewGetErrorString(err) << std::endl;

        glfwTerminate();
        return nullptr;
    }

    if (IsDebugEnabled)
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

    return window;
}


/// Destroys the window and the OpenGL context
void destroyContext(GLFWwindow* window)
{
    glfwDestroyWindow(window);
    glfwTerminate();
}


/// Program entry point
int main(int argc, char* argv[])
{
    parseCommandLine(argc, argv);

    auto window = makeContext();
    if (window == nullptr)
    {
        return EXIT_FAILURE;
    }

    // Create resources.
    GLuint vao = createTriangle();
    GLuint sp = createShaderProgram("simple");

    // Set camera matrices.
    auto model_location = glGetUniformLocation(sp, "model");
    auto view_location = glGetUniformLocation(sp, "view");
    auto proj_location = glGetUniformLocation(sp, "proj");

    GLfloat model[] = 
    { 
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    GLfloat view[] = 
    { 
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    GLfloat proj[] = 
    { 
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sp);
        
        float time = static_cast<float>(glfwGetTime());
        view[0] = cos(time);
        view[1] = -sin(time);
        view[4] = sin(time);
        view[5] = cos(time);
        
        glUniformMatrix4fv(model_location, 1, GL_FALSE, model);
        glUniformMatrix4fv(view_location, 1, GL_FALSE, view);
        glUniformMatrix4fv(proj_location, 1, GL_FALSE, proj);
        
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    destroyContext(window);

    return EXIT_SUCCESS;
}

