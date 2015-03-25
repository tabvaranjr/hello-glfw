#version 150

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

in vec3 pos;
in vec3 color;
in vec3 normal;

out vec3 vertex_color;
out vec3 vertex_normal;

void main()
{
    vertex_color = color;
    vertex_normal = normal;

    gl_Position = proj * model * view * vec4(pos, 1.0);
}

