///
/// \brief  Main program file
/// \author Patrick Clément-Bonhomme <patrick.cb@gmail.com>
///

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <boost/format.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ApplicationParameters.h"
#include "File.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "RenderContext.h"

/// Create a triangle.
GLuint createTriangle()
{
    std::vector<glm::vec3> vertices
    {
        { 0.5f, 0.5f, 0.0f },
        { -0.5f, 0.5f, 0.0f },
        { 0.0f, -0.5f, 0.0f }
    };

    std::vector<glm::vec3> colors
    {
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 0.0f, 1.0f }
    };

    std::vector<glm::vec3> normals
    {
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 1.0f },
        { 0.0f, 0.0f, 1.0f }
    };

    // Create vertex buffer objects (VBOs)
    GLuint vbo[3];
    glGenBuffers(3, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), glm::value_ptr(vertices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3),  glm::value_ptr(colors[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),  glm::value_ptr(normals[0]), GL_STATIC_DRAW);

    // Create a vertex array object (VAO).
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    return vao;
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

    glm::mat4x4 model = glm::mat4x4(1.0);
    glm::mat4x4 proj = glm::mat4x4(1.0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0);

    // Main loop
    while (!context->isCloseFlagged())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sp);

        float time = static_cast<float>(glfwGetTime());
        glm::mat4x4 view = glm::rotate(glm::mat4x4(1.0), time, glm::vec3(0, 0, 1));

        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        context->swapBuffers();
        context->poolEvents();
    }

    return EXIT_SUCCESS;
}
