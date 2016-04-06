//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Camera.h
// Camera Object - position, up and lookat
//------------------------------------------------------------------------------

#ifndef __CAMERA_H__
#define __CAMERA_H__
#include <C:\SolarSystem\src\include\GL\glut.h>
#include "STMatrix4.h"
#include "STVector3.h"



class Camera
{

public:
                            Camera(void);
                            ~Camera(void);

					

    void                    Reset                                       (void);
    void                    ResetUp                                     (void);
    void                    SetUpAndRight                               (void);
    void                    Strafe                                      (float delta_x, float delta_y);
    void                    Zoom                                        (float delta_y);
    void                    Rotate                                      (float delta_x, float delta_y);
    void                    Orbit                                       (float q[4], float p1x, float p1y, float p2x, float p2y);


    STVector3               Position                                    (void);
    STVector3               LookAt                                      (void);
    STVector3               Up                                          (void);
    STVector3               Right                                       (void);
    void                    ToggleRotationMode                          (void);
    STMatrix4               GetProjectionMatrix                         (void);
    STMatrix4               GetViewMatrix                               (void);
    void                    SetProjectionMatrix                         (STMatrix4 m);
    void                    SetViewMatrix                               (STMatrix4 m);
	void					Screen_Rotate_Left_Right(void);
    void                    SetLookAt                                   (STVector3 lookat);
    void                    SetPosition                                 (STVector3 position);
    void                    SetUp                                       (STVector3 up);
	float p_ProjectToSphere(float r, float x, float y);
	void					Rotate_about_X(GLfloat Angle);
	void					Rotate_about_Y(GLfloat Angle);
	void					Rotate_about_Z(GLfloat Angle);

private:
    STVector3               m_Position;
    STVector3               m_LookAt; // view direction
    STVector3               m_Right;
    STVector3               m_Up;
    STMatrix4               m_MV; // view matrix
    STMatrix4               m_MP; // projection matrix
    float                   m_trackballsize;
    bool                    m_rotationMode;
	GLfloat					m_rotate_X; 
	GLfloat					m_rotate_Y; 
	GLfloat					m_rotate_Z;

    void                    Init                                        (void);

};


#endif //__CAMERA_H__

