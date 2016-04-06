#ifndef TEXTURE_H
#define TEXTURE_H

#include <C:\SolarSystem\src\include\GL\glaux.h>
#include <C:\SolarSystem\src\include\GL\glut.h>


class Texture
{
	GLuint	texture;
public:
	Texture(wchar_t* path);

	GLuint GetTexture();

};
#endif 



