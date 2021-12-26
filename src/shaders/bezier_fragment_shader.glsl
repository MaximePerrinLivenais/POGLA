#version 450

uniform vec3 object_color;

in float diffuse;

out vec4 color;

void main(void)
{
    color = vec4(diffuse * object_color, 1.);
}
