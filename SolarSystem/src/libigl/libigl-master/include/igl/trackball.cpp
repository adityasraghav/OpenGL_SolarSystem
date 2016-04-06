// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "trackball.h"

#include "EPS.h"
#include "dot.h"
#include "cross.h"
#include "axis_angle_to_quat.h"
#include "quat_mult.h"
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <algorithm>
#include <iostream>

// Utility IGL_INLINE functions
template <typename Q_type>
static IGL_INLINE Q_type _QuatD(double w, double h)
{
  using namespace std;
  return (Q_type)(std::abs(w) < std::abs(h) ? std::abs(w) : std::abs(h)) - 4;
}
template <typename Q_type>
static IGL_INLINE Q_type _QuatIX(double x, double w, double h)
{
  return (2.0f*(Q_type)x - (Q_type)w - 1.0f)/_QuatD<Q_type>(w, h);
}
template <typename Q_type>
static IGL_INLINE Q_type _QuatIY(double y, double w, double h)
{
  return (-2.0f*(Q_type)y + (Q_type)h - 1.0f)/_QuatD<Q_type>(w, h);
}

// This is largely the trackball as implemented in AntTweakbar. Much of the
// code is straight from its source in TwMgr.cpp
// http://www.antisphere.com/Wiki/tools:anttweakbar
template <typename Q_type>
IGL_INLINE void igl::trackball(
  const double w,
  const double h,
  const Q_type speed_factor,
  const double down_mouse_x,
  const double down_mouse_y,
  const double mouse_x,
  const double mouse_y,
  Q_type * quat)
{
  assert(speed_factor > 0);

  double original_x =
    _QuatIX<Q_type>(speed_factor*(down_mouse_x-w/2)+w/2, w, h);
  double original_y =
    _QuatIY<Q_type>(speed_factor*(down_mouse_y-h/2)+h/2, w, h);

  double x = _QuatIX<Q_type>(speed_factor*(mouse_x-w/2)+w/2, w, h);
  double y = _QuatIY<Q_type>(speed_factor*(mouse_y-h/2)+h/2, w, h);

  double z = 1;
  double n0 = sqrt(original_x*original_x + original_y*original_y + z*z);
  double n1 = sqrt(x*x + y*y + z*z);
  if(n0>igl::DOUBLE_EPS && n1>igl::DOUBLE_EPS)
  {
    double v0[] = { original_x/n0, original_y/n0, z/n0 };
    double v1[] = { x/n1, y/n1, z/n1 };
    double axis[3];
    cross(v0,v1,axis);
    double sa = sqrt(dot(axis, axis));
    double ca = dot(v0, v1);
    double angle = atan2(sa, ca);
    if( x*x+y*y>1.0 )
    {
      angle *= 1.0 + 0.2f*(sqrt(x*x+y*y)-1.0);
    }
    double qrot[4];
    axis_angle_to_quat(axis,angle,qrot);
    quat[0] = qrot[0];
    quat[1] = qrot[1];
    quat[2] = qrot[2];
    quat[3] = qrot[3];
  }
}


template <typename Q_type>
IGL_INLINE void igl::trackball(
  const double w,
  const double h,
  const Q_type speed_factor,
  const Q_type * down_quat,
  const double down_mouse_x,
  const double down_mouse_y,
  const double mouse_x,
  const double mouse_y,
  Q_type * quat)
{
  double qrot[4], qres[4], qorig[4];
  igl::trackball<double>(
    w,h,
    speed_factor,
    down_mouse_x,down_mouse_y,
    mouse_x,mouse_y,
    qrot);
  double nqorig =
    sqrt(down_quat[0]*down_quat[0]+
    down_quat[1]*down_quat[1]+
    down_quat[2]*down_quat[2]+
    down_quat[3]*down_quat[3]);

  if( fabs(nqorig)>igl::DOUBLE_EPS_SQ )
  {
      qorig[0] = down_quat[0]/nqorig;
      qorig[1] = down_quat[1]/nqorig;
      qorig[2] = down_quat[2]/nqorig;
      qorig[3] = down_quat[3]/nqorig;
      igl::quat_mult<double>(qrot,qorig,qres);
      quat[0] = qres[0];
      quat[1] = qres[1];
      quat[2] = qres[2];
      quat[3] = qres[3];
  }
  else
  {
      quat[0] = qrot[0];
      quat[1] = qrot[1];
      quat[2] = qrot[2];
      quat[3] = qrot[3];
  }
}

template <typename Scalardown_quat, typename Scalarquat>
IGL_INLINE void igl::trackball(
  const double w,
  const double h,
  const double speed_factor,
  const Eigen::Quaternion<Scalardown_quat> & down_quat,
  const double down_mouse_x,
  const double down_mouse_y,
  const double mouse_x,
  const double mouse_y,
  Eigen::Quaternion<Scalarquat> & quat)
{
  using namespace std;
  return trackball(
    w,
    h,
    (Scalarquat)speed_factor,
    down_quat.coeffs().data(),
    down_mouse_x,
    down_mouse_y,
    mouse_x,
    mouse_y,
    quat.coeffs().data());
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template specialization
// generated by autoexplicit.sh
template void igl::trackball<double>(double, double, double, double const*, double, double, double, double, double*);
// generated by autoexplicit.sh
template void igl::trackball<float>(double, double, float, float const*, double, double, double, double, float*);
template void igl::trackball<float, float>(double, double, double, Eigen::Quaternion<float, 0> const&, double, double, double, double, Eigen::Quaternion<float, 0>&);
template void igl::trackball<double, double>(double, double, double, Eigen::Quaternion<double, 0> const&, double, double, double, double, Eigen::Quaternion<double, 0>&);
#endif
