# Makefile for hello-glfw
#
# NOTE: This file is a bit less but nevertheless still UNIX-centric.
   
cmake_minimum_required(VERSION 2.8)
project(hello-glfw)

# ----------------------------------------------------------------------------

# C++11 support is required
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
endif()

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# GLFW3
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# ----------------------------------------------------------------------------

file(GLOB SRC "*.cpp")
file(GLOB HDR "*.h")

add_executable(hello-glfw ${SRC} ${HDR})
target_link_libraries(hello-glfw ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${OPENGL_gl_LIBRARY})

