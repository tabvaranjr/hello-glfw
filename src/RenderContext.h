#ifndef HELLO_GLFW_RENDERCONTEXT_H
#define HELLO_GLFW_RENDERCONTEXT_H

#include <iostream>

class Parameters;
class GLFWwindow;

class RenderContext final
{
public:
    RenderContext();

    explicit RenderContext(const Parameters& parameters);

    RenderContext(const RenderContext&) = delete;

    ~RenderContext();

    RenderContext& operator=(const RenderContext&) = delete;

    void swapBuffers();

    void poolEvents() const;

    bool isCloseRequested() const;

    void printContextInformation() const;

private:
    GLFWwindow* window;
};

#endif
