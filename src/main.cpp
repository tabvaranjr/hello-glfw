#include "CommandLineArguments.h"
#include "Console.h"
#include "RenderContext.h"
#include "Timer.h"
#include "sol.hpp"
#include "TestApplication.h"

#include <fmt/format.h>
#include <stdexcept>

const double MaxSecondsPerFrame = 1.0 / 60.0;

int main(int argc, char* argv[])
{
    try
    {
        auto arguments = CommandLineArguments::parse(argc, argv);

        sol::state lua;
        lua.open_libraries(sol::lib::base);

        RenderContext context;
        Console console;
        Timer mainclock;

        TestApplication test;

        // Main loop.
        auto lastTime = mainclock.getTime();
        while (true)
        {
            auto currentTime = mainclock.getTime();

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
            test.update(currentTime);

            // Render.
            test.render();
            context.swapBuffers();

            // Take a nap... when well-deserved.
            lastTime = mainclock.getTime();
            double elapsedTime = lastTime - currentTime;
            if (elapsedTime < MaxSecondsPerFrame)
            {
                std::this_thread::sleep_for(std::chrono::duration<double>(MaxSecondsPerFrame - elapsedTime));
            }
        }

        return 0;
    }
    catch (std::exception& e)
    {
        fmt::print("(┛◉Д◉)┛彡┻━┻: {0}\n", e.what());

        return 1;
    }
}
