#version 150

layout(location = 0) out vec4 fragcolor;

void main()
{
    if (gl_FrontFacing)
    {
        fragcolor = vec4(0.0, 0.5, 1.0, 1.0);
    }
    else
    {
        fragcolor = vec4(0.5, 0.5, 0.5, 1.0);
    }
}

