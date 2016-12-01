#ifndef HELLO_GLFW_OBJECTINTERFACE_H
#define HELLO_GLFW_OBJECTINTERFACE_H

#include "glad/glad.h"

class ObjectInterface
{
public:
    GLuint getId() const
    {
        return id;
    }

protected:
    GLuint id;
};

#endif //HELLO_GLFW_OBJECTINTERFACE_H
