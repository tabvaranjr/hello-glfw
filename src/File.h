#ifndef HELLO_GLFW_FILE_H
#define HELLO_GLFW_FILE_H

#include <string>

class File
{
public:
    /// Reads a text file into a string.
    static std::string readTextFile(const std::string& filename);
};

#endif

