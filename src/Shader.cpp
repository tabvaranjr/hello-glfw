#include "Shader.h"

#include <stdexcept>

Shader::Shader(Type type, const std::string& source)
{
    id = glCreateShader(static_cast<GLenum>(type));

    auto sourcePtr = source.c_str();
    glShaderSource(id, 1, &sourcePtr, nullptr);
    glCompileShader(id);
}

Shader::~Shader()
{
    glDeleteShader(id);
}
