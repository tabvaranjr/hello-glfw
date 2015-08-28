#include "ShaderProgram.h"

#include <format.h>

#include "File.h"

ShaderProgram::ShaderProgram() :
    object(0)
{
}

ShaderProgram::~ShaderProgram()
{
}

GLuint ShaderProgram::createFromFiles(const std::string &program)
{
    auto&& vertexShaderFile = File::readTextFile(fmt::format("shaders/{0}.vert", program));
    auto vertexShaderFilePtr = vertexShaderFile.c_str();
    auto triangleVs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(triangleVs, 1, &vertexShaderFilePtr, nullptr);
    glCompileShader(triangleVs);

    auto&& geometryShaderFile = File::readTextFile(fmt::format("shaders/{0}.geom", program));
    auto geometryShaderFilePtr = geometryShaderFile.c_str();
    auto triangleGs = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(triangleGs, 1, &geometryShaderFilePtr, nullptr);
    glCompileShader(triangleGs);

    auto&& fragmentShaderFile = File::readTextFile(fmt::format("shaders/{0}.frag", program));
    auto fragmentShaderFilePtr = fragmentShaderFile.c_str();
    auto triangleFs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(triangleFs, 1, &fragmentShaderFilePtr, nullptr);
    glCompileShader(triangleFs);

    auto sp = glCreateProgram();
    glAttachShader(sp, triangleVs);
    glAttachShader(sp, triangleGs);
    glAttachShader(sp, triangleFs);

    glLinkProgram(sp);

    // Free the resources taken by the shader stage
    // It will be done once the program is deleted; otherwise, they will continue to exist!
    glDetachShader(sp, triangleVs);
    glDetachShader(sp, triangleGs);
    glDetachShader(sp, triangleFs);

    glDeleteShader(triangleVs);
    glDeleteShader(triangleGs);
    glDeleteShader(triangleFs);

    return sp;
}
