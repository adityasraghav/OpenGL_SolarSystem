//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Scene.h
// Stores all the objects - lights, camera and surfaces for setting up the scene.
//------------------------------------------------------------------------------


#ifndef __SCENE_H__
#define __SCENE_H__


//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// These are new include files added to the scene class for this assignment
//------------------------------------------------------------------------------------
#include<queue>
//------------------------------------------------------------------------------------

#include "Camera.h"
#include "defs.h"
#include "Ray.h"
#include "Lists.h"
#include "RGBR_f.h"
#include "SceneNode.h"





class Scene
{

public:
                                Scene                                       (void);
                                ~Scene                                      (void);

    void                        SetBackgroundColor                          (RGBR_f color);
    RGBR_f                      GetBackgroundColor                          (void);

    void                        AddLight                                    (Light lightin);
    void                        AddSurface                                  (Surface *pSurfacein);


    Camera                      *GetCamera                                  (void);
    STVector3                    GetLightDirection                          (void);

    int                         FindIntersection                            (Ray ray, Intersection *pIntersection, bool bAny);
    int                         FindClosestIntersection                     (Ray ray, Intersection *pIntersection);
    int                         SelectClosest                               (IntersectionList *pIntersectionList, Intersection *pIntersection);


    //------------------------------------------------------------------------------------
    // TO DO: Proj3_4 OpenGL
    // These are all of the new members added to the scene class for this assignment
    //------------------------------------------------------------------------------------

    void                        ToggleManipMode                             (void);
    void                        ToggleManipGeometry                         (void);
    void                        ToggleRenderMode                            (void);
    void                        InitManipMode                               (void);
    void                        InitManipGeometryMode                       (void);
    RenderMode                  GetRenderMode                               (void);
    void                        SetRenderMode                               (RenderMode mode);                                  

    void                        Translate                                   (int axis, STMatrix4 viewProjection, SceneNode object, STVector2 prevMousePos, STVector2 curMousePos);
    void                        Rotate                                      (int axis, STMatrix4 viewProjection, SceneNode object, STVector2 prevMousePos, STVector2 curMousePos);
    void                        Spin                                        (float QMat1[4], float QMat2[4], float QMat3[4]);

    void                        PropogateTransforms                         (SceneNode *pNode);

    STVector3                   GetLightPosition                            (void);

    void                        AddManipulator                              (void);
    ManipMode                   CurrentManipMode                            (void);
    ManipGeom                   CurrentManipGeometryState                   (void);
    ManipMotionType             CurrentManipMotion                          (void);
    void                        SetCurrentManipMotion                       (ManipMotionType mmotiontype);
    void                        SetActiveManipGeom                          (ManipGeom mgeom);
    ManipGeom                   GetActiveManipGeom                          (void);
    bool                        RotatingManip                               (void);
    bool                        TranslatingManip                            (void);
    bool                        HasManipulator                              (void);
    void                        RemoveManip                                 (void);


    bool                        SelectObject                                (int mouseX, int mouseY, int width, int height, STPoint3 bspherecenter, float bsphereradius);
    bool                        SelectManipulator                           (int mouseX, int mouseY, int width, int height);
    //--------------------------------------------------------------------------------------


private:


    // surfaces
    SurfaceList                  m_surfaceList;


    // camera
    Camera                      *m_pCamera;

    // lights
    LightList                   m_lights;


    // background color
    RGBR_f                     m_background;


    // clear scene
    void                        Clear               (void);



    //------------------------------------------------------------------------------------
    // TO DO: Proj3_4 OpenGL
    // These are all of the new members added to the scene class for this assignment
    //------------------------------------------------------------------------------------
    bool                        RayTestManip                        (STVector3 raystart, STVector3 rayend, ManipGeom *selectedGeom);

    ManipMotionType             MapGeomToMotion                     (ManipGeom selectedGeom);

    std::queue<ManipMode>       m_modeQueue;                        // the current mode is at the top LOCAL, PARENT, NONE
    std::queue<ManipGeom>       m_manipGeomQueue;                   // the current manip geom state is at the top, which parts are visible
    ManipMotionType             m_manipMotionType;                  // stores the current motion type, the selected geometry triggers this
    ManipGeom                   m_activeManipGeom;                  // active manip geometry

    SceneNode                   *m_pTree;                           // root node of the scene graph

    RenderMode                  m_renderMode;                       // determines how objects are rendered

    bool                        m_bHasManipulator;                  // true if there is a manipulator in the scene

    //--------------------------------------------------------------------------------------





};


#endif //__SCENE_H__


