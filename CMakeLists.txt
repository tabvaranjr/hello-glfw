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

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

# cppformat
find_package(CppFormat REQUIRED)
include_directories(${CPPFORMAT_INCLUDE_DIR})

# ----------------------------------------------------------------------------
# Program
# ----------------------------------------------------------------------------

file(GLOB SRC "src/*.cpp")
file(GLOB HDR "src/*.h")

add_executable(hello-glfw ${SRC} ${HDR})
target_link_libraries(hello-glfw ${GLEW_LIBRARIES} ${GLFW3_LIBRARY} ${OPENGL_gl_LIBRARY} ${CPPFORMAT_LIBRARY})
set_property(TARGET hello-glfw PROPERTY CXX_STANDARD 11)
set_property(TARGET hello-glfw PROPERTY CXX_STANDARD_REQUIRED ON)

install(TARGETS hello-glfw RUNTIME DESTINATION bin)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION share)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
