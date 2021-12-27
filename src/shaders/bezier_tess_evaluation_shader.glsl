#version 450

layout (quads, equal_spacing, ccw) in;

out vec4 tes_normal;
out float tes_diffuse;

uniform mat4 mvp_matrix;

struct Vertex
{
    vec3 position;
    vec3 normal;
};

float[4] get_polynom(float param)
{
    float polynom[4];

    polynom[0] = (1. - param) * (1. - param) * (1. - param);
    polynom[1] = (1. - param) * (1. - param) * param * 3;
    polynom[2] = (1. - param) * param * param * 3;
    polynom[3] = param * param * param;

    return polynom;
}

float[4] get_derivate(float param)
{
    float derivates[4];

    derivates[0] = -3. * (1. - param) * (1. - param);
    derivates[1] = 3. * (1. - param) * (1. - param) - 6. * param * (1. - param);
    derivates[2] = 6. * param * (1. - param) - 3. * param * param;
    derivates[3] = 3 * param * param;

    return derivates;
}

Vertex compute_output_vertex(float u, float v)
{
    int level = 4;

    float[] u_polynom = get_polynom(u);
    float[] v_polynom = get_polynom(v);

    float[] u_derivate = get_derivate(u);
    float[] v_derivate = get_derivate(v);

    vec3 pos = vec3(0, 0, 0);
    vec3 u_tangent = vec3(0, 0, 0);
    vec3 v_tangent = vec3(0, 0, 0);

    for (int i = 0; i < level; i++)
    {
        for (int j = 0; j < level; j++)
        {
            vec3 u_control_point = gl_in[i * level + j].gl_Position.xyz;
            //vec3 v_control_point = gl_in[j * level + i].gl_Position.xyz;

            pos += u_polynom[i] * v_polynom[j] * u_control_point;
            u_tangent += u_derivate[i] * v_polynom[j] * u_control_point;
            v_tangent += u_polynom[i] * v_derivate[j] * u_control_point;
        }
    }

    vec3 normal = cross(u_tangent, v_tangent);

    return Vertex(pos, normal);
}

float get_diffuse(vec3 light_pos, Vertex vertex)
{
    vec3 normal = normalize(vertex.normal);
    vec3 light_dir = normalize(light_pos - vertex.position);
    return clamp(dot(normal, light_dir), 0., 1.);
}

void main(void)
{
    float[] u_polynom = get_polynom(gl_TessCoord.x);
    float[] v_polynom = get_polynom(gl_TessCoord.y);

    Vertex vertex = compute_output_vertex(gl_TessCoord.x, gl_TessCoord.y);

    gl_Position = mvp_matrix * vec4(vertex.position, 1.);

    vec3 light_pos = vec3(20, 50, 20);
    tes_diffuse = get_diffuse(light_pos, vertex);
    tes_normal = vec4(vertex.normal, 1);
}
