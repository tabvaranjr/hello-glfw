///
/// \brief  Main program file
/// \author Patrick Clément-Bonhomme <patrick.cb@gmail.com>
///

#include <cstdlib>
#include <cmath>
#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <format.h>

#include "ApplicationParameters.h"
#include "File.h"
#include "RenderContext.h"
#include "Primitives.h"

/// Create the shader program.
GLuint createShaderProgram(const std::string& program)
{
    auto&& vertexShaderFile = File::readTextFile(fmt::format("shaders/{0}.vert", program));
    auto vertexShaderFilePtr = vertexShaderFile.c_str();
    auto triangleVs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(triangleVs, 1, &vertexShaderFilePtr, nullptr);
    glCompileShader(triangleVs);

    auto&& geometryShaderFile = File::readTextFile(fmt::format("shaders/{0}.geom", program));
    auto geometryShaderFilePtr = geometryShaderFile.c_str();
    auto triangleGs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(triangleGs, 1, &geometryShaderFilePtr, nullptr);
    glCompileShader(triangleGs);

    auto&& fragmentShaderFile = File::readTextFile(fmt::format("shaders/{0}.frag", program));
    auto fragmentShaderFilePtr = fragmentShaderFile.c_str();
    auto triangleFs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(triangleFs, 1, &fragmentShaderFilePtr, nullptr);
    glCompileShader(triangleFs);

    auto sp = glCreateProgram();
    glAttachShader(sp, triangleVs);
    glAttachShader(sp, triangleGs);
    glAttachShader(sp, triangleFs);

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
            fmt::print("Debug mode is enabled\n");
            parameters.IsDebugModeActive = true;
        }
        else if (std::string(argv[i]) == "-f")
        {
            fmt::print("Full screen mode is enabled\n");
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
    GLuint vao;
    GLuint count;
    createQuad(vao, count);
    auto sp = createShaderProgram("simple");

    // Set camera matrices.
    auto model_location = glGetUniformLocation(sp, "model");
    auto view_location = glGetUniformLocation(sp, "view");
    auto proj_location = glGetUniformLocation(sp, "proj");

    auto model = glm::mat4x4(1.0);
    auto proj = glm::mat4x4(1.0);
    auto view = glm::mat4x4(1.0);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0);

    // Main loop
    while (!context->isCloseRequested())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sp);

        auto time = static_cast<float>(glfwGetTime());
        model = glm::rotate(glm::mat4x4(1.0), time, glm::vec3(0, 0, 1));

        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(proj));

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, count);

        context->swapBuffers();
        context->poolEvents();
    }

    return EXIT_SUCCESS;
}
