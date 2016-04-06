#include "Planet.h"
#include "defs.h"
float scalePlanet = .00007f;
Planet::Planet(float distanceFromSun, float revolutionTime, float rotationTime, float radiusOfPlanet, GLuint texture)
{
	this->distanceFromSun = distanceFromSun;
	this->revolutionTime = revolutionTime;
	this->rotationTime = rotationTime;
	this->radiusOfPlanet = radiusOfPlanet;
	this->texture = texture;
}

void Planet::calculatePosition(float time)
{
	positionOfPlanet.x = sin(time * PI / revolutionTime) * distanceFromSun;
	positionOfPlanet.y = cos(time * PI / revolutionTime) * distanceFromSun * 1.5f;
	positionOfPlanet.z = 0;
	rotation = time * 360 / rotationTime;
	calculateMoonPosition(time);
}

void Planet::calculateMoonPosition(float time)
{
	for (int i = 0; i < moons.size(); i++)
		moons[i].calculateMoonPosition(time);
}

void Planet::drawPlanet(void)
{
	glPushMatrix();
	glTranslatef(positionOfPlanet.x * distanceScale, positionOfPlanet.y * distanceScale, positionOfPlanet.z * distanceScale);
	for (int i = 0; i < moons.size(); i++) {
		moons[i].render();
	}
	rotatePlanet();
	glBindTexture(GL_TEXTURE_2D, texture);
	GLUquadricObj* planetQuadric = gluNewQuadric();
	propertyQuadric(planetQuadric);
	drawSphere(planetQuadric);
	glPopMatrix();
}

void Planet::propertyQuadric(GLUquadricObj* planetQuadric)
{
	gluQuadricTexture(planetQuadric, true);
	gluQuadricNormals(planetQuadric, GLU_SMOOTH);
}

void Planet::rotatePlanet(void)
{
	if (distanceFromSun > 0.005f)
	glRotatef(rotation, 0.0f, 0.0f, 1.0f);
}

void Planet::drawSphere(GLUquadricObj* planetQuadric)
{
	if (distanceFromSun < -5.0f)
		drawSpace(planetQuadric);

	else if (distanceFromSun < 0.001f && distanceFromSun > -1.0f)
		drawSun(planetQuadric);
	
	else
		drawPlanetSphere(planetQuadric);
}

void Planet::drawSun(GLUquadricObj* planetQuadric)
{
	float finalRadius = radiusOfPlanet * scalePlanet;
	if (finalRadius > 0.5f)
	finalRadius = 1.0f;
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	gluSphere(planetQuadric, finalRadius, 60, 60);
	glEnable(GL_LIGHTING); // Shading on planet while revolution
	glEnable(GL_LIGHT0); // Light from sun falling on planet
}

void Planet::drawSpace(GLUquadricObj* planetQuadric)
{
	float finalRadius = radiusOfPlanet * scalePlanet;
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	gluSphere(planetQuadric, finalRadius, 60, 60);
	glEnable(GL_LIGHTING); // Shading on planet while revolution
	glEnable(GL_LIGHT0); // Light from sun falling on planet
}

void Planet::drawPlanetSphere(GLUquadricObj* planetQuadric)
{
	gluSphere(planetQuadric, radiusOfPlanet * scalePlanet, 60, 60); //glutsolidsphere

	if (radiusOfPlanet == 36184)
	{
		//gluDisk(planetQuadric, 45000 * scalePlanet, 90000 * scalePlanet, 60, 60);
		//glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		gluDisk(planetQuadric, 45000 * scalePlanet, 90000 * scalePlanet, 60, 60);
		glEnable(GL_LIGHTING); // Shading on planet while revolution
		//glEnable(GL_LIGHT0); // Light from sun falling on planet
	}

}

void Planet::addMoon(float distanceFromEarth, float revolutionTime, float rotationTime, float radiusOfMoon, GLuint texture)
{
	moons.push_back(Moon(distanceFromEarth, revolutionTime, rotationTime, radiusOfMoon, texture));
}

void Planet::addPlanetRing()
{
	GLUquadricObj* ringQuadric = gluNewQuadric();
	propertyQuadric(ringQuadric);
	gluDisk(ringQuadric, 40000, 70000, 60, 60);
}
void Planet::drawOrbit(void)
{
	glBegin(GL_LINE_STRIP);
	drawVertex();
	glEnd();
	translatePlanet();
}

void Planet::drawVertex(void)
{
	for (float angle = 0.0f; angle < 2 * PI; angle += 0.05f)
	{
			glVertex3f(sin(angle) * distanceFromSun * distanceScale, cos(angle) * distanceFromSun * distanceScale * 1.5f, 0.0f);
	}
	glVertex3f(0.0f, distanceFromSun * distanceScale * 1.5f, 0.0f);
}
void Planet::translatePlanet(void)
{
	glPushMatrix();
	glTranslatef(positionOfPlanet.x * distanceScale, positionOfPlanet.y * distanceScale, (positionOfPlanet.z * distanceScale));
	for (int i = 0; i < moons.size(); i++) 
		moons[i].renderOrbit();
	glPopMatrix();
}

void Planet::getPosition(float* vec) 
{
	vec[0] = positionOfPlanet.x * distanceScale;
	vec[1] = positionOfPlanet.y * distanceScale;
	vec[2] = positionOfPlanet.z * distanceScale;
}

float Planet::getRadius(void) 
{
	return radiusOfPlanet;
}

