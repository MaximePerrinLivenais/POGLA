#version 450

layout (quads, equal_spacing, ccw) in;

uniform mat4 mvp_matrix;

float[4] get_polynom(float param)
{
    float polynom[4];

    polynom[0] = (1. - param) * (1. - param) * (1. - param);
    polynom[1] = (1. - param) * (1. - param) * param * 3;
    polynom[2] = (1. - param) * param * param * 3;
    polynom[3] = param * param * param;

    return polynom;
}

vec3 compute_pos(float u_polynom[4], float v_polynom[4])
{
    int n = 4;
    int m = 4;

    vec3 pos = vec3(0, 0, 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            pos += u_polynom[i] * v_polynom[j] * gl_in[j * m + i].gl_Position.xyz;
    }

    return pos;
}

void main(void)
{
    float[] u_polynom = get_polynom(gl_TessCoord.x);
    float[] v_polynom = get_polynom(gl_TessCoord.y);

    gl_Position = mvp_matrix * vec4(compute_pos(u_polynom, v_polynom), 1.);
}
