#.rst:
# FindFMT
# -------
#
# Locate the fmt/cppformat C++ formatting library.
#
# This module defines the following variables:
#
# ::
#
#   FMT_FOUND         - true when the fmt/cppformat header and library files are found
#   FMT_LIBRARY       - the fmt/cppformat library
#   FMT_INCLUDE_DIR   - path to fmt/cppformat include directory (format.h)

#=============================================================================
# Copyright 2015-2016 Patrick Clément-Bonhomme <patrick.cb@gmail.com>
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
    "/usr/include"
    "/usr/local/include"
)

set(_fmt_LIB_SEARCH_DIRS
    "/usr/lib"
    "/usr/local/lib"
)

# Use user spefied location when available as root search directory
set(_fmt_ENV_ROOT $ENV{FMT_ROOT})
if(NOT FMT_ROOT AND _fmt_ENV_ROOT)
    set(FMT_ROOT ${_fmt_ENV_ROOT})
endif()

if(FMT_ROOT)
    list(INSERT _fmt_HEADER_SEARCH_DIRS 0 "${FMT_ROOT}/include")
    list(INSERT _fmt_LIB_SEARCH_DIRS 0 "${FMT_ROOT}/lib")
endif()

# Search for the header
find_path(FMT_INCLUDE_DIR "fmt/format.h" PATHS ${_fmt_HEADER_SEARCH_DIRS})

# Search for the library
find_library(FMT_LIBRARY NAMES fmt cppformat PATHS ${_fmt_LIB_SEARCH_DIRS})

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(FMT DEFAULT_MSG FMT_INCLUDE_DIR FMT_LIBRARY)

mark_as_advanced(FMT_INCLUDE_DIR FMT_LIBRARY)
