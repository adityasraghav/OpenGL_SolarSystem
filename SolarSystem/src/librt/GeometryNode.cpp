//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// GeometryNode.cpp
// Geometry Node.
//------------------------------------------------------------------------------

#include "GeometryNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>

GeometryNode::GeometryNode(void) 
{ 
}

GeometryNode::~GeometryNode(void) 
{ 
}

void GeometryNode::Initialize(Surface *pSurface)
{
    m_pSurface = pSurface;
}

void GeometryNode::Update(void)
{
	// Triangle Mesh added in mainsrc_proj3_4.cpp
  SceneNode::Update();
}


