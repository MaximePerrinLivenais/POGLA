#version 430

in vec4 vertex_color;
out vec4 fragColor;
void main()
{
    vec2 temp = gl_PointCoord - vec2(0.5);
    float f = dot(temp, temp);

    if (f > 0.25)
        discard;

    fragColor = vertex_color * (0.25 - f) * 4;
};
