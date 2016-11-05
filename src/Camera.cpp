#include "Camera.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera()
{
    view = glm::mat4(1.0);
    projection = glm::mat4(1.0);
}

void Camera::setPerspectiveProjection(double fov, double aspect, double zNear, double zFar)
{
    projection = glm::perspective(glm::radians(fov), aspect, zNear, zFar);
}

void Camera::setView(const glm::mat4& view)
{
    Camera::view = view;
}

const glm::mat4& Camera::getView() const
{
    return view;
}

const glm::mat4& Camera::getProjection() const
{
    return projection;
}
