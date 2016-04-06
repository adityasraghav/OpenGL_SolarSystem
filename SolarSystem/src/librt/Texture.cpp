#include "Texture.h"
#include <tchar.h>
#include <C:\SolarSystem\src\include\GL\glaux.h>
Texture::Texture(wchar_t* location)
{
	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad(location);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, texture1->sizeX, texture1->sizeY, GL_RGB, GL_UNSIGNED_BYTE, texture1->data); 
}

GLuint Texture::GetTexture()
{
	return texture;
}



