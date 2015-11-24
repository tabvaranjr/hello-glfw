#ifndef HELLO_GLFW_MESH_H
#define HELLO_GLFW_MESH_H

#define GLEW_STATIC
#include <GL/glew.h>

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void Draw() const;

private:
    GLuint vao;
    GLuint vbo[3];
    GLsizei count;
};

#endif //HELLO_GLFW_MESH_H
