//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// LightNode.h
// Light Node for scenes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// This is a new file added for assignment Proj3_4 OpenGL
//------------------------------------------------------------------------------


#ifndef __LIGHTNODE_H__
#define __LIGHTNODE_H__

#include"SceneNode.h"


class Light;

class LightNode: public SceneNode {

public:

                                            LightNode                   (void);
                                            ~LightNode                  (void);
                                            
    void                                    Initialize                  (Light *pLight);

    void                                     Update                     (void);

private:

    Light           *m_pLight;

};


#endif //__LIGHTNODE_H__
//---------------------------------------------------------------------------------------------

