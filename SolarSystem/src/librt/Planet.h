#ifndef PLANET_H
#define PLANET_H

#include <math.h>
#include <vector>
using namespace std;
#include <C:\SolarSystem\src\include\GL\glut.h>
#include "STVector3.h"
#include "Moon.h"

class Planet
{
	float distanceFromSun;
	float revolutionTime;
	float rotationTime;
	float radiusOfPlanet;
	STVector3 positionOfPlanet; 
	float rotation;
	GLuint texture;
	vector<Moon> moons;

public:
	Planet(float distanceFromSun, float revolutionTime, float rotationTime, float radiusOfPlanet, GLuint texture);
	void calculatePosition(float time);
	void calculateMoonPosition(float time);
	void drawPlanet(void);
	void drawOrbit(void);
	void rotatePlanet(void);
	void translatePlanet(void);
	void drawSphere(GLUquadricObj* planetQuadric);
	void drawSun(GLUquadricObj* planetQuadric);
	void drawPlanetSphere(GLUquadricObj* planetQuadric);
	void drawSpace(GLUquadricObj* planetQuadric);
	void drawVertex(void);
	void propertyQuadric(GLUquadricObj* planetQuadric);
	void getPosition(float* vec);
	float getRadius(void);
	void addPlanetRing();
	void addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint texture);

};
#endif