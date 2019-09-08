// This file is part of libigl, a simple c++ geometry processing library.
//
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public License
// v. 2.0. If a copy of the MPL was not distributed with this file, You can
// obtain one at http://mozilla.org/MPL/2.0/.
#include "snap_to_canonical_view_quat.h"

#include "canonical_quaternions.h"
#include "normalize_quat.h"

#include <cstdio>
#include <cassert>

// Note: For the canonical view quaternions it should be completely possible to
// determine this anaylitcally. That is the max_distance should be a
// theoretical known value
// Also: I'm not sure it matters in this case, but. We are dealing with
// quaternions on the 4d unit sphere, but measuring distance in general 4d
// space (i.e. not geodesics on the sphere). Probably something with angles
// would be better.
template <typename Q_type>
IGL_INLINE bool igl::snap_to_canonical_view_quat(
  const Q_type* q,
  const Q_type threshold,
  Q_type* s)
{
  // Copy input into output
  // CANNOT use std::copy here according to:
  // http://www.cplusplus.com/reference/algorithm/copy/
  s[0] = q[0];
  s[1] = q[1];
  s[2] = q[2];
  s[3] = q[3];

  // Normalize input quaternion
  Q_type qn[4];
  bool valid_len =
    igl::normalize_quat(q,qn);
  // If normalizing valid then don't bother
  if(!valid_len)
  {
    return false;
  }

  // 0.290019
  const Q_type MAX_DISTANCE = 0.4;
  Q_type min_distance = 2*MAX_DISTANCE;
  int min_index = -1;
  double min_sign = 0;
  // loop over canonical view quaternions
  for(double sign = -1;sign<=1;sign+=2)
  {
    for(int i = 0; i<NUM_CANONICAL_VIEW_QUAT; i++)
    {
      Q_type distance = 0.0;
      // loop over coordinates
      for(int j = 0;j<4;j++)
      {
        // Double cast because of bug in llvm version 4.2 with -O3
        distance +=
          (qn[j]-sign*igl::CANONICAL_VIEW_QUAT<Q_type>(i,j))*
          (qn[j]-sign*igl::CANONICAL_VIEW_QUAT<Q_type>(i,j));
      }
      if(min_distance > distance)
      {
        min_distance = distance;
        min_index = i;
        min_sign = sign;
      }
    }
  }

  if(MAX_DISTANCE < min_distance)
  {
    fprintf(
      stderr,
      "ERROR: found new max MIN_DISTANCE: %g\n"
      "PLEASE update snap_to_canonical_quat()",
      min_distance);
  }

  assert(min_distance < MAX_DISTANCE);
  assert(min_index >= 0);

  if( min_distance/MAX_DISTANCE <= threshold)
  {
    // loop over coordinates
    for(int j = 0;j<4;j++)
    {
      s[j] = min_sign*igl::CANONICAL_VIEW_QUAT<Q_type>(min_index,j);
    }
    return true;
  }
  return false;
}

template <typename Scalarq, typename Scalars>
IGL_INLINE bool igl::snap_to_canonical_view_quat(
  const Eigen::Quaternion<Scalarq> & q,
  const double threshold,
  Eigen::Quaternion<Scalars> & s)
{
  return snap_to_canonical_view_quat<Scalars>(
    q.coeffs().data(),threshold,s.coeffs().data());
}

#ifdef IGL_STATIC_LIBRARY
// Explicit template instantiation
// generated by autoexplicit.sh
template bool igl::snap_to_canonical_view_quat<double>(const double*, double, double*);
// generated by autoexplicit.sh
template bool igl::snap_to_canonical_view_quat<float>(const float*, float, float*);
template bool igl::snap_to_canonical_view_quat<float, float>(Eigen::Quaternion<float, 0> const&, double, Eigen::Quaternion<float, 0>&);
template bool igl::snap_to_canonical_view_quat<double, double>(Eigen::Quaternion<double, 0> const&, double, Eigen::Quaternion<double, 0>&);
#endif
