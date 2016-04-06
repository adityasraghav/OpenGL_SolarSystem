/* reflectance.frag*/

/*
    TO DO: Proj3_4 OpenGL
    Write your reflectance fragment shader code here

*/

/* variable declarations */


/* add your main function here*/

#version 330 core
// Incoming surface normal and view-space position
in vec3 vs_fs_normal;
in vec3 vs_fs_position;
// Final fragment color
layout (location = 0) out vec4 color;
// The cube-map texture
uniform samplerCube tex;
void main(void)
{
// Calculate the texture coordinate by reflecting the

// view-space position around the surface normal.
vec3 tc = reflect(-vs_fs_position, normalize(vs_fs_normal));
// Sample the texture and color the resulting fragment
// a golden color.
color = vec4(0.3, 0.2, 0.1, 1.0) +
vec4(0.97, 0.83, 0.79, 0.0) *
texture(tex, tc);
}