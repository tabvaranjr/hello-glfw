#ifndef __SHADER_H__
#define __SHADER_H__

#define GLEW_STATIC
#include <GL/glew.h>

class Shader
{
public:
    Shader();
    ~Shader();

    GLuint getObject() const { return mObject; }

private:
    GLuint mObject;    
};

#endif

