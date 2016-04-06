//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Camera.cpp
// Camera Object - position, up and lookat
//------------------------------------------------------------------------------

#include "Camera.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "STMatrix4.h"
#include "utilities.h"
#include "defs.h"
#include <C:\SolarSystem\src\include\GL\glut.h>

Camera::Camera(void)
    : m_trackballsize   (0.8f)
{
    Reset();
    m_rotationMode = ORBIT;
}

Camera::~Camera()
{

}

void Camera::SetUpAndRight(void)
{
    m_Right = STVector3::Cross(m_LookAt - m_Position, m_Up);
    m_Right.Normalize();
    m_Up = STVector3::Cross(m_Right, m_LookAt - m_Position);
    m_Up.Normalize();
}

void Camera::Reset(void) 
{
    m_LookAt=STVector3(0.f,3.0f,-1.0f);
    m_Position=STVector3(1.0f,-5.0f,1.0f);
    m_Up=STVector3(0.0f,1.0f,0.0f);
	m_Right = STVector3(1.0f, 0.0f, 0.0f);
    SetUpAndRight();
}

void Camera::ResetUp(void)
{
    m_Up = STVector3(0.f,1.f,0.f);
    m_Right = STVector3::Cross(m_LookAt - m_Position, m_Up);
    m_Right.Normalize();
    m_Up = STVector3::Cross(m_Right, m_LookAt - m_Position);
    m_Up.Normalize();
}


void Camera::Orbit(float axis[4], float p1x, float p1y, float p2x, float p2y)
{
}

void Camera::Rotate_about_X(GLfloat Angle) // Rotate around the X axis by arrow key
{
	m_rotate_X = m_rotate_X + Angle;
	m_LookAt = m_LookAt*cos(Angle * PI / 180.0) + m_Up*sin(Angle * PI / 180.0);
	m_LookAt.Normalize();
	m_Up = STVector3::Cross(m_LookAt, m_Right)*-1;
}

void Camera::Rotate_about_Y(GLfloat Angle) // Rotate around the Y axis by arrow key
{
	m_rotate_Y = m_rotate_Y + Angle;
	m_LookAt = m_LookAt*cos(Angle * PI / 180.0) - m_Right*sin(Angle * PI / 180.0);
	m_LookAt.Normalize();
	m_Right = STVector3::Cross(m_LookAt, m_Up);
}

void Camera::Rotate_about_Z(GLfloat Angle) // Rotate around the Z axis by arrow key
{
	m_rotate_Z = m_rotate_Z + Angle;
	m_Right = (m_Right*cos(Angle*PI / 180.0) + m_Up*sin(Angle*PI / 180.0));
	m_Right.Normalize();
	m_Up = STVector3::Cross(m_LookAt, m_Right)*-1;
}

  float p_ProjectToSphere(float r, float x, float y)
{
	float d, t, z;
	d = sqrt(x * x + y * y);
	if (d < r * 0.70710678118654752440)
	{
		z = sqrt(r * r - d * d);
	}
	else
	{
		t = (float)(r / 1.41421356237309504880);
		z = t * t / d;
	}
	return -z;
}

void Camera::Rotate(float delta_x, float delta_y)
{
	float yaw_rate = 1.f;
	float pitch_rate = 1.f;
	m_Position -= m_LookAt;
	STMatrix4 m;
	m.EncodeR(-1 * delta_x*yaw_rate, m_Up);
	m_Position = m * m_Position;
	m.EncodeR(-1 * delta_y*pitch_rate, m_Right);
	m_Position = m * m_Position;
	m_Position += m_LookAt;	
}


void Camera::Zoom(float delta_y)
{
    STVector3 direction = m_LookAt - m_Position;
    float magnitude = direction.Length();
    direction.Normalize();
    float zoom_rate = 0.1f*magnitude < 0.5f ? .1f*magnitude : .5f;
    if(delta_y * zoom_rate + magnitude > 0)
    {
        m_Position += (delta_y * zoom_rate) * direction;
    }
}


void Camera::Strafe(float delta_x, float delta_y)
{
    float strafe_rate = 0.05f;
    m_Position -= strafe_rate * delta_x * m_Right;
    m_LookAt   -= strafe_rate * delta_x * m_Right;
    m_Position += strafe_rate * delta_y * m_Up;
    m_LookAt   += strafe_rate * delta_y * m_Up;
}


STVector3 Camera::Position (void)
{
    return(m_Position);
}


STVector3 Camera::LookAt (void)
{
    return(m_LookAt);
}


STVector3 Camera::Up (void)
{
    return(m_Up);
}

STVector3 Camera::Right (void)
{
    return(m_Right);
}


STMatrix4 Camera::GetProjectionMatrix (void)
{
    return(m_MP);
}


STMatrix4 Camera::GetViewMatrix (void)
{
    return(m_MV);
}


void Camera::SetProjectionMatrix (STMatrix4 m)
{
    m_MP = m;
}


void Camera::SetViewMatrix (STMatrix4 m)
{
    m_MV = m;
}


void Camera::ToggleRotationMode (void)
{
    if(m_rotationMode == ORBIT)
        m_rotationMode = FLY;
    else if(m_rotationMode == FLY)
        m_rotationMode = ORBIT;
}

void Camera::Screen_Rotate_Left_Right(void)
{
	STVector3 m_Lookpoint = m_Position + m_LookAt;
	gluLookAt(m_Position.x, m_Position.y, m_Position.z, m_Lookpoint.x, m_Lookpoint.y, m_Lookpoint.z, m_Up.x, m_Up.y, m_Up.z);
}

void Camera::SetLookAt(STVector3 lookat)
{
    m_LookAt = lookat;
}

void Camera::SetPosition(STVector3 position)
{
    m_Position = position;
}

void Camera::SetUp(STVector3 up)
{
    m_Up = up;
}