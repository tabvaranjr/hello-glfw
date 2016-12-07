#ifndef HELLO_GLFW_CONSOLE_H
#define HELLO_GLFW_CONSOLE_H

#include <string>
#include <queue>
#include <thread>

class Console final
{
public:
    Console();
    ~Console();

    std::string getNextInputLine();

    bool hasInputAvailable() const;

private:
    std::deque<std::string> commands;

    std::thread inputThread;

    bool isQuitting;
};


#endif //HELLO_GLFW_CONSOLE_H
