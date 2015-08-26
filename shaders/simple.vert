#version 150
#extension GL_ARB_explicit_attrib_location : require

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;

out vec3 vertex_color;
out vec3 vertex_normal;

void main()
{
    vertex_color = color;
    vertex_normal = normal;

    gl_Position = proj * model * view * vec4(pos, 1.0);
}

