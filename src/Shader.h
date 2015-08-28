#ifndef HELLO_GLFW_SHADER_H
#define HELLO_GLFW_SHADER_H

#define GLEW_STATIC
#include <GL/glew.h>

class Shader
{
public:
    Shader();
    ~Shader();

    GLuint getObject() const { return object; }

private:
    GLuint object;    
};

#endif

