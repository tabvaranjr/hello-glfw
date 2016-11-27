#ifndef HELLO_GLFW_RENDERCONTEXT_H
#define HELLO_GLFW_RENDERCONTEXT_H

class ApplicationParameters;
class GLFWwindow;

class RenderContext
{
public:
    RenderContext(const ApplicationParameters& parameters);
    RenderContext(const RenderContext&) = delete;
    ~RenderContext();

    RenderContext& operator=(const RenderContext&) = delete;

    void swapBuffers();

    void poolEvents();

    bool isCloseRequested();

private:
    GLFWwindow* window;

    void makeContext(const ApplicationParameters& parameters);
    void destroyContext();
};

#endif
