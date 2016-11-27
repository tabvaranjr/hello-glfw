#ifndef HELLO_GLFW_APPLICATION_H
#define HELLO_GLFW_APPLICATION_H

#include <memory>

class ApplicationParameters;
class RenderContext;

class TestApplication
{
public:
    TestApplication(const ApplicationParameters& parameters);
    virtual ~TestApplication();

    void run();

private:
    std::shared_ptr<RenderContext> context;
};


#endif //HELLO_GLFW_APPLICATION_H
