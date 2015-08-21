#include "File.h"

#include <format.h>
#include <fstream>
#include <iostream>
#include <sstream>

std::string File::readTextFile(const std::string& filename)
{
    std::ifstream ifs(filename.c_str());
    if (ifs)
    {
        std::stringstream sstr;
        sstr << ifs.rdbuf();
        ifs.close();
        return sstr.str();
    }
    else
    {
        fmt::print(std::cerr, "Failed to open {0} for reading.\n", filename);
        return "";
    }
}

