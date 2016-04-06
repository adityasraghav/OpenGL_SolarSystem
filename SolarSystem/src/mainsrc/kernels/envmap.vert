#version 330 
/* TO DO: Proj3_4 OpenGL implement envmap.vert
   Complete skybox implementation.
*/



layout(location = 0) in vec3 Vertex;

uniform mat4 Mat_VP;

varying vec3 Texture_Position;
out vec3 Position;

void main(void)
{

Texture_Position = gl_vertex.xyz;

Texture_Position = Vertex;
Position = Mat_VP * vec4(Vertex, 1.0);
}