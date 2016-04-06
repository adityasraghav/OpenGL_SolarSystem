//----------------------------------------------------------------
// Triangle.cpp
// Copyright: Corey Toler-Franklin, University of Florida
// 
// Triangle surface class
// This class is represented by the surface enclosed by 3 points:m_a, m_b, m_c
//----------------------------------------------------------------
#include "Triangle.h"
#include "LinearSolver.h"
#include "defs.h"

Triangle::Triangle(void)
        : Surface()
{

}

Triangle::~Triangle()
{

}

bool Triangle::IntersectionSolver(Ray ray, STVector3 A, STVector3 B, STVector3 C, double u, double v, double w)
{
    LinearSolver L;
    bool bFoundSolution = false;
    return(bFoundSolution);
}

bool Triangle::FindIntersection (Ray ray, Intersection *pIntersection)
{
    bool bFound = false;
    return(bFound);
}

STVector3 Triangle::ComputeNormalVector(void)
{
    STVector3 normal(0,0,1);
    return(normal);
}

