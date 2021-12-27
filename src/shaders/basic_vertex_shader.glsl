#version 450

in vec3 position;

uniform mat4 mvp_matrix;

void main(void)
{
    vec4 pos = mvp_matrix * vec4(position, 1);
    gl_Position =  pos;
    gl_PointSize = 3 * abs(1.0 - (pos.z / pos.w)) * 32.0;
}
