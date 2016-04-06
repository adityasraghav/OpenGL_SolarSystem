    //------------------------------------------------------------------------------------
    // TO DO: Proj3_4 OpenGL
    // These are new members added to the matrix class for this assignment
    // No implementation required
    //------------------------------------------------------------------------------------



// STMatrix4.inl
#ifndef __STMATRIX4_INL__
#define __STMATRIX4_INL__

/**
* Inline file for STMatrix4.h
*/

#include "STVector3.h"
#include <cstring>
inline STMatrix4::STMatrix4()
{
    EncodeI();
}

inline STMatrix4::STMatrix4( const float* pf )
{
	memcpy(&table[0][0], pf, sizeof(STMatrix4));
}

inline void STMatrix4::EncodeI()
{
    for(int i=0;i<4;i++)for(int j=0;j<4;j++)
        table[i][j]=(i==j?1.f:0.f);
}

inline void STMatrix4::EncodeT(float tx,float ty,float tz)
{
    EncodeI();
    table[0][3]=tx;
    table[1][3]=ty;
    table[2][3]=tz;
}


inline void STMatrix4::GetT(float *tx,float *ty,float *tz)
{
    *tx = table[0][3];
    *ty = table[1][3];
    *tz = table[2][3];
}

inline void STMatrix4::EncodeS(float sx,float sy,float sz)
{
    EncodeI();
    table[0][0]=sx;
    table[1][1]=sy;
    table[2][2]=sz;
}

inline void STMatrix4::EncodeR(float degrees,const STVector3& axis)
{
    EncodeI();
    //http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
    float cos_t=cos(degrees * 3.1415926536f / 180.f);
    float sin_t=sin(degrees * 3.1415926535f / 180.f);

    STVector3 unit_vector=axis;
    unit_vector.Normalize();

    const float& x=unit_vector.x;
    const float& y=unit_vector.y;
    const float& z=unit_vector.z;

    table[0][0] = cos_t + x*x*(1.f-cos_t);
    table[0][1] = x*y*(1-cos_t) - z*sin_t;
    table[0][2] = x*z*(1-cos_t) + y*sin_t;

    table[1][0] = y*x*(1-cos_t) + z*sin_t;
    table[1][1] = cos_t + y*y*(1-cos_t);
    table[1][2] = y*z*(1-cos_t) - x*sin_t;

    table[2][0] = z*x*(1-cos_t) - y*sin_t;
    table[2][1] = z*y*(1-cos_t) + x*sin_t;
    table[2][2] = cos_t + z*z*(1-cos_t);
}

inline STVector3 STMatrix4::operator*(const STVector3& v)
{
    STVector3 result;
    result.x = table[0][0]*v.x + table[0][1]*v.y + table[0][2]*v.z;
    result.y = table[1][0]*v.x + table[1][1]*v.y + table[1][2]*v.z;
    result.z = table[2][0]*v.x + table[2][1]*v.y + table[2][2]*v.z;
    return result;
}


inline STMatrix4 STMatrix4::operator * ( const STMatrix4& mat ) const
{
	STMatrix4 matT;
	matT.Multiply(*this, mat);
	return matT;
}

inline void MatMult(const float *a, const float *b, float *r)
{
	r[0] = a[0]*b[0] + a[1]*b[4] + a[2]*b[8]  + a[3]*b[12];
	r[1] = a[0]*b[1] + a[1]*b[5] + a[2]*b[9]  + a[3]*b[13];
	r[2] = a[0]*b[2] + a[1]*b[6] + a[2]*b[10] + a[3]*b[14];
	r[3] = a[0]*b[3] + a[1]*b[7] + a[2]*b[11] + a[3]*b[15];

	r[4] = a[4]*b[0] + a[5]*b[4] + a[6]*b[8]  + a[7]*b[12];
	r[5] = a[4]*b[1] + a[5]*b[5] + a[6]*b[9]  + a[7]*b[13];
	r[6] = a[4]*b[2] + a[5]*b[6] + a[6]*b[10] + a[7]*b[14];
	r[7] = a[4]*b[3] + a[5]*b[7] + a[6]*b[11] + a[7]*b[15];

	r[8] = a[8]*b[0] + a[9]*b[4] + a[10]*b[8] + a[11]*b[12];
	r[9] = a[8]*b[1] + a[9]*b[5] + a[10]*b[9] + a[11]*b[13];
	r[10]= a[8]*b[2] + a[9]*b[6] + a[10]*b[10]+ a[11]*b[14];
	r[11]= a[8]*b[3] + a[9]*b[7] + a[10]*b[11]+ a[11]*b[15];

	r[12]= a[12]*b[0]+ a[13]*b[4]+ a[14]*b[8] + a[15]*b[12];
	r[13]= a[12]*b[1]+ a[13]*b[5]+ a[14]*b[9] + a[15]*b[13];
	r[14]= a[12]*b[2]+ a[13]*b[6]+ a[14]*b[10]+ a[15]*b[14];
	r[15]= a[12]*b[3]+ a[13]*b[7]+ a[14]*b[11]+ a[15]*b[15];
}

inline void STMatrix4::Multiply( const STMatrix4 &matrix)
{
	STMatrix4 tmp;
	tmp = *this;
	MatMult( (float*)&tmp, (float*)&matrix, (float*)this);
}


inline void STMatrix4::Multiply( const STMatrix4 &m1, const STMatrix4 &m2 )
{
    MatMult( (float*)&m1, (float*)&m2, (float*)this);
}

#endif  // __STMATRIX4_INL__
