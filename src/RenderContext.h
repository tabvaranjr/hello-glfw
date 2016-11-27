#ifndef HELLO_GLFW_RENDERCONTEXT_H
#define HELLO_GLFW_RENDERCONTEXT_H

#include "ApplicationParameters.h"

class GLFWwindow;

class RenderContext
{
public:
    RenderContext(const ApplicationParameters& cliParameters);
    RenderContext(const RenderContext&) = delete;
    ~RenderContext();

    RenderContext& operator=(const RenderContext&) = delete;

    void swapBuffers();

    void poolEvents();

    bool isCloseRequested();

private:
    GLFWwindow* window;
    ApplicationParameters parameters;

    void makeContext();
    void destroyContext();
};

#endif
