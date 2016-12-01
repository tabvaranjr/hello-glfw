#ifndef HELLO_GLFW_SHADER_H
#define HELLO_GLFW_SHADER_H

#include "glad/glad.h"
#include "ObjectInterface.h"

#include <string>

class Shader : public ObjectInterface
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
};

#endif
