#ifndef HELLO_GLFW_APPLICATION_H
#define HELLO_GLFW_APPLICATION_H

#include <memory>
#include <glm/mat4x4.hpp>

class Camera;
class Mesh;
class ShaderProgram;

class TestApplication final
{
public:
    TestApplication();
    ~TestApplication();

    void processInput();
    void update(double time);
    void render();

private:
    glm::mat4x4 model;
    std::shared_ptr<Camera> camera;
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<ShaderProgram> shader;
};


#endif //HELLO_GLFW_APPLICATION_H
