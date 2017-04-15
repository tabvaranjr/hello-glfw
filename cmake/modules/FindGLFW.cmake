# Locate the glfw library
#
# This module defines the following variables:
#
# GLFW_LIBRARY      the name of the library;
# GLFW_INCLUDE_DIR  where to find glfw include files.
# GLFW_FOUND        true if both the GLFW_LIBRARY and GLFW_INCLUDE_DIR have been found.
#
# To help locate the library and include file, you can define a 
# variable called GLFW_ROOT which points to the root of the glfw library
# installation.
#

# default search dirs
set( _glfw_HEADER_SEARCH_DIRS
  "/usr/include"
  "/usr/local/include"
  "C:/Program Files (x86)/glfw/include" )
set( _glfw_LIB_SEARCH_DIRS
  "/usr/lib"
  "/usr/local/lib"
  "C:/Program Files (x86)/glfw/lib-msvc110" )

# Check environment for root search directory
set( _glfw_ENV_ROOT $ENV{GLFW_ROOT} )
if( NOT GLFW_ROOT AND _glfw_ENV_ROOT )
  set(GLFW_ROOT ${_glfw_ENV_ROOT} )
endif()

# Put user specified location at beginning of search
if( GLFW_ROOT )
  list( INSERT _glfw_HEADER_SEARCH_DIRS 0 "${GLFW_ROOT}/include" )
  list( INSERT _glfw_LIB_SEARCH_DIRS 0 "${GLFW_ROOT}/lib" )
endif()

# Search for the header 
FIND_PATH(GLFW_INCLUDE_DIR "GLFW/glfw3.h"
  PATHS ${_glfw_HEADER_SEARCH_DIRS} )

# Search for the library
FIND_LIBRARY(GLFW_LIBRARY NAMES glfw
  PATHS ${_glfw_LIB_SEARCH_DIRS} )

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GLFW DEFAULT_MSG
                                  GLFW_LIBRARY GLFW_INCLUDE_DIR)
