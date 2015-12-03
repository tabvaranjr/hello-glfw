#ifndef HELLO_GLFW_SHADER_H
#define HELLO_GLFW_SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    enum class Type : GLenum
    {
        Vertex = GL_VERTEX_SHADER,
        Geometry = GL_GEOMETRY_SHADER,
        Fragment = GL_FRAGMENT_SHADER
    };

    Shader(Type type, const std::string& source);
    ~Shader();

    GLuint getId() const { return id; }

private:
    GLuint id;
};

#endif
