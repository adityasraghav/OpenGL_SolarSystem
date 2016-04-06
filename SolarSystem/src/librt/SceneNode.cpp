//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// SceneNode.cpp
// Base class for scene nodes.
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// This is a new file added for assignment Proj3_4 OpenGL
//------------------------------------------------------------------------------------
#include "SceneNode.h"
#include <assert.h>
#include <stdio.h>
#include <string>




SceneNode::SceneNode(void) 
{ 
}


SceneNode::~SceneNode(void) 
{ 
    Destroy();
}

void SceneNode::Release(void) 
{ 
    delete this; 
}

void SceneNode::Update(void)
{
    for( std::list<SceneNode*>::iterator i = m_lstChildren.begin(); i != m_lstChildren.end(); i++ )
    {
      (*i)->Update();
    }
}

void SceneNode::Destroy(void)
{
    for( std::list<SceneNode*>::iterator i = m_lstChildren.begin();
        i != m_lstChildren.end(); i++ )
        (*i)->Release();

    m_lstChildren.clear();
}


 void SceneNode::AddChild(SceneNode* pNode )
{
    m_lstChildren.push_back(pNode);
}

 std::list<SceneNode*> SceneNode::GetChildren(void)
{
    return(m_lstChildren);
}


