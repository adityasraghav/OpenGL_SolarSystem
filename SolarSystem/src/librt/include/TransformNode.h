//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// TransformNode.h
// Transform Node for scenes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// This is a new file added for assignment Proj3_4 OpenGL
//------------------------------------------------------------------------------


#ifndef __TRANSFORMNODE_H__
#define __TRANSFORMNODE_H__



#include"SceneNode.h"
#include "STMatrix4.h"



class TransformNode: public SceneNode {

public:

                                            TransformNode               (void);
                                            ~TransformNode              (void);

                        void                Initialize                  (STMatrix4 m);

                        void                Update                      (void);


private:

    STMatrix4           m_Matrix; 

};


#endif //__TRANSFORMNODE_H__
//---------------------------------------------------------------------------------------------

