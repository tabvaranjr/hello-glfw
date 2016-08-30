#ifndef HELLO_GLFW_MESH_H
#define HELLO_GLFW_MESH_H

#include "glad/glad.h"
#include <vector>
#include <glm/vec3.hpp>

class Mesh
{
public:
    Mesh(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec3>& colors, const std::vector<glm::vec3>& normals);
    ~Mesh();

    void Draw() const;

private:
    GLuint vao;
    GLuint vbo[3];
    GLsizei count;
};

#endif //HELLO_GLFW_MESH_H
