#ifndef __APPLICATION_PARAMETERS_H__
#define __APPLICATION_PARAMETERS_H__

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
