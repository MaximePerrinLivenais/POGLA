#version 430

in vec3 color;
out vec4 output_color;

in vec2 uv_coordinates;

vec4 texture_color;

uniform sampler2D texture_sampler1;

void main()
{
    output_color = vec4(color, 1) * texture(texture_sampler1, uv_coordinates);
}
