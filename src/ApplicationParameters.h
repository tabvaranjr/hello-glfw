#ifndef HELLO_GLFW_APPLICATION_PARAMETERS_H
#define HELLO_GLFW_APPLICATION_PARAMETERS_H

/// Holds the global parameters of the application.
struct ApplicationParameters
{
    ApplicationParameters() :
        IsDebugModeActive(false),
        IsFullScreen(false)
    {
    }

    bool IsDebugModeActive;
    bool IsFullScreen;
};

#endif
