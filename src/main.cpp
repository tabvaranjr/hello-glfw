#include "CommandLineArguments.h"
#include "LuaBindings.h"
#include "Parameters.h"
#include "TestApplication.h"
#include "sol.hpp"

#include <fmt/format.h>
#include <stdexcept>

int main(int argc, char* argv[])
{
    try
    {
        auto arguments = CommandLineArguments::parse(argc, argv);

        sol::state lua;
        lua.open_libraries(sol::lib::base);
        LuaBindings::generate(lua);

        auto parameters = Parameters();
        if (!arguments.configFile.empty())
        {
            lua.script_file(arguments.configFile);
            parameters.IsFullScreen = lua["config"]["fullscreen"].get_or(false);
            parameters.IsDebugModeActive = lua["config"]["debug"].get_or(false);
        }

        TestApplication app(parameters);

        app.run();

        return 0;

    }
    catch (std::exception& e)
    {
        fmt::print("{0}\n", e.what());

        return 1;
    }
}
