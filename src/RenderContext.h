#ifndef HELLO_GLFW_RENDERCONTEXT_H
#define HELLO_GLFW_RENDERCONTEXT_H

class Parameters;
class GLFWwindow;

class RenderContext
{
public:
    RenderContext(const Parameters& parameters);
    RenderContext(const RenderContext&) = delete;
    ~RenderContext();

    RenderContext& operator=(const RenderContext&) = delete;

    void swapBuffers();

    void poolEvents();

    bool isCloseRequested();

private:
    GLFWwindow* window;
};

#endif
