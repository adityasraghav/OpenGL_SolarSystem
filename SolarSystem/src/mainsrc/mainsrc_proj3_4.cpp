#include "C:\SolarSystem\src\librt\SolarSystem.h"
#include "C:\SolarSystem\src\librt\Texture.h"
#include "Camera.h"
#include <C:\SolarSystem\src\include\GL\glut.h>
#include "defs.h"

Camera cam;
int gWindowSizeX, gWindowSizeY;
SolarSystem solarSystem;
double realTime = 1;
double realTimeIncrement = 0.1;
int gPreviousMouseX = -1;
int gPreviousMouseY = -1;
int gMouseButton = -1;
bool help = TRUE;
bool skybox = TRUE;
bool particlesys = FALSE;
void timer(int) 
{
	glutPostRedisplay(); 
	glutTimerFunc(10, timer, 0); 
}

struct Particle
{
	STVector3 pos, speed, accleration, force;
	float size, angle, weight, d, time = 1;
	float life = 10000000; // Remaining life of the particle. if < 0 : dead and unused.
	
};
const int MaxParticles = 200;
int LastUsedParticle = 0;
Particle ParticlesContainer[MaxParticles];
float factor = 0.1;
int drawAsteroid()
{

	// Finds a Particle in ParticlesContainer which isn't used yet.
	// (i.e. life < 0);
	if (LastUsedParticle < MaxParticles){
		
		for (int i = LastUsedParticle; i<MaxParticles; i++){
		
		if (ParticlesContainer[i].life > 0){
			
			Particle& p = ParticlesContainer[i];
	
			p.speed.x = rand() % 1000 + 100;
			p.speed.y = 200000000 + (10000000 * factor);
			p.size = rand() % 1000 + 1000;
			p.life = rand() % 1000000 + 10000;
			
			factor += 0.1;
			p.pos.x = sin(realTime / (365 + p.speed.x)) * (p.speed.y);
			p.pos.y = cos(realTime / (365 + p.speed.x)) * (p.speed.y) * 1.5f;
			p.pos.z = 0;
			glPushMatrix();
			glTranslatef(p.pos.x * distanceScale, p.pos.y * distanceScale, p.pos.z * distanceScale);
			GLUquadricObj* planetQuadric = gluNewQuadric();
			gluQuadricNormals(planetQuadric, GLU_FLAT);
			gluSphere(planetQuadric, p.size * scalePlanet, 10, 10);
			glPopMatrix();
			LastUsedParticle++;
		}
	}

	}
	return 0; // All particles are taken, override the first one
}
void mainAsteroid()
{
	int ParticlesCount = 0,fac =1;
	for (int i = 0; i<MaxParticles; i++){

		Particle& p = ParticlesContainer[i]; // shortcut

		if (p.life > 0.0f){

			// Decrease life
			p.life -= 2;
			if (p.life == 0 || p.size <= 10)
			{
				LastUsedParticle--;
			}
			if (p.life > 0.0f && p.size > 10){
				factor = 0;
				p.pos.x = sin((realTime * p.time)* PI / (365 + p.speed.x)) * (p.speed.y);
				p.pos.y = cos((realTime * p.time)* PI / (365 + p.speed.x)) * (p.speed.y) * 1.5f;
				p.pos.z = 0;
				glPushMatrix();
				if (realTime >= 1000){
				for (int j = i+1; j < MaxParticles; j++)
				{
					Particle& q = ParticlesContainer[j];
					if( abs(p.pos.x - q.pos.x) <= 20000000 && abs(p.pos.y - q.pos.y) <= 20000000 )
					{
						
						if (p.speed.x > q.speed.x)
						{
							p.time = -0.1 ;
							p.size = p.size / 2;
						}
						
					}

				}
				}
				glTranslatef(p.pos.x * distanceScale, p.pos.y * distanceScale, p.pos.z * distanceScale);
				GLUquadricObj* planetQuadric = gluNewQuadric();
				gluQuadricNormals(planetQuadric, GLU_FLAT);
				gluSphere(planetQuadric, p.size * scalePlanet, 10, 10);
				glPopMatrix();
			}


		}
	}

}


void addTexture(void)
{
	Texture* sun = new Texture(L"../../data/scenes/textures/sun.bmp");
	Texture* mercury = new Texture(L"../../data/scenes/textures/mercury.bmp");
	Texture* venus = new Texture(L"../../data/scenes/textures/venus.bmp");
	Texture* earth = new Texture(L"../../data/scenes/textures/earth.bmp");
	Texture* mars = new Texture(L"../../data/scenes/textures/mars.bmp");
	Texture* jupiter = new Texture(L"../../data/scenes/textures/jupiter.bmp");
	Texture* saturn = new Texture(L"../../data/scenes/textures/saturn.bmp");
	Texture* uranus = new Texture(L"../../data/scenes/textures/uranus.bmp");
	Texture* neptune = new Texture(L"../../data/scenes/textures/neptune.bmp");
	Texture* ring = new Texture(L"../../data/scenes/textures/saturnring.bmp");
	Texture* moon = new Texture(L"../../data/scenes/textures/moon.bmp");
	Texture* pluto = new Texture(L"../../data/scenes/textures/pluto.bmp");

	solarSystem.addPlanet(0, 1, 500, 432474, sun->GetTexture()); // sun
	solarSystem.addPlanet(42666716, 88, 5865, 1516, mercury->GetTexture()); // mercury
	solarSystem.addPlanet(67240000, 225, -24302, 3760, venus->GetTexture()); // venus
	solarSystem.addPlanet(92960000, 365, 100, 3959, earth->GetTexture()); // earth
	solarSystem.addPlanet(140000000, 687, 101.5f, 2106, mars->GetTexture()); // mars
	solarSystem.addPlanet(483800000, 4380, 42.0f, 43441, jupiter->GetTexture()); // jupiter
	solarSystem.addPlanet(890700000, 10585, 44.0, 36184, saturn->GetTexture()); // saturn
	solarSystem.addPlanet(1783939400, 30660, 71.833, 15759, uranus->GetTexture()); // uranus
	solarSystem.addPlanet(2795084800, 60225, 66.53, 15299, neptune->GetTexture()); // neptune
	solarSystem.addPlanet(3670050000, 90520, 66.53, 15299, neptune->GetTexture()); // pluto
	solarSystem.addMoon(3, 320000 * 70, 27.3, 27.3, 1738, moon->GetTexture()); // test moon for the earth
	solarSystem.addPlanet(890800000, 10585, 44.0, 36184, ring->GetTexture()); // ring of saturn


}

void init(void) 
{
	glShadeModel(GL_SMOOTH);  // For smooth shading - Goraud Shading, phong sh
 	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	addTexture();
	timer(0);
}

void drawCube(void)
{
	glBegin(GL_QUADS);
	// new face
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-100.0f, -100.0f, 100.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(100.0f, -100.0f, 100.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-100.0f, 100.0f, 100.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(100.0f, 100.0f, -100.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(100.0f, -100.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(100.0f, -100.0f, 100.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(100.0f, 100.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(-100.0f, 100.0f, -100.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(-100.0f, -100.0f, -100.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(100.0f, -100.0f, -100.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-100.0f, -100.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(-100.0f, -100.0f, 100.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(-100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-100.0f, 100.0f, -100.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-100.0f, 100.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(100.0f, 100.0f, -100.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(100.0f, 100.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-100.0f, 100.0f, 100.0f);
	// new face
	glTexCoord2f(0.0f, 0.0f);   glVertex3f(-100.0f, -100.0f, -100.0f);
	glTexCoord2f(1.0f, 0.0f);   glVertex3f(100.0f, -100.0f, -100.0f);
	glTexCoord2f(1.0f, 1.0f);   glVertex3f(100.0f, -100.0f, 100.0f);
	glTexCoord2f(0.0f, 1.0f);   glVertex3f(-100.0f, -100.0f, 100.0f);

	glEnd();
}

void DisplayCallback(void) 
{



	realTime = realTime + realTimeIncrement;
	solarSystem.calculatePositions(realTime);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (float)gWindowSizeX / (float)gWindowSizeY, 0.1f, 10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	cam.Screen_Rotate_Left_Right();
	if (skybox){
		Texture* space = new Texture(L"../../data/scenes/textures/str1.bmp");
		glBindTexture(GL_TEXTURE_2D, space->GetTexture());
		glDisable(GL_DEPTH_TEST);
		drawCube();
	}
	GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	solarSystem.render();
	glDisable(GL_LIGHTING);

	solarSystem.renderOrbits();
	if (particlesys){
		drawAsteroid();
		mainAsteroid();
		glDisable(GL_DEPTH_TEST);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/*Texture* menu = new Texture(L"../../data/scenes/textures/help.bmp");
	glBindTexture(GL_TEXTURE_2D, menu->GetTexture());
	*/
	if (help == TRUE)
	{
	Texture* menu = new Texture(L"../../data/scenes/textures/help.bmp");
	glBindTexture(GL_TEXTURE_2D, menu->GetTexture());
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);	glVertex2f(0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f);	glVertex2f(1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f);	glVertex2f(1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);	glVertex2f(0.0f, 1.0f);
		glEnd();
	}
	glFlush();
	glutSwapBuffers();





}

void ReshapeCallback(int w, int h) 
{
	gWindowSizeX = w;
	gWindowSizeY = h;
	glViewport(0, 0, gWindowSizeX, gWindowSizeY);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspectRatio = (float)gWindowSizeX / (float)gWindowSizeY;
	gluPerspective(90.0f, aspectRatio, 0.001f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SpecialKeyCallback(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		cam.Strafe(10, 0);
		break;
	case GLUT_KEY_RIGHT:
		cam.Strafe(-10, 0);
		break;
	case GLUT_KEY_DOWN:
		cam.Strafe(0, -10);
		break;
	case GLUT_KEY_UP:
		cam.Strafe(0, 10);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}


void KeyCallback(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
		exit(0);
		break;
	case 'a':
		cam.Rotate_about_Y(.1);
		DisplayCallback();
		break;
	case 'd':
		cam.Rotate_about_Y(-0.1);
		DisplayCallback();
		break;
	case 'w':
		cam.Zoom(0.1);
		DisplayCallback();
		break;
	case 's':
		cam.Zoom(-0.1);
		DisplayCallback();
		break;
	case 'y':
		cam.Rotate_about_X(0.1);
		DisplayCallback();
		break;
	case 'h':
		cam.Rotate_about_X(-0.1);
		DisplayCallback();
		break;
	case 'c':
		cam.Strafe(-1, 0);
		DisplayCallback();
		break;
	case 'v':
		cam.Strafe(1, 0);
		DisplayCallback();
		break;
	case 'l':
		cam.Rotate_about_Z(-0.1);
		DisplayCallback();
		break;
	case 'j':
		cam.Rotate_about_Z(0.1);
		DisplayCallback();
		break;
	case '+':
		realTimeIncrement = realTimeIncrement + 0.1;
		realTime = realTime + realTimeIncrement;
		break;
	case '-':
		realTimeIncrement = realTimeIncrement - 0.1;
		realTime = realTime + realTimeIncrement;
		break;
	case 'r':
		cam.Reset();
		break;
	case '[':
		realTimeIncrement = 0;
		break;
	case ']':
		realTimeIncrement = 0.2;
		break;
	case 'p':
		realTimeIncrement = 0.1;
		realTime = 0;
		break;
	case 'm':
		if (help)
			help = FALSE;
		else
			help = TRUE;
		break;
	case 'x':
		if (skybox)
			skybox = FALSE;
		else
			skybox = TRUE;
		break;
	case '1':
		if (particlesys)
			particlesys = FALSE;
		else
			particlesys = TRUE;
		break;
	}
}
void MouseCallback(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON || button == GLUT_RIGHT_BUTTON || button == GLUT_MIDDLE_BUTTON)
		gMouseButton = button;
	else
		gMouseButton = -1;

	if (state == GLUT_UP)
	{
		gPreviousMouseX = -1;
		gPreviousMouseY = -1;
	}
}

void MouseMotionCallback(int x, int y)
{
	if (gPreviousMouseX >= 0 && gPreviousMouseY >= 0)
	{
		float deltaX = x - gPreviousMouseX;
		float deltaY = y - gPreviousMouseY;
		gPreviousMouseX = x;
		gPreviousMouseY = y;

		if (gMouseButton == GLUT_LEFT_BUTTON)
			cam.Rotate(deltaX, deltaY);
		else if (gMouseButton == GLUT_MIDDLE_BUTTON)
			cam.Strafe(deltaX, deltaY);
		else if (gMouseButton == GLUT_RIGHT_BUTTON)
			cam.Zoom(deltaY);
	}
	else
	{
		gPreviousMouseX = x;
		gPreviousMouseY = y;
	}

}

int main(int argc, char** argv)
{
	cam.Reset();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1920, 1080);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutSpecialFunc(SpecialKeyCallback);
	glutKeyboardFunc(KeyCallback);
	glutMouseFunc(MouseCallback);
	glutMotionFunc(MouseMotionCallback);
	glutMainLoop();
	glutIdleFunc(DisplayCallback);

	return 0;
}