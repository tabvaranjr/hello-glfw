#include "ApplicationParameters.h"

#include <string>
#include <fmt/format.h>

ApplicationParameters::ApplicationParameters() :
        IsDebugModeActive(false),
        IsFullScreen(false)
{
}

ApplicationParameters ApplicationParameters::createFromCommandLineArguments(int argc, char** argv)
{
    ApplicationParameters parameters;

    for (int i = 0; i < argc; ++i)
    {
        if (std::string(argv[i]) == "-d")
        {
            fmt::print("Debug mode is enabled\n");
            parameters.IsDebugModeActive = true;
        }
        else if (std::string(argv[i]) == "-f")
        {
            fmt::print("Full screen mode is enabled\n");
            parameters.IsFullScreen = true;
        }
    }

    return parameters;
}
