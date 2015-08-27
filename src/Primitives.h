#ifndef HELLO_GLFW_PRIMITIVES_H
#define HELLO_GLFW_PRIMITIVES_H

#define GLEW_STATIC
#include <GL/glew.h>

void createTriangle(GLuint& vao, GLuint& count);
void createQuad(GLuint& vao, GLuint& count);

#endif
