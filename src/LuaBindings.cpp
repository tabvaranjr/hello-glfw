#include "LuaBindings.h"

#include "sol.hpp"

#include "Parameters.h"
#include "Timer.h"
#include "TestApplication.h"

void LuaBindings::generate(sol::state& lua)
{
    lua.new_usertype<Parameters>(
            "Parameters",
            sol::constructors<sol::types<>>(),
            "fullscreen", &Parameters::IsFullScreen,
            "debug", &Parameters::IsDebugModeActive
    );

    lua.new_usertype<Timer>(
            "Timer",
            sol::constructors<sol::types<>>(),
            "reset", &Timer::reset,
            "getTime", &Timer::getTime
    );
}
