
/* TO DO: Proj3_4 OpenGL implement envmap.frag
   Fill in your new shader
   Perform environment map texture lookup.

variable declarations 

Complete your main function here

void main()
{
    gl_FragColor = getEnvColor(Texture, Position);
}*/

varying vec3 Texture_Position;

layout (location = 0) out vec4 color;
uniform samplerCube Texture;

void main()
{
    gl_FragColor = getEnvColor(textureCube(Texture, Texture_Position), Position);	
}