#ifndef HELLO_GLFW_APPLICATION_H
#define HELLO_GLFW_APPLICATION_H

#include "ApplicationParameters.h"
#include "RenderContext.h"

#include <memory>

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
