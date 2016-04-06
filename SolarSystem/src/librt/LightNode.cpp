//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// LightNode.cpp
// Light Node.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// This is a new file added for assignment Proj3_4 OpenGL
//------------------------------------------------------------------------------------
#include "LightNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>





LightNode::LightNode(void) 
{ 
}


LightNode::~LightNode(void) 
{ 
}


void LightNode::Initialize(Light *pLight)
{
    m_pLight = pLight;
}


void LightNode::Update(void)
{
  SceneNode::Update();
}


