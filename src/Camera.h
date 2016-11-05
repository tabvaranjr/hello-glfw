#ifndef HELLO_GLFW_CAMERA_H
#define HELLO_GLFW_CAMERA_H

#include <glm/mat4x4.hpp>

class Camera
{
public:
    Camera();

    void setView(const glm::mat4& view);

    void setPerspectiveProjection(double fov, double aspect, double zNear, double zFar);

    const glm::mat4& getView() const;

    const glm::mat4& getProjection() const;

private:
    glm::mat4 view;
    glm::mat4 projection;
};


#endif //HELLO_GLFW_CAMERA_H
