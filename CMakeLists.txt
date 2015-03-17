# Makefile for hello-glfw
#
# NOTE: This file is currently quite UNIX-centric.
   
cmake_minimum_required(VERSION 2.8)
project(hello-glfw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

include_directories(${GLFW_INCLUDE_DIRS})

file(GLOB SRC "*.cpp")
file(GLOB HDR "*.h")

add_executable(hello-glfw ${SRC} ${HDR})
target_link_libraries(hello-glfw ${GLFW_LIBRARIES})

