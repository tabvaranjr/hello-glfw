#include "CommandLineArguments.h"
#include "LuaBindings.h"
#include "Parameters.h"
#include "TestApplication.h"
#include "sol.hpp"

#include <fmt/format.h>
#include <stdexcept>

int main(int argc, char* argv[])
{
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    LuaBindings::generate(lua);

    try
    {
        auto arguments = CommandLineArguments::parse(argc, argv);

        if (!arguments.scriptFile.empty())
        {
            lua.script_file(arguments.scriptFile);
        }
        else
        {
            auto parameters = Parameters();
            TestApplication app(parameters);
            app.run();
        }

        return 0;
    }
    catch (std::exception& e)
    {
        fmt::print("(┛◉Д◉)┛彡┻━┻: {0}\n", e.what());

        return 1;
    }
}
