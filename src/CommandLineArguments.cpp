#include "CommandLineArguments.h"

#include <fmt/format.h>

CommandLineArguments CommandLineArguments::parse(int argc, char* argv[])
{
    CommandLineArguments args;

    if (argc > 1)
    {
        if (argc == 2)
        {
            args.configFile = argv[1];
        }
        else
        {
            throw std::runtime_error(fmt::format("usage: {0} [config_file]\n", argv[0]));
        }
    }

    return args;
}
