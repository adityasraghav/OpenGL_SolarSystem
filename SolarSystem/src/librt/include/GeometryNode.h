//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// GeometryNode.h
// Geometry Node for scenes
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// This is a new file added for assignment Proj3_4 OpenGL
//------------------------------------------------------------------------------

#ifndef __GEOMETRYNODE_H__
#define __GEOMETRYNODE_H__

#include"SceneNode.h"
#include"Surface.h"


class GeometryNode: public SceneNode {

public:

                                            GeometryNode                    (void);
                                            ~GeometryNode                   (void);

    void                                    Initialize                      (Surface *pSurface);

    void                                    Update                          (void);

private:

    //------------------------------------------------------------------------------------
    // TO DO: Proj3_4 OpenGL
    // Your geometry node should also store traingle meshses
    // The - List of triangle meshes in your geometry node
    //       is effectively a group node
    //       
    //------------------------------------------------------------------------------------


    Surface                 *m_pSurface;

};


#endif //__GEOMETRYNODE_H__
//---------------------------------------------------------------------------------------------

