#include "TestApplication.h"
#include "Parameters.h"

#include <iostream>
#include <string>

#include "sol.hpp"
#include "LuaBindings.h"

int main(int argc, char* argv[])
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    LuaBindings::generate(lua);

    lua.script_file("config.lua");
    auto parameters = Parameters();
    parameters.IsFullScreen = lua["config"]["fullscreen"].get_or(false);
    parameters.IsDebugModeActive = lua["config"]["debug"].get_or(false);

    TestApplication app(parameters);

    app.run();

    return 0;
}
