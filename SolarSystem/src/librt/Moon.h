#ifndef MOON_H
#define MOON_H

#include <math.h>
#include <C:\SolarSystem\src\include\GL\glut.h>

class Moon
{
		float distanceFromEarth;
		float revolutionTime;
		float rotationTime;
		float radiusOfMoon;
		float position[3];
		float rotation;
		GLuint texture;

public:
	Moon(float distanceFromEarth, float revolutionTime, float rotationTime, float radiusOfMoon, GLuint texture);
	void calculateMoonPosition(float time);
	void render(void);
	void renderOrbit(void);
	void drawVertex(void);
	void propertyMoonQuadric(GLUquadricObj* moonQuadric);
	void movementOfMoon(void);
};

#endif
