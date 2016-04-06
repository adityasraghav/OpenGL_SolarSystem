#include "Moon.h"
#include <cmath>
#include "defs.h"

Moon::Moon(float distanceFromEarth, float revolutionTime, float rotationTime, float radiusOfMoon, GLuint texture){
	this->distanceFromEarth = distanceFromEarth;
	this->revolutionTime = revolutionTime;
	this->rotationTime = rotationTime;
	this->radiusOfMoon = radiusOfMoon;
	this->texture = texture;
}

void Moon::calculateMoonPosition(float time)
{
	float angle = time *  PI / revolutionTime;
	position[0] = sin(angle) * distanceFromEarth;
	position[1] = cos(angle) * distanceFromEarth;
	position[2] = 0;
	rotation = time * 360 / rotationTime;
}

void Moon::render(void)
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture);
	movementOfMoon();
	GLUquadricObj* moonQuadric = gluNewQuadric();
	propertyMoonQuadric(moonQuadric);
	glPopMatrix();
}

void Moon::movementOfMoon(void)
{
	glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
	glRotatef(-rotation, 0.0f, 0.0f, 1.0f);
}

void Moon::propertyMoonQuadric(GLUquadricObj* moonQuadric)
{
	gluQuadricTexture(moonQuadric, true);
	gluQuadricNormals(moonQuadric, GLU_SMOOTH);
	gluSphere(moonQuadric, radiusOfMoon * scalePlanet, 60, 60);
}


void Moon::renderOrbit(void){
	glBegin(GL_LINE_STRIP);
	drawVertex();
	glEnd();
}

void Moon::drawVertex(void)
{
	for (float angle = 0.0f; angle < 6.283185307f; angle += 0.1f)
		glVertex3f(sin(angle) * distanceFromEarth * distanceScale, cos(angle) * distanceFromEarth * distanceScale, 0.0f);
	glVertex3f(0.0f, distanceFromEarth * distanceScale, 0.0f);
}
