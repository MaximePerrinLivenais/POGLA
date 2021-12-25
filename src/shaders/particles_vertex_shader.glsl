#version 430

in vec3 vertex_position;
in vec3 position;
in vec4 color;
in float size;

out vec4 vertex_color;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

void main()
{
   vec4 pos = proj_matrix * view_matrix * vec4(position, 1);
   gl_Position =  pos;
   gl_PointSize = size * abs(1.0 - (pos.z / pos.w)) * 32.0;

   vertex_color = color;
};
