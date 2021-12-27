#version 450

layout(triangles) in;
layout(line_strip, max_vertices = 2) out;

in vec4 tes_normal[3];
in float tes_diffuse[3];
out float gs_diffuse;

void main()
{
    vec4 origin = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3;
    vec4 mean_normal = (tes_normal[0] + tes_normal[1] + tes_normal[2]) / 3;

    gs_diffuse = 1;
    gl_Position = origin;
    EmitVertex();

    gl_Position = origin + 0.1 * mean_normal;
    EmitVertex();

    EndPrimitive();
}
