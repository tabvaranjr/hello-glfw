#.rst:
# FindCppFormat
# -------
#
# Locate the cppformat C++ formatting library.
#
# This module defines the following variables:
#
# ::
#
#   CPPFORMAT_FOUND         - true when the cppformat header and library files are found
#   CPPFORMAT_LIBRARY       - the cppformat library
#   CPPFORMAT_INCLUDE_DIR   - path to cppformat include directory (format.h)

#=============================================================================
# Copyright 2015 Patrick Clément-Bonhomme <patrick.cb@gmail.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

# Default search directories
set(_fmt_HEADER_SEARCH_DIRS
    "/usr/include/cppformat/"
    "/usr/include"
    "/usr/local/include"
)

set(_fmt_LIB_SEARCH_DIRS
    "/usr/lib"
    "/usr/local/lib"
)

# Search for the header
find_path(CPPFORMAT_INCLUDE_DIR "format.h" PATHS ${_fmt_HEADER_SEARCH_DIRS})

# Search for the library
find_library(CPPFORMAT_LIBRARY NAMES cppformat format PATHS ${_fmt_LIB_SEARCH_DIRS} )

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CPPFORMAT DEFAULT_MSG CPPFORMAT_INCLUDE_DIR CPPFORMAT_LIBRARY)

mark_as_advanced(CPPFORMAT_INCLUDE_DIR CPPFORMAT_LIBRARY)
