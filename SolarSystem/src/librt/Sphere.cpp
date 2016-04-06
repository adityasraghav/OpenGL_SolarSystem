//----------------------------------------------------------------
// Sphere.cpp
//----------------------------------------------------------------
#include "Sphere.h"
#include <assert.h>
#include <stdio.h>
#include <string>
#include "defs.h"

Sphere::Sphere(void)
    : m_radius(0.5)
{
      m_center = STVector3(0,0,0);
}

Sphere::~Sphere()
{

}

bool Sphere::FindIntersection(Ray ray, Intersection *pIntersection) 
{

    bool bFound = false;
    return(bFound);
}

