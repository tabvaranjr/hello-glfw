#ifndef HELLO_GLFW_APPLICATION_PARAMETERS_H
#define HELLO_GLFW_APPLICATION_PARAMETERS_H

/// Holds the global parameters of the application.
struct ApplicationParameters
{
    static ApplicationParameters createFromCommandLineArguments(int argc, char** argv);

    bool IsDebugModeActive;
    bool IsFullScreen;

private:
    ApplicationParameters();
};

#endif
