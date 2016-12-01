#ifndef HELLO_GLFW_COMMANDLINEARGUMENTS_H
#define HELLO_GLFW_COMMANDLINEARGUMENTS_H

#include <string>

struct CommandLineArguments
{
    static CommandLineArguments parse(int argc, char* argv[]);

    std::string scriptFile;
};

#endif //HELLO_GLFW_COMMANDLINEARGUMENTS_H
