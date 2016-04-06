/* reflectance.vert */
/*
    TO DO: Proj3_4 OpenGL
    Write your reflectance vertex shader code here

*/



/* variable declarations */


/* Add your main function here*/


#version 330 core

in vec3 vs_fs_normal;
in vec3 vs_fs_position;

layout (location = 0) out vec4 color;

uniform samplerCube SkyBoxTexture;
void main(void)
{

vec3 tc = reflect(-vs_fs_position, normalize(vs_fs_normal));

color = vec4(0.3, 0.2, 0.1, 1.0) +
vec4(0.97, 0.83, 0.79, 0.0) *
texture(SkyBoxTexture, tc);
}

// Incoming position and normal
layout (location = 0) in vec4 in_position;
layout (location = 1) in vec3 in_normal;
// Outgoing surface normal and view-space position
out vec3 vs_fs_normal;
out vec3 vs_fs_position;
// Model-view-projection and model-view matrices
uniform mat4 mat_mvp;
uniform mat4 mat_mv;
void main(void)
{
// Clip-space position
gl_Position = mat_mvp * in_position;
// View-space normal and position
vs_fs_normal = mat3(mat_mv) * in_normal;
vs_fs_position = (mat_mv * in_position).xyz;
}



