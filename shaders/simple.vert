#version 150

in vec3 pos;
in vec3 color;
in vec3 normal;

out vec3 vertex_color;
out vec3 vertex_normal;

void main()
{
    vertex_color = color;
    vertex_normal = normal;

    gl_Position = vec4(pos, 1.0);
}

