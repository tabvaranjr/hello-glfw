#ifndef __RENDERCONTEXT_H__
#define __RENDERCONTEXT_H__

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ApplicationParameters.h"

class RenderContext
{
public:
    RenderContext(const ApplicationParameters& cliParameters);
    RenderContext(const RenderContext&) = delete;
    ~RenderContext();

    RenderContext& operator=(const RenderContext&) = delete;

    void swapBuffers();

    void poolEvents();

    bool isCloseFlagged();

private:
    GLFWwindow* window;
    ApplicationParameters parameters;

    void makeContext();
    void destroyContext();
};

#endif
