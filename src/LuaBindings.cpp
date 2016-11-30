//
// Created by pclement on 16-11-29.
//

#include "LuaBindings.h"

#include "sol.hpp"
#include "Parameters.h"

void LuaBindings::generate(sol::state& lua)
{
    lua.new_usertype<Parameters>(
            "Parameters",
            sol::constructors<sol::types<>>(),
            "fullscreen", &Parameters::IsFullScreen,
            "debug", &Parameters::IsDebugModeActive
    );
}
