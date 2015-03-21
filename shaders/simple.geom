#version 150

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 vertex_color[];
in vec3 vertex_normal[];

out vec3 color;
out vec3 normal;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    color = vertex_color[0];
    normal = vertex_normal[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    color = vertex_color[1];
    normal = vertex_normal[1];
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    color = vertex_color[2];
    normal = vertex_normal[2];
    EmitVertex();
}

