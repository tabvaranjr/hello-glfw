#include "CommandLineArguments.h"
#include "Console.h"
#include "RenderContext.h"
#include "Timer.h"
#include "sol.hpp"
#include "TestApplication.h"

#include <fmt/format.h>
#include <stdexcept>


int main(int argc, char* argv[])
{
    try
    {
        sol::state lua;
        lua.open_libraries(sol::lib::base);

        RenderContext context;
        Console console;
        Timer mainclock;

        auto arguments = CommandLineArguments::parse(argc, argv);

        TestApplication test;

        // Main loop.
        while (true)
        {
            auto time = mainclock.getTime();

            // Process input.
            if (console.hasInputAvailable())
            {
                std::string command = console.getNextInputLine();

                try
                {
                    lua.script(command);
                }
                catch (sol::error& e)
                {
                    fmt::print("щ（ﾟДﾟщ）: {0}\n", e.what());
                }
            }

            test.processInput();

            context.poolEvents();
            if (context.isCloseRequested())
            {
                break;
            }

            // Update.
            test.update(time);

            // Render.
            test.render();
            context.swapBuffers();

            // Take a well-deserved nap...
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

        return 0;
    }
    catch (std::exception& e)
    {
        fmt::print("(┛◉Д◉)┛彡┻━┻: {0}\n", e.what());

        return 1;
    }
}
