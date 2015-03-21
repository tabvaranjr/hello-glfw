///
/// \brief  Main program file
/// \author Patrick Clément-Bonhomme <patrick.cb@gmail.com>
///

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

/// Callback for errors logged by GLFW
static void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "Error " << error << ": " << description << std::endl;
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
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
        std::cout << "Left button";   
        break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
        std::cout << "Middle button";
        break;

    case GLFW_MOUSE_BUTTON_RIGHT:
        std::cout << "Right button";
        break;

    default:
        std::cout << "Button " << button;
        break;
    }

   switch (action)
    {
    case GLFW_PRESS:
        std::cout << " pressed";
        break;    

    case GLFW_RELEASE:
        std::cout << " released";
        break;
    }

    if (mods != 0)
    {
        std::cout << " with";

        if (mods & GLFW_MOD_SHIFT)
        {
            std::cout << " SHIFT";
        }
        
        if (mods & GLFW_MOD_CONTROL)
        {
            std::cout << " CTRL";
        } 

        if (mods & GLFW_MOD_ALT)
        {
            std::cout << " ALT";
        }

        if (mods & GLFW_MOD_SUPER)
        {
            std::cout << " SUPER";
        }    
    }
    
    std::cout << std::endl;
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
    std::cout << "Window size changed to: " << width << "x" << height << std::endl;

    glViewport(0, 0, width, height);
}


/// Reads a text file into a string
std::string readTextFile(const std::string& filename)
{
    std::ifstream ifs(filename.c_str());
    if (ifs)
    {
        std::stringstream sstr;
        sstr << ifs.rdbuf();
        ifs.close();
        return sstr.str();
    }
    else
    {
        std::cerr << "Failed to read " << filename << std::endl;
        return "";
    }
}


/// Program entry point
int main(int argc, char* argv[])
{
    glfwSetErrorCallback(glfwErrorCallback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW." << std::endl;
        return EXIT_FAILURE;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello GLFW3", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);    

    // Reminder: GLEW requires a valid OpenGL context before initialization.
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION)  << std::endl;

    // Set callbacks for feedback.
    glfwSetKeyCallback(window, glfwKeyCallback);
    glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
    glfwSetWindowIconifyCallback(window, glfwWindowIconifyCallback);
    glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);

    glEnable(GL_DEPTH_TEST);

    GLfloat triangleVertices[] = 
    {
        0.75f, 0.75f, 0.0f,
        -0.75f, 0.75f, 0.0f,
        0.0f, -0.75f, 0.0f
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

    // Create the shader stage objects.
    std::string&& vertexShaderFile = readTextFile("shaders/hello.vs.glsl");
    auto vertexShaderFilePtr = vertexShaderFile.c_str();
    GLuint triangleVs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(triangleVs, 1, &vertexShaderFilePtr, nullptr);
    glCompileShader(triangleVs);

    std::string&& geometryShaderFile = readTextFile("shaders/hello.gs.glsl");
    auto geometryShaderFilePtr = geometryShaderFile.c_str();
    GLuint triangleGs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(triangleGs, 1, &geometryShaderFilePtr, nullptr);
    glCompileShader(triangleGs);

    std::string&& fragmentShaderFile = readTextFile("shaders/hello.fs.glsl");
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

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sp);
        glBindVertexArray(triangleVao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return EXIT_SUCCESS;
}

