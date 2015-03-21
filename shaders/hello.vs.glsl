#version 150

in vec3 pos;
in vec3 color;

out vec3 vertex_color;

void main()
{
    vertex_color = color;

    gl_Position = vec4(pos, 1.0);
}

