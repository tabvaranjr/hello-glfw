#include "ShaderProgram.h"

#include "File.h"
#include "Shader.h"

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& fragmentShader) :
    id(0)
{
    id = glCreateProgram();
    glAttachShader(id, vertexShader.getId());
    glAttachShader(id, fragmentShader.getId());

    glLinkProgram(id);

    // Free the resources taken by the shader stage
    // It will be done once the program is deleted; otherwise, they will continue to exist!
    glDetachShader(id, vertexShader.getId());
    glDetachShader(id, fragmentShader.getId());
}

ShaderProgram::ShaderProgram(const Shader& vertexShader, const Shader& geometryShader, const Shader& fragmentShader) :
    id(0)
{
    id = glCreateProgram();
    glAttachShader(id, vertexShader.getId());
    glAttachShader(id, geometryShader.getId());
    glAttachShader(id, fragmentShader.getId());

    glLinkProgram(id);

    // Free the resources taken by the shader stage
    // It will be done once the program is deleted; otherwise, they will continue to exist!
    glDetachShader(id, vertexShader.getId());
    glDetachShader(id, geometryShader.getId());
    glDetachShader(id, fragmentShader.getId());

}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(id);
}
