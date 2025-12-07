;/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : sphere.h
 * PURPOSE     : Raytracing project.
 *               Sphere class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 24.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __sphere_h_
#define __sphere_h_
#include "def.h"

/* Application namespace. */
namespace gort
{
  /* Sphere shape class. */
  class sphere : public shape
  {
    vec3 C;
    DBL R;
    DBL R2;
  public:

    sphere( const vec3 &Center, const DBL Rad )
    {
      R = Rad;
      R2 = Rad * Rad;
      C = Center;
    }
    sphere( const vec3 &Center, const DBL Rad, const surface Mtl )
    {
      R = Rad;
      R2 = Rad * Rad;
      C = Center;
      Material = Mtl;
    }
    /* Get normal function.
     * ARGUMENTS:
     *   - intersection data:
     *       intr *in;
     * RETURNS: None.
     */
    VOID GetNormal( intr *in )
    {
      in->N = (in->P - C) / R;
    } /* End of 'GetNormal' function */

    /* 
     * 
     */
    BOOL Intersect( const ray &R, intr *Intr )
    {
      vec3 a = C - R.Org;
      DBL OK = a & R.Dir;
      if (OK < 0)
        return FALSE;

      DBL OC2 = a & a;
      DBL OK2 = OK * OK;
      DBL h2 = R2 - (OC2 - OK2);

      if (OC2 < R2)
      {
        Intr->T = OK + std::sqrt(h2);
        return TRUE;
      }
      if (h2 < 0)
        return FALSE;
      Intr->T = OK - std::sqrt(h2);
      return TRUE;
    } /* End of 'Intersect' function */

   /* Get all ray shape intersection function.
    * ARGUMENTS:
    *   - ray to intersect with:
    *       const ray &R;
    *   - result intersection list:
    *       intr_list &IList;
    * RETURNS:
    *   (INT) number of intersecion points.
    */
  INT AllIntersect( const ray &R, intr_list &IList ) override
  {
    // Check for intersection
    vec3 OC = C - R.Org;
    DBL
      oc2 = OC & OC,
      ok = OC & R.Dir,
      ok2 = ok * ok,
      h2 = R2 - (oc2 - ok2);

    // Ray leaves sphere behind
    if (ok < 0)
    {
      // Check for ray starts outside sphere
      if (h2 < ok2)
        return 0;
      // Ray starts inside sphere
      IList << intr(this, ok + sqrt(h2), intr::Leave);
      return 1;
    }

    // Ray starts before sphere
    if (h2 < Threshold)
      return 0;

    DBL h = sqrt(h2);
    if (h < ok)
    {
      // Ray starts outside sphere
      IList << intr(this, ok - h, intr::Enter);
      IList << intr(this, ok + h, intr::Leave);
      return 2;
    }
    // Ray starts inside sphere
    IList << intr(this, ok + h, intr::Leave);
    return 1;
  } /* End of 'AllIntersect' function */

      /* Finding is point shape or nor found
       * ARGUMENTS:
       *   - point in space:
       *       vec3 &Pos;
       * RETURNS:
       *   (BOOL) if point inside TRUE, FALSE otherwise.
       */
      BOOL IsInside( const vec3 &P )
      {
        return ((P - C) & (P - C)) - R2 <= Threshold;
      } /* End of 'IsInside' function */
  }; /* End of 'sphere' class */
} /* End of 'gort' namespace */

#endif // __sphere_h_

/* End of 'sphere.h' file */
