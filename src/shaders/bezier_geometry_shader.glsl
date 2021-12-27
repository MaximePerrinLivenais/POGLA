#version 450

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in float tes_diffuse[3];
out float gs_diffuse;

void main()
{
    gl_Position = gl_in[0].gl_Position;
    gs_diffuse = tes_diffuse[0];
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    gs_diffuse = tes_diffuse[1];
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    gs_diffuse = tes_diffuse[2];
    EmitVertex();

    EndPrimitive();
}
