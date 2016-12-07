# ----------------------------------------------------------------------------
# Makefile for hello-glfw
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.1)
project(hello-glfw)

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Add local CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# GLFW3
find_package(GLFW3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIR})
add_definitions("-DGLFW_INCLUDE_NONE")

# GLAD
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glad)
set(GLAD_INCLUDE_DIR ${GLAD_DIR}/include)
set(GLAD_SRC ${GLAD_INCLUDE_DIR}/glad/glad.h ${GLAD_DIR}/src/glad.c)
include_directories(${GLAD_INCLUDE_DIR})

# GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

# fmt
find_package(Fmt REQUIRED)
include_directories(${FMT_INCLUDE_DIR})

# Lua
find_package(Lua REQUIRED)
include_directories(${LUA_INCLUDE_DIR})

# sol2 (Lua wrapper)
set(SOL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/sol2)
set(SOL_INCLUDE_DIR ${SOL_DIR})
include_directories(${SOL_INCLUDE_DIR})

# Any local threading library
find_package(Threads REQUIRED)

# ----------------------------------------------------------------------------
# Program
# ----------------------------------------------------------------------------

# C++14 is a requirement for the whole project due to sol2
# This isn't a bad thing, mind you.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES src/main.cpp
    src/Console.cpp src/Console.h
    src/Parameters.cpp src/Parameters.h
    src/Camera.cpp src/Camera.h
    src/File.cpp src/File.h
    src/Mesh.cpp src/Mesh.h
    src/RenderContext.cpp src/RenderContext.h
    src/Shader.cpp src/Shader.h
    src/ShaderProgram.cpp src/ShaderProgram.h
    src/TestApplication.cpp src/TestApplication.h
    src/Timer.cpp src/Timer.h
    src/LuaBindings.cpp src/LuaBindings.h
    src/CommandLineArguments.cpp src/CommandLineArguments.h
    src/ObjectInterface.h
    )

add_executable(hello-glfw ${SOURCE_FILES} ${GLAD_SRC})
target_link_libraries(hello-glfw ${GLFW3_LIBRARY} ${FMT_LIBRARY} ${LUA_LIBRARY} Threads::Threads ${CMAKE_DL_LIBS})

install(TARGETS hello-glfw RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION share)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testapplication.lua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
