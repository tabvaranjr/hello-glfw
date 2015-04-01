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
#include <memory>

#include "ApplicationParameters.h"
#include "File.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "RenderContext.h"

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
ApplicationParameters parseCommandLine(int argc, char* argv[])
{
    ApplicationParameters parameters;

    for (int i = 0; i < argc; ++i)
    {
        if (std::string(argv[i]) == "-d")
        {
            std::cout << "Debug mode is enabled." << std::endl;
            parameters.IsDebugModeActive = true;
        }
        else if (std::string(argv[i]) == "-f")
        {
            std::cout << "Full Screen mode is enabled." << std::endl;
            parameters.IsFullScreen = true;
        }
    }

    return parameters;
}


/// Program entry point
int main(int argc, char* argv[])
{
    auto&& parameters = parseCommandLine(argc, argv);

    auto context = std::make_shared<RenderContext>(parameters);

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
    while (!context->isCloseFlagged())
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

        context->swapBuffers();
        context->poolEvents();
    }

    return EXIT_SUCCESS;
}
