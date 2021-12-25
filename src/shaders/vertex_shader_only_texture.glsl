#version 430

layout (location = 0) in vec3 vPosition;
layout (location = 3) in vec2 vertex_uv;

uniform mat4 mvp_matrix;

out vec2 uv_coordinates;

void main()
{
    gl_Position = mvp_matrix * vec4(vPosition, 1.0);

    uv_coordinates = vertex_uv;
}
