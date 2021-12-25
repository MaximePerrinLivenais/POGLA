#version 430

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 3) in vec2 vertex_uv;

uniform mat4 mvp_matrix;

uniform vec3 camera_position;
uniform vec3 object_color;

uniform float diffuse;
uniform float specular;

out vec3 color;
out float coef;

out vec2 uv_coordinates;

void main()
{
    vec3 l_pos = vec3(10, 30, 10);

    vec3 light_dir = normalize(l_pos - vPosition);
    vec3 camera_dir = normalize(vPosition - camera_position);

    vec3 reflected_dir = reflect(light_dir, vNormal);

    float coef_diffuse = dot(normalize(vNormal), light_dir);
    float coef_specular = clamp(dot(camera_dir, reflected_dir), 0, 1);

    coef_diffuse = clamp(coef_diffuse, 0, 1);

    gl_Position = mvp_matrix * vec4(vPosition, 1.0);

    uv_coordinates = vertex_uv;

    color = diffuse * object_color * coef_diffuse +
            specular * vec3(1, 1, 1) * pow(coef_specular, 5);
}
