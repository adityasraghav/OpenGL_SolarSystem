#include "SolarSystem.h"

SolarSystem::SolarSystem(void) {

}

void SolarSystem::calculatePositions(float time)
{
	for (int i = 0; i < planets.size(); i++) 
		planets[i].calculatePosition(time);
}

void SolarSystem::addPlanet(float distanceFromSun, float revolutionTime, float rotationTime, float radiusOfPlanet, GLuint texture)
{
	planets.push_back(Planet(distanceFromSun, revolutionTime, rotationTime, radiusOfPlanet, texture));
}

void SolarSystem::addMoon(int planetIndex, float distanceFromEarth, float revolutionTime, float rotationTime, float radiusOfMoon, GLuint texture)
{
	planets[planetIndex].addMoon(distanceFromEarth, revolutionTime, rotationTime, radiusOfMoon, texture);
}
void SolarSystem::render()
{
	for (int i = 0; i < planets.size(); i++) 
		planets[i].drawPlanet();
}

void SolarSystem::renderOrbits()
{
	for (int i = 0; i < planets.size(); i++) 
		planets[i].drawOrbit();
}

void SolarSystem::getPlanetPosition(int index, float* vec)
{
	planets[index].getPosition(vec);
}

float SolarSystem::getRadiusOfPlanet(int index)
{
	return planets[index].getRadius();
}
