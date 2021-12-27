#version 450

uniform vec3 object_color;

in float gs_diffuse;
in float gs_specular;

out vec4 color;

void main(void)
{
    color = clamp(vec4(gs_diffuse * object_color, 1.) + gs_specular * vec4(1.), 0., 1.);
}
