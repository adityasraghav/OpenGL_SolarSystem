//------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// This is a new file added for assignment Proj3_4 OpenGL
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// SceneNode.h
// Base class for scenes
//------------------------------------------------------------------------------


#ifndef __SCENENODES_H__
#define __SCENENODES_H__

#include<list>

class SceneNode {

public:
                            // constructor
                            SceneNode                                       (void);

                            // destructor - calls destroy
                             virtual ~SceneNode                             (void);

    // release this object from memory
    void                    Release                                         (void);

    // update our scene node
    virtual void            Update                                          (void);

    // destroy all the children
    void                    Destroy                                         (void);

    // add a child to our custody
    void                    AddChild                                        (SceneNode* pNode);

    std::list<SceneNode*>   GetChildren                                     (void);


protected:

    // list of children
    std::list<SceneNode*> m_lstChildren;
};


#endif //__SCENENODE_H__
//---------------------------------------------------------------------------------------------

