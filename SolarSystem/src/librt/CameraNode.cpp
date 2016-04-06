//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// CameraNode.cpp
// Camera Node.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// This is a new file added for assignment Proj3_4 OpenGL
//------------------------------------------------------------------------------------
#include "CameraNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>

CameraNode::CameraNode(void) 
{ 
}


CameraNode::~CameraNode(void) 
{ 
}


void CameraNode::Initialize(Camera *pCamera)
{
    m_pCamera = pCamera;
}


void CameraNode::Update(void)
{
	// CameraNode function updated in Camera.cpp
  SceneNode::Update();
}





