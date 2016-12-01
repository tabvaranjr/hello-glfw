#ifndef HELLO_GLFW_SHADERPROGRAM_H
#define HELLO_GLFW_SHADERPROGRAM_H

#include "glad/glad.h"
#include "ObjectInterface.h"

#include <string>

class Shader;

class ShaderProgram : public ObjectInterface
{
public:
    ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader);
    ShaderProgram(const Shader& vertexShader, const Shader& geometryShader, const Shader& fragmentShader);
    ~ShaderProgram();
};

#endif
