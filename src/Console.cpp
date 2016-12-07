#include "Console.h"

#include <sstream>
#include <iostream>
#include <fmt/format.h>


Console::Console() :
        isQuitting(false)
{
    auto inputLoop = [&]()
    {
        std::string buf;

        while (!isQuitting)
        {
            fmt::print("> ");

            if (std::getline(std::cin, buf))
            {
                commands.push_back(buf);
            }
            else if (std::cin.eof())
            {
                fmt::print("EOF detected.\n");
                std::cin.clear();
            }
        }
    };

    inputThread = std::thread(inputLoop);
}

Console::~Console()
{
    isQuitting = true;
    inputThread.join();
}

bool Console::hasInputAvailable() const
{
    return (!commands.empty());
}

std::string Console::getNextInputLine()
{
    std::string command(commands.front());
    commands.pop_front();
    return command;
}
