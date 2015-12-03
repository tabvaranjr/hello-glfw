#ifndef HELLO_GLFW_DEMO_H
#define HELLO_GLFW_DEMO_H

#include <memory>

#include "Mesh.h"
#include "ShaderProgram.h"

std::shared_ptr<ShaderProgram> makeShaderProgram(const std::string& program);

std::shared_ptr<Mesh> makeQuad();

#endif
