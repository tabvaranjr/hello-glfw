#version 150

in vec3 color;
in vec3 normal;

out vec4 fragcolor;

void main()
{
    if (gl_FrontFacing)
    {
        fragcolor = vec4(color, 1.0);
    }
    else
    {
        fragcolor = vec4(0.5, 0.5, 0.5, 1.0);
    }
}

