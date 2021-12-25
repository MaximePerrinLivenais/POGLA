#version 450

layout (vertices = 16) out;

void main(void)
{
    if (gl_InvocationID == 0)
    {
        int tesselation_level = 12;

        gl_TessLevelOuter[0] = tesselation_level;
        gl_TessLevelOuter[1] = tesselation_level;
        gl_TessLevelOuter[2] = tesselation_level;
        gl_TessLevelOuter[3] = tesselation_level;

        gl_TessLevelInner[0] = tesselation_level;
        gl_TessLevelInner[1] = tesselation_level;
    }

    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}
