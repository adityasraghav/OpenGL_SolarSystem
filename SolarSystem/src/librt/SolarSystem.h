#ifndef SOLAR_SYSTEM_H
#define SOLAR_SYSTEM_H

#include <vector>
#include "Planet.h"
#include "Lists.h"
using namespace std;

class SolarSystem
{
	PlanetList planets;

public:
	SolarSystem();

	void calculatePositions(float time);

	void addPlanet(float distanceFromSun, float revolutionTime, float rotationTime, float radiusOfPlanet, GLuint texture);

	void addMoon(int planetIndex, float distanceFromPlanet, float revolutionTime, float rotationTime, float radiusOfPlanet, GLuint texture);

	void render();

	void renderOrbits();

	void getPlanetPosition(int index, float* vec);

	float getRadiusOfPlanet(int index);
};

#endif