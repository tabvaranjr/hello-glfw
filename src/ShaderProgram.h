#ifndef HELLO_GLFW_SHADERPROGRAM_H
#define HELLO_GLFW_SHADERPROGRAM_H

#define GLEW_STATIC
#include <GL/glew.h>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    GLuint getObject() const { return object; }

private:
    GLuint object;
};

#endif

