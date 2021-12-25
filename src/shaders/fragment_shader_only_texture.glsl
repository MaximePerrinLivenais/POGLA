#version 430

out vec4 output_color;
in vec2 uv_coordinates;

uniform sampler2D texture_sampler1;

void main()
{
    output_color = texture(texture_sampler1, uv_coordinates);
}
