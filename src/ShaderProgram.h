#ifndef HELLO_GLFW_SHADERPROGRAM_H
#define HELLO_GLFW_SHADERPROGRAM_H

#include <string>
#define GLEW_STATIC
#include <GL/glew.h>


class ShaderProgram
{
public:
    static GLuint createFromFiles(const std::string &program);

    ShaderProgram();
    ~ShaderProgram();

    GLuint getObject() const { return object; }

private:
    GLuint object;
};

#endif

