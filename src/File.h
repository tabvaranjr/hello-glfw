#ifndef __FILE_H__
#define __FILE_H__

#include <string>

class File
{
public:
    /// Reads a text file into a string.
    static std::string readTextFile(const std::string& filename);
};

#endif

