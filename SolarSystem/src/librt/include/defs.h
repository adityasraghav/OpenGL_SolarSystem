//------------------------------------------------------------------------------
// Copyright 2015 Corey Toler-Franklin, University of Florida
// Defs.h
// Global Definitions
//------------------------------------------------------------------------------


#ifndef __DEFS_H__
#define __DEFS_H__

#include <vector>
#include "Light.h"
#include "Intersection.h"


//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// New definitions
// No implementation required
//------------------------------------------------------------------------------------

// Manipulator modes 
// determines whether translations happen locally
// or in the parent coordinate system
// or if no manipulations at all
typedef enum {
    NONE       = 0, // no manipulators
    LOCAL      = 1, // manipulators local transforms
    PARENT     = 2  // manupulators parent coordinate transforms

}ManipMode;


// Camera modes 
// determines whether rotations  focus around and object (orbit)
// or the camera view (fly)
typedef enum {
    FLY        = 0, 
    ORBIT      = 1
}CameraRotationMode;


// Manipulation modes 
// Specifies the type of manipulation
typedef enum {
    TRANS_YZ                = 0, 
    TRANS_XZ                = 1, 
    TRANS_XY                = 2, 
    TRANS_XYZ               = 3, 
    TRANS_X                 = 4, 
    TRANS_Y                 = 5, 
    TRANS_Z                 = 6,
    ROTATE_X                = 7,
    ROTATE_Y                = 8,
    ROTATE_Z                = 9,
    ROTATE_SCREEN           = 10,
    ROTATE_DUPLICATE        = 11,
    MANIP_NONE              = 12
}ManipMotionType;

// Manipulator geometry parts
// hides parts of the manipulator to make
// it easier to select parts of the geometry
// also used to determine which part of the 
// manipulator is selected
typedef enum {
    AXIS_ALL                    = 0, 
    AXIS_TRANSXYZ               = 1,
    AXIS_TRANSX                 = 2,
    AXIS_TRANSY                 = 3,
    AXIS_TRANSZ                 = 4,
    AXIS_ROTX                   = 5,
    AXIS_ROTY                   = 6,
    AXIS_ROTZ                   = 7,
    AXIS_ROTTRACKBALL           = 8,
    AXIS_ROTSCREEN              = 9,
    AXIS_ROTATIONALL            = 10,
    AXIS_DUPLICATE              = 11, 
    AXIS_NONE                   = 12
}ManipGeom;


//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// Added NAVIGATIONMODE
// No implementation required
// render modes 
// determines the type of image created
typedef enum {
    LAMBERTIAN      = 0,
    PHONG           = 1,
    MIRROR          = 2,
    ENVIRONMENTMAP  = 3,
    EFFECT_1        = 4,
    EFFECT_2        = 5,
    EFFECT_3        = 6,
    NAVIGATION
}RenderMode;


//------------------------------------------------------------------------------------
// TO DO: Proj3_4 OpenGL
// New definitions
// No implementation required
//------------------------------------------------------------------------------------

// constants use for the manipulator
#define RENORMCOUNT 97         
#define TRACKBALLSIZE 0.8f;
const float PI    =  3.14159265358979323846f;

const float distanceScale = 0.00000003f;

extern float scalePlanet;

#define NULL_VECTOR STVector3(0.0f,0.0f,0.0f)


// TEXT_texture_cube_map support
//--------------------------------------------------------------
#ifndef GL_EXT_texture_lod_bias
# define GL_MAX_TEXTURE_LOD_BIAS         0x84fd
# define GL_TEXTURE_FILTER_CONTROL       0x8500
# define GL_TEXTURE_LOD_BIAS             0x8501
#endif

#ifndef GL_EXT_texture_cube_map
# define GL_NORMAL_MAP                          0x8511
# define GL_REFLECTION_MAP                      0x8512
# define GL_TEXTURE_CUBE_MAP                    0x8513
# define GL_TEXTURE_BINDING_CUBE_MAP            0x8514
# define GL_TEXTURE_CUBE_MAP_POSITIVE_X         0x8515
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_X         0x8516
# define GL_TEXTURE_CUBE_MAP_POSITIVE_Y         0x8517
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y         0x8518
# define GL_TEXTURE_CUBE_MAP_POSITIVE_Z         0x8519
# define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z         0x851A
# define GL_PROXY_TEXTURE_CUBE_MAP              0x851B
# define GL_MAX_CUBE_MAP_TEXTURE_SIZE           0x851C
#endif


// teapot geometry
static int geom_teapot[][16] =
{
    /* rim */
  {102, 103, 104, 105, 4, 5, 6, 7, 8, 9, 10, 11,
    12, 13, 14, 15},
    /* body */
  {12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27},
  {24, 25, 26, 27, 29, 30, 31, 32, 33, 34, 35, 36,
    37, 38, 39, 40},
    /* lid */
  {96, 96, 96, 96, 97, 98, 99, 100, 101, 101, 101,
    101, 0, 1, 2, 3,},
  {0, 1, 2, 3, 106, 107, 108, 109, 110, 111, 112,
    113, 114, 115, 116, 117},
    /* bottom */
  {118, 118, 118, 118, 124, 122, 119, 121, 123, 126,
    125, 120, 40, 39, 38, 37},
    /* handle */
  {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
    53, 54, 55, 56},
  {53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64,
    28, 65, 66, 67},
    /* spout */
  {68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83},
  {80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
    92, 93, 94, 95}
};


static float geomData_teapot[][3] =
{
    {0.2, 0, 2.7}, {0.2, -0.112, 2.7}, {0.112, -0.2, 2.7}, {0,
    -0.2, 2.7}, {1.3375, 0, 2.53125}, {1.3375, -0.749, 2.53125},
    {0.749, -1.3375, 2.53125}, {0, -1.3375, 2.53125}, {1.4375,
    0, 2.53125}, {1.4375, -0.805, 2.53125}, {0.805, -1.4375,
    2.53125}, {0, -1.4375, 2.53125}, {1.5, 0, 2.4}, {1.5, -0.84,
    2.4}, {0.84, -1.5, 2.4}, {0, -1.5, 2.4}, {1.75, 0, 1.875},
    {1.75, -0.98, 1.875}, {0.98, -1.75, 1.875}, {0, -1.75,
    1.875}, {2, 0, 1.35}, {2, -1.12, 1.35}, {1.12, -2, 1.35},
    {0, -2, 1.35}, {2, 0, 0.9}, {2, -1.12, 0.9}, {1.12, -2,
    0.9}, {0, -2, 0.9}, {-2, 0, 0.9}, {2, 0, 0.45}, {2, -1.12,
    0.45}, {1.12, -2, 0.45}, {0, -2, 0.45}, {1.5, 0, 0.225},
    {1.5, -0.84, 0.225}, {0.84, -1.5, 0.225}, {0, -1.5, 0.225},
    {1.5, 0, 0.15}, {1.5, -0.84, 0.15}, {0.84, -1.5, 0.15}, {0,
    -1.5, 0.15}, {-1.6, 0, 2.025}, {-1.6, -0.3, 2.025}, {-1.5,
    -0.3, 2.25}, {-1.5, 0, 2.25}, {-2.3, 0, 2.025}, {-2.3, -0.3,
    2.025}, {-2.5, -0.3, 2.25}, {-2.5, 0, 2.25}, {-2.7, 0,
    2.025}, {-2.7, -0.3, 2.025}, {-3, -0.3, 2.25}, {-3, 0,
    2.25}, {-2.7, 0, 1.8}, {-2.7, -0.3, 1.8}, {-3, -0.3, 1.8},
    {-3, 0, 1.8}, {-2.7, 0, 1.575}, {-2.7, -0.3, 1.575}, {-3,
    -0.3, 1.35}, {-3, 0, 1.35}, {-2.5, 0, 1.125}, {-2.5, -0.3,
    1.125}, {-2.65, -0.3, 0.9375}, {-2.65, 0, 0.9375}, {-2,
    -0.3, 0.9}, {-1.9, -0.3, 0.6}, {-1.9, 0, 0.6}, {1.7, 0,
    1.425}, {1.7, -0.66, 1.425}, {1.7, -0.66, 0.6}, {1.7, 0,
    0.6}, {2.6, 0, 1.425}, {2.6, -0.66, 1.425}, {3.1, -0.66,
    0.825}, {3.1, 0, 0.825}, {2.3, 0, 2.1}, {2.3, -0.25, 2.1},
    {2.4, -0.25, 2.025}, {2.4, 0, 2.025}, {2.7, 0, 2.4}, {2.7,
    -0.25, 2.4}, {3.3, -0.25, 2.4}, {3.3, 0, 2.4}, {2.8, 0,
    2.475}, {2.8, -0.25, 2.475}, {3.525, -0.25, 2.49375},
    {3.525, 0, 2.49375}, {2.9, 0, 2.475}, {2.9, -0.15, 2.475},
    {3.45, -0.15, 2.5125}, {3.45, 0, 2.5125}, {2.8, 0, 2.4},
    {2.8, -0.15, 2.4}, {3.2, -0.15, 2.4}, {3.2, 0, 2.4}, {0, 0,
    3.15}, {0.8, 0, 3.15}, {0.8, -0.45, 3.15}, {0.45, -0.8,
    3.15}, {0, -0.8, 3.15}, {0, 0, 2.85}, {1.4, 0, 2.4}, {1.4,
    -0.784, 2.4}, {0.784, -1.4, 2.4}, {0, -1.4, 2.4}, {0.4, 0,
    2.55}, {0.4, -0.224, 2.55}, {0.224, -0.4, 2.55}, {0, -0.4,
    2.55}, {1.3, 0, 2.55}, {1.3, -0.728, 2.55}, {0.728, -1.3,
    2.55}, {0, -1.3, 2.55}, {1.3, 0, 2.4}, {1.3, -0.728, 2.4},
    {0.728, -1.3, 2.4}, {0, -1.3, 2.4}, {0, 0, 0}, {1.425,
    -0.798, 0}, {1.5, 0, 0.075}, {1.425, 0, 0}, {0.798, -1.425,
    0}, {0, -1.5, 0.075}, {0, -1.425, 0}, {1.5, -0.84, 0.075},
    {0.84, -1.5, 0.075}
};



// TO DO: Proj2 raytracer
// CAP5705 - Add constant parameters for special effects.
// 1. Add any constant parameters that may be useful for your
//    special effect. Some examples are added below.
//------------------------------------------------
//------------------------------------------------
const double EPSILON = 1.0e-6; 
const double REFRACT_INDEX_VACUUM           = 1.0000;
const double REFRACT_INDEX_AIR              = 1.0003;
const double REFRACT_INDEX_WATER            = 1.3330;
const double REFRACT_INDEX_GLASS            = 1.5500;
const double REFRACT_INDEX_MIN              = 1.0000;
const double REFRACT_INDEX_MAX              = 9.0000;


#endif //__DEFS_H__

