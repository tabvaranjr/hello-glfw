#include "File.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <boost/format.hpp>

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
        std::cerr << boost::format("Failed to open %1% for reading.") % filename << std::endl;
        return "";
    }
}

