#ifndef HELLO_GLFW_SHADERPROGRAM_H
#define HELLO_GLFW_SHADERPROGRAM_H

#include <string>
#include <GL/glew.h>

#include "Shader.h"

class ShaderProgram
{
public:
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    ShaderProgram(const Shader& vertexShader, const Shader& geometryShader, const Shader& fragmentShader);
    ~ShaderProgram();

    GLuint getId() const { return id; }

private:
    GLuint id;
};

#endif
