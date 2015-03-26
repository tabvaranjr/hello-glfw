# ----------------------------------------------------------------------------
# Makefile for hello-glfw
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)
project(hello-glfw)

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Add local CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# C++11 support is required
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
endif()

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# GLFW3
find_package(GLFW3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Boost C++ Libraries
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# ----------------------------------------------------------------------------
# Program
# ----------------------------------------------------------------------------

file(GLOB SRC "src/*.cpp")
file(GLOB HDR "src/*.h")

add_executable(hello-glfw ${SRC} ${HDR})
target_link_libraries(hello-glfw ${GLEW_LIBRARIES} ${GLFW3_LIBRARY} ${OPENGL_gl_LIBRARY})
install(TARGETS hello-glfw RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION share)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

