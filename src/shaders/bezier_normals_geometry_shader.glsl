#version 450

uniform mat4 mvp_matrix;

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in vec4 tes_normal[3];
in float tes_diffuse[3];
in float tes_specular[3];
out float gs_diffuse;
out float gs_specular;

void emit_vertices_normal()
{
    for (int index = 0; index < 3; index++)
    {
        gl_Position = gl_in[index].gl_Position;
        EmitVertex();

        gl_Position += normalize(mvp_matrix * tes_normal[index]);
        EmitVertex();
        EndPrimitive();
    }
}

void main()
{
    gs_diffuse = 0.;
    gs_specular = 0.;
    emit_vertices_normal();
}
