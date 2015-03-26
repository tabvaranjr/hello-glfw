#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#define GLEW_STATIC
#include <GL/glew.h>

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();

    GLuint getObject() const { return mObject; }

private:
    GLuint mObject;
};

#endif

