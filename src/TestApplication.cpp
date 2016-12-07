#include "TestApplication.h"

#include <fmt/format.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include "Parameters.h"
#include "Camera.h"
#include "File.h"
#include "Mesh.h"
#include "RenderContext.h"
#include "Shader.h"
#include "ShaderProgram.h"

std::shared_ptr<ShaderProgram> makeShaderProgram(const std::string& program)
{
    auto vertexShaderFile = File::readTextFile(fmt::format("shaders/{0}.vert", program));
    Shader vs(Shader::Type::Vertex, vertexShaderFile);

    auto geometryShaderFile = File::readTextFile(fmt::format("shaders/{0}.geom", program));
    Shader gs(Shader::Type::Geometry, geometryShaderFile);

    auto fragmentShaderFile = File::readTextFile(fmt::format("shaders/{0}.frag", program));
    Shader fs(Shader::Type::Fragment, fragmentShaderFile);

    return std::make_shared<ShaderProgram>(vs, gs, fs);
}

std::shared_ptr<Mesh> makeSimpleQuad()
{
    std::vector<glm::vec3> vertices
    {
            { -0.5f, -0.5f, 0.0f },
            { 0.5f, 0.5f, 0.0f },
            { -0.5f, 0.5f, 0.0f },
            { 0.5f, -0.5f, 0.0f },
            { 0.5f, 0.5f, 0.0f },
            { -0.5f, -0.5f, 0.0f }
    };

    std::vector<glm::vec3> colors
    {
            { 1.0f, 0.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f },
            { 0.0f, 0.0f, 1.0f },
            { 1.0f, 1.0f, 0.0f },
            { 0.0f, 1.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f }
    };

    std::vector<glm::vec3> normals
    {
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 1.0f }
    };

    return std::make_shared<Mesh>(vertices, colors, normals);
}

TestApplication::TestApplication()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.05f, 0.05f, 0.05f, 1.0);

    // Create resources.
    mesh = makeSimpleQuad();
    shader = makeShaderProgram("simple");

    camera.reset(new Camera);
    camera->setPerspectiveProjection(90, 1, 0.1, 10.0);
    camera->setView(glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
}

TestApplication::~TestApplication()
{
}

void TestApplication::processInput()
{
}

void TestApplication::update(double time)
{
    model = glm::rotate(glm::mat4x4(1.0), static_cast<float>(time), glm::vec3(0, 0, 1));
}

void TestApplication::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader->getId());
    auto model_location = glGetUniformLocation(shader->getId(), "model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(model));

    auto view_location = glGetUniformLocation(shader->getId(), "view");
    glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(camera->getView()));

    auto proj_location = glGetUniformLocation(shader->getId(), "proj");
    glUniformMatrix4fv(proj_location, 1, GL_FALSE, glm::value_ptr(camera->getProjection()));

    mesh->Draw();
}
