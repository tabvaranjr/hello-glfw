#ifndef HELLO_GLFW_APPLICATION_H
#define HELLO_GLFW_APPLICATION_H

#include <memory>

class Parameters;
class RenderContext;

class TestApplication
{
public:
    TestApplication(const Parameters& parameters);
    virtual ~TestApplication();

    void run();

private:
    std::shared_ptr<RenderContext> context;
};


#endif //HELLO_GLFW_APPLICATION_H
