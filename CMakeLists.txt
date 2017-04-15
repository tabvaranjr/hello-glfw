# ----------------------------------------------------------------------------
# Makefile for hello-glfw
# ----------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.1)
project(hello-glfw)

# ----------------------------------------------------------------------------
# Options
# ----------------------------------------------------------------------------

option(USE_EXTERNAL_GLFW "Use the version of GLFW found in the 'external' directory" OFF)
option(USE_EXTERNAL_GLM "Use the version of GLM found in the 'external' directory" OFF)
option(USE_EXTERNAL_FMT "Use the version of fmt found in the 'external' directory" OFF)

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------

# Add local CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# Any local threading library
find_package(Threads REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Set up the generated GLAD bindings
set(GLAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glad)
set(GLAD_INCLUDE_DIR ${GLAD_DIR}/include)
set(GLAD_SRC ${GLAD_INCLUDE_DIR}/glad/glad.h ${GLAD_DIR}/src/glad.c)
include_directories(${GLAD_INCLUDE_DIR})

# GLFW
if(USE_EXTERNAL_GLFW)
    message(STATUS "Using external GLFW")
    add_subdirectory(external/glfw)
    set(GLFW_LIBRARY glfw ${GLFW_LIBRARIES})
else()
    find_package(GLFW REQUIRED)
    include_directories(${GLFW_INCLUDE_DIR})
    add_definitions("-DGLFW_INCLUDE_NONE")
endif()

# GLM
if(USE_EXTERNAL_GLM)
    message(STATUS "Using external GLM")
    set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/glm CACHE PATH "Include directory for GLM")
else()
    find_package(GLM REQUIRED)
    include_directories(${GLM_INCLUDE_DIR})
endif()

# fmt
if(USE_EXTERNAL_FMT)
    message(STATUS "Using external fmt")
    add_subdirectory(external/fmt)
    set(FMT_LIBRARY fmt)
else()
    find_package(Fmt REQUIRED)
    include_directories(${FMT_INCLUDE_DIR})
endif()

# ----------------------------------------------------------------------------
# Program
# ----------------------------------------------------------------------------

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
    src/CommandLineArguments.cpp src/CommandLineArguments.h
    src/ObjectInterface.h
    )

add_executable(hello-glfw ${SOURCE_FILES} ${GLAD_SRC})
target_link_libraries(hello-glfw ${GLFW_LIBRARY} ${FMT_LIBRARY} ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT})

install(TARGETS hello-glfw RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION share)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/testapplication.lua DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
