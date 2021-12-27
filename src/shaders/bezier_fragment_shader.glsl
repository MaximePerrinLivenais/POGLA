#version 450

uniform vec3 object_color;

in float gs_diffuse;

out vec4 color;

void main(void)
{
    color = vec4(gs_diffuse * object_color, 1.);
}
