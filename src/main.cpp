#include <cstdlib>
#include <cmath>
#include <memory>
#include <chrono>
#include <thread>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <fmt/format.h>

#include "ApplicationParameters.h"
#include "Demo.h"
#include "Camera.h"
#include "Mesh.h"
#include "RenderContext.h"
#include "ShaderProgram.h"

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
    auto parameters = parseCommandLine(argc, argv);

    auto context = std::make_shared<RenderContext>(parameters);

    // Create resources.
    auto mesh = makeSimpleQuad();
    auto sp = makeShaderProgram("simple");

    auto cam = Camera();
    cam.setPerspectiveProjection(90, 1, 0.1, 10.0);
    cam.setView(glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0);

    // Main loop
    while (!context->isCloseRequested())
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(sp->getId());

        auto time = static_cast<float>(glfwGetTime());
        auto model = glm::rotate(glm::mat4x4(1.0), time, glm::vec3(0, 0, 1));

        auto model_location = glGetUniformLocation(sp->getId(), "model");
        glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

        auto view_location = glGetUniformLocation(sp->getId(), "view");
        glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(cam.getView()));

        auto proj_location = glGetUniformLocation(sp->getId(), "proj");
        glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(cam.getProjection()));

        mesh->Draw();

        context->swapBuffers();
        context->poolEvents();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    return 0;
}
