//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Scene.cpp
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------



// GLEW
#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <c:/SolarSystem/src/include/GL/glut.h>
#endif

#include "Scene.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "Intersection.h"
#include "Surface.h"
#include "Light.h"
#include "Sphere.h"
#include "STMatrix4.h"
#include "STVector2.h"
#include "CameraNode.h"
#include "TransformNode.h"
#include "LightNode.h"
#include "GeometryNode.h"
#include "utilities.h"
#include "STVector3.h"



Scene::Scene(void)
    : m_background(RGBR_f(0, 0, 0, 1)),
      m_pCamera(NULL),
      m_renderMode(LAMBERTIAN),
      m_bHasManipulator (false),
      m_manipMotionType(MANIP_NONE), 
      m_activeManipGeom(AXIS_NONE)
 {
    m_pCamera = new Camera();
	Camera *Camera_1 = new Camera();
	//Camera_1->SetValue(POSITION, 2.2, 0.9, 3);


//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// Add initial node to the scene graph
// 1. Create a new CameraNode
// 2. Initialize the node with the camera
// 3. Create a TranfromNode for the camera based on the light position
// 4. Add the and the camera to the scene tree
//------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------
	
    InitManipMode();
}


Scene::~Scene()
{
}


void Scene::SetBackgroundColor(RGBR_f color)
{
    m_background = color;
}


RGBR_f Scene::GetBackgroundColor(void)
{
    return(m_background);
}


void Scene::AddLight(Light lightin)
{
    m_lights.push_back(lightin);
	// Light nodes not needed
//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// Add the light to the scene graph
// 1. Create a new LightNode
// 2. Initialize the node with the light
// 3. Create a TranfromNode for the light based on the light position
// 4. Add the TransfromNode and the light to the scene
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

}


void Scene::AddSurface(Surface *pSurfacein)
{

    m_surfaceList.push_back(pSurfacein);
	// Surface added in mainsrc_proj3_4.cpp
//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// Add the geometry to the scene graph
// 1. Create a new GeometryNode
// 2. Initialize the node with the surface
// 3. Create a TranfromNode for the surface based on the surface position
// 4. Add the and the surface to the scene
//------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
}


Camera *Scene::GetCamera(void)
{
    return(m_pCamera);
}



STVector3 Scene::GetLightDirection(void)
{
    STVector3 lightDirection;
    return(lightDirection);
}


int Scene::SelectClosest(IntersectionList *pIntersectionList, Intersection *pIntersection) 
{
    int numPoints = 0;
    return(numPoints);
}


int Scene::FindClosestIntersection(Ray ray, Intersection *pIntersection)
{
    int numPoints = 0;
    numPoints = FindIntersection(ray, pIntersection, false);
    return(numPoints);
}


int Scene::FindIntersection(Ray ray, Intersection *pIntersection, bool bAny)
{
    bool bFound = false;
    int numPoints = 0;
    IntersectionList intersectionList;
    SurfaceList::const_iterator iter = m_surfaceList.begin();
    SurfaceList::const_iterator end  = m_surfaceList.end();

    for (; iter != end; ++iter) {

    }
    return(numPoints);
}

void Scene::Clear(void)
{
    SurfaceList::iterator iter = m_surfaceList.begin();
    SurfaceList::iterator end  = m_surfaceList.end();

    for (; iter != end; ++iter) 
	{
        delete *iter;
        *iter = NULL;
    }

	m_surfaceList.clear();
}


STVector3 Scene::GetLightPosition(void)
{
    if(m_lights.size())
        return(m_lights[0].GetPosition());

    STVector3 p(10.0f, 15.0f, 10.0f);
    return(p);
}


void Scene::ToggleRenderMode(void)
{
    if(m_renderMode == NAVIGATION) {
        RemoveManip();
        InitManipMode();
        m_renderMode = ENVIRONMENTMAP;
    }
    else if(m_renderMode == ENVIRONMENTMAP) {
        m_renderMode = NAVIGATION;
        InitManipMode();
    }
}

void Scene::ToggleManipMode(void)
{
    if(m_renderMode == NAVIGATION) {
        m_modeQueue.push(m_modeQueue.front());
        m_modeQueue.pop();
    }
}

void Scene::ToggleManipGeometry(void)
{
    if((m_renderMode == NAVIGATION) && (m_bHasManipulator)){
        m_manipGeomQueue.push(m_manipGeomQueue.front());
        m_manipGeomQueue.pop();
    }
}

void Scene::InitManipMode(void)
{
    std::queue<ManipMode> empty;
    std::swap(m_modeQueue, empty);
    m_modeQueue.push(LOCAL);
    m_modeQueue.push(PARENT);
    m_modeQueue.push(NONE);

    InitManipGeometryMode();
    RemoveManip();
}


void Scene::InitManipGeometryMode(void)
{
    std::queue<ManipGeom> empty;
    std::swap(m_manipGeomQueue, empty);
    m_manipGeomQueue.push(AXIS_ALL);
    m_manipGeomQueue.push(AXIS_TRANSXYZ);
    m_manipGeomQueue.push(AXIS_ROTATIONALL);
}

 
void Scene::Translate(int axis, STMatrix4 viewProjection, SceneNode object, STVector2 prevMousePos, STVector2 curMousePos)
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); 	
	if (axis == AXIS_TRANSX)
	{
		float movement = (curMousePos.x - prevMousePos.x)* (curMousePos.x - prevMousePos.x);
		printf("\nMovement along axis of X\n");
		glTranslatef(movement,0, 0);

	}
	if (axis == AXIS_TRANSY)
	{
		float movement = curMousePos.x - prevMousePos.x;
		printf("\nMovement along axis of Y\n");
		glTranslatef(0, movement,0);

	}
	glPopMatrix();
}


void Scene::Rotate(int axis, STMatrix4 viewProjection, SceneNode object, STVector2 prevMousePos, STVector2 curMousePos)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	if (axis == AXIS_TRANSX)
	{
		float movement = curMousePos.x - prevMousePos.x;
		printf("\nRotation Axis about X with coordinates %f\n",curMousePos.x);
		glRotatef(90,movement, 0, 0);

	}
	if (axis == AXIS_TRANSY)
	{
		float movement = curMousePos.x - prevMousePos.x;
		printf("\nRotation Axis about Y with coordinates %f\n",curMousePos.y);
		glRotatef(90,0, movement, 0);

	}
	glPopMatrix();

    // TO DO: Proj3_4 OpenGL
    // Consider M - The object's transformation, T the adjustment
    // 1. Check which manipulation mode the program is in - the mode in the front of m_modeQueue
    // 2. For local mode - transform in the objects coordinate system, M = M * T
    // 3. For parent mode - transform in relation to the object's parent, M = T * M
    // 4. Formulate the transform along the axis by delta related to 
    //    the product of the difference in mouse positions and a constant term
    // 5. Make your manipulator move with the mouse position. 
    //    The point you press on should remain under the mouse as it moves
    //    Form a ray corresponding to the mouse click and 
    //    the line corresponding to the manipulation axis in world space
    //    Compute the t intervals along the axis that correspond to the mouse movement.
    //---------------------------------------------------------------------------------
	// Part  1, 4, 5 completed in mainsrc_proj3_4.cpp

    //--------------------------------------------------------------------------------------
}

void Scene::Spin(float QMat1[4], float QMat2[4], float QMat3[4])
{
    combineQ(QMat1, QMat2, QMat3);
    glutPostRedisplay();
}


// Propogates group transformations to child nodes
void Scene::PropogateTransforms(SceneNode *pNode)
{
    // TO DO: Proj3_4 OpenGL
    // Consider A - the Object's parent's world transform
    //          B - the Object's local transform
    // 1. Implement a recursive function that:
    // 2. for an Object that is not at the root
    //             sets m_worldT and m_worldInvT with the Object
    //             m_worldT should be set to AB
    //             m_worldIT should be set to transform the normal vectors
    // 3. Finally traverse the tree making a recursive call o each of the Object's children
    //----------------------------------------------------------------------------------


    //---------------------------------------------------------------------------------
}


void Scene::SetRenderMode (RenderMode mode)
{
    m_renderMode = mode;
}


RenderMode Scene::GetRenderMode (void)
{
    return(m_renderMode);
}


void Scene::AddManipulator(void)
{
  
    m_bHasManipulator = true;
}


bool Scene::RotatingManip(void)
{
    if   ( (RenderMode() == NAVIGATION)
        && (HasManipulator())
        && ((CurrentManipMode() == LOCAL) || (CurrentManipMode() == PARENT))
        && ((CurrentManipGeometryState() == AXIS_ALL) || 
            (CurrentManipGeometryState() == AXIS_ROTATIONALL))
        && ((CurrentManipMotion() == ROTATE_X) || 
            (CurrentManipMotion() == ROTATE_Y) || 
            (CurrentManipMotion() == ROTATE_Z) || 
            (CurrentManipMotion() == ROTATE_SCREEN) || 
            (CurrentManipMotion() == ROTATE_DUPLICATE)))
        return(true);

    return(false);
}


bool Scene::TranslatingManip(void)
{
    if   ( (RenderMode() == NAVIGATION)
        && (HasManipulator())
        && ((CurrentManipMode() == LOCAL) || (CurrentManipMode() == PARENT))
        && ((CurrentManipGeometryState() == AXIS_ALL) || 
            (CurrentManipGeometryState() == AXIS_TRANSXYZ))
        && ((CurrentManipMotion() == TRANS_YZ) || 
            (CurrentManipMotion() == TRANS_XZ) || 
            (CurrentManipMotion() == TRANS_XY) || 
            (CurrentManipMotion() == TRANS_X)  || 
            (CurrentManipMotion() == TRANS_Y)  ||
            (CurrentManipMotion() == TRANS_Z)))
        return(true);

    return(false);
}


bool Scene::HasManipulator(void)
{
    return(m_bHasManipulator);
}


bool Scene::SelectManipulator(int mouseX, int mouseY, int width, int height)
{
    double matModelView[16], matProjection[16]; 
    int viewport[4]; 
    double t = 0.0;
    STVector3 closestPt;
    bool bHit = false;

    glGetDoublev(GL_MODELVIEW_MATRIX, matModelView ); 
    glGetDoublev(GL_PROJECTION_MATRIX, matProjection ); 
    glGetIntegerv(GL_VIEWPORT, viewport ); 
	double winX = (double)mouseX; 
    double winY = viewport[3] - (double)mouseY; 

    GLdouble   m_startX, m_startY, m_startZ;
    GLdouble   m_endX,   m_endY,   m_endZ;

    gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
                 viewport, &m_startX, &m_startY, &m_startZ); 
    gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
                 viewport, &m_endX, &m_endY, &m_endZ); 

    ManipGeom selectedGeom;
    bHit = RayTestManip(STVector3(m_startX, m_startY, m_startZ), STVector3(m_endX, m_endY, m_endZ), &selectedGeom);
	if(bHit) 
	{
       SetActiveManipGeom(selectedGeom);
       ManipMotionType mtype = MapGeomToMotion(selectedGeom);
       SetCurrentManipMotion(mtype);
    }
    return(bHit);
}



void Scene::RemoveManip(void)
{
    m_bHasManipulator = false;
}

bool Scene::SelectObject(int mouseX, int mouseY, int width, int height, STPoint3 bspherecenter, float bsphereradius)
{

    double matModelView[16], matProjection[16]; 
    int viewport[4]; 
    double t = 0.0;
    STVector3 closestPt;
    bool bHit = false;

    glGetDoublev(GL_MODELVIEW_MATRIX, matModelView ); 
    glGetDoublev(GL_PROJECTION_MATRIX, matProjection ); 
    glGetIntegerv(GL_VIEWPORT, viewport ); 
    double winX = (double)mouseX; 
    double winY = viewport[3] - (double)mouseY; 

    GLdouble   m_startX, m_startY, m_startZ;
    GLdouble   m_endX,   m_endY,   m_endZ;

    gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
                 viewport, &m_startX, &m_startY, &m_startZ); 
    gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
                 viewport, &m_endX, &m_endY, &m_endZ); 

    STVector3 center(bspherecenter.x, bspherecenter.y, bspherecenter.z);
    bHit = RayTest(center, bsphereradius, center,
                   STVector3(m_startX, m_startY, m_startZ), 
                   STVector3(m_endX, m_endY, m_endZ),
                   &closestPt, &t);

    return(bHit);
}

// TO DO: Proj3_4 OpenGL
// map the geometry part to the motion
//    AXIS_ROTX    - ROTATE_X                
//    AXIS_ROTY    - ROTATE_Y               
//    AXIS_ROTZ    - ROTATE_Z              
//
//   AXIS_TRANSX   - TRANS_X                
//   AXIS_TRANSY   - TRANS_Y                 
//   AXIS_TRANSX    - TRANS_Z                 
//
//   AXIS_ROTSCREEN - ROTATE_SCREEN
//   AXIS_DUPLICATE - ROTATE_DUPLICATE
ManipMotionType  Scene::MapGeomToMotion(ManipGeom selectedGeom)
{
    ManipMotionType mType;

    switch(selectedGeom) {
        case AXIS_TRANSX: mType = TRANS_X; break;
		case AXIS_TRANSY: mType = TRANS_Y; break;
		case AXIS_TRANSZ: mType = TRANS_Z; break;
        default:mType = MANIP_NONE; break;
    }

    return(mType);
}


bool Scene::RayTestManip(STVector3 raystart, STVector3 rayend, ManipGeom *selectedGeom)
{
	// checking to which axis, X Y or Z is the point clicked by mouse is closest to and within threshold
	// so as to assign the corressponding axis of translation.
	int threshold = 1;

	if (raystart.z == 0)
	{
		if (raystart.x < raystart.y)
		{
			if (raystart.x < threshold)
				SetActiveManipGeom(AXIS_TRANSY); return true;
		}

		else
		{
			if (raystart.y < threshold)
				SetActiveManipGeom(AXIS_TRANSX); return true;
		}
	}

	if (raystart.x == 0)
	{
		if (raystart.z < raystart.y)
		{
			if (raystart.z < threshold)
				SetActiveManipGeom(AXIS_TRANSY); return true;
		}

		else
		{
			if (raystart.y < threshold)
				SetActiveManipGeom(AXIS_TRANSZ); return true;
		}
		
	}

	if (raystart.y == 0)
	{
		if (raystart.z < raystart.x)
		{
			if (raystart.z < threshold)
				SetActiveManipGeom(AXIS_TRANSX); return true;
		}

		else
		{
			if (raystart.x < threshold)
				SetActiveManipGeom(AXIS_TRANSZ); return true;
		}

	}
	return(false);
}

ManipMode Scene::CurrentManipMode(void)
{
    ManipMode mmanipmode = m_modeQueue.front();
    return (mmanipmode);
}

ManipGeom Scene::CurrentManipGeometryState(void)
{
    ManipGeom mmanipGeomState = m_manipGeomQueue.front();
    return (mmanipGeomState);
}


ManipMotionType Scene::CurrentManipMotion(void)
{
    return (m_manipMotionType);
}

void Scene::SetCurrentManipMotion(ManipMotionType mmotiontype)
{
    m_manipMotionType = mmotiontype;
}

ManipGeom Scene::GetActiveManipGeom(void)
{
    return (m_activeManipGeom);
}

void Scene::SetActiveManipGeom(ManipGeom mgeom)
{
    m_activeManipGeom = mgeom;
}



