//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// TransformNode.cpp
// Transform Node.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// This is a new file added for assignment Proj3_4 OpenGL
//------------------------------------------------------------------------------------
#include "TransformNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "stgl.h"




TransformNode::TransformNode(void) 
{ 
}


TransformNode::~TransformNode(void) 
{ 
}


void TransformNode::Initialize(STMatrix4 m)
{
    m_Matrix = m;
}


void TransformNode::Update(void)
{
    glPushMatrix();
    glLoadMatrixf((float *)m_Matrix.table);
    SceneNode::Update();
    glPopMatrix();
}


