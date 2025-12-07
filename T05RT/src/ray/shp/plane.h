/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : plane.h
 * PURPOSE     : Raytracing project.
 *               Plane shape class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 24.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __plane_h_
#define __plane_h_
#include "def.h"
#include "../rt_def.h"


/* Application namespace. */
namespace gort
{
  /* Plane shape class. */
  class plane : public shape
  {
    vec3 P;
    vec3 N;
  public:

    plane( const vec3 &Pos, const vec3 &Norm, const surface mtl = {} )
    {
      P = Pos;
      N = Norm.Normalizing();
      Material = mtl;
    }
    plane( const vec3 &Pos0, const vec3 &Pos1, const vec3 &Pos2, const surface mtl = {} )
    {
      P = Pos0;
      N = ((Pos2 - Pos0) % (Pos1 - Pos0)).Normalizing();
      Material = mtl;
    }

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection data:
     *       intr *in;
     * RETURNS: None.
     */
    VOID GetNormal( intr *in )
    {
      in->N = N;
    } /* End of 'GetNormal' function */


    BOOL Intersect( const ray &R, intr *Intr )
    {
      DBL D = P & N;
      DBL ND = N & R.Dir;
      if (fabs(ND) <= Threshold)
        return FALSE;

      Intr->T =(D - (N & R.Org)) / ND;
      if (Intr->T < Threshold)
        return FALSE;

      Intr->Shp = (shape *)this;
      Intr->IsPlane = TRUE;
      return TRUE;
    } /* End of 'Intersect' function */

    /* Finding all intersection function
       * ARGUMENTS:
       *   - tracing ray:
       *       ray &R;
       *   - intersection contnainer:
       *       intr_list &Il;
       * RETURNS:
       *   (INT) Count of intersection.
       */
      INT AllIntersect( const ray &R, intr_list &Il )
      {
        intr in;
        DBL D = P & N;
        DBL ND = N & R.Dir;
        if (fabs(ND) <= Threshold)
          return 0;

        in.T = (D - (N & R.Org)) / ND;
        if (in.T < Threshold)
          return 0;

        in.Shp = this;
        Il << in;
        return 1;
      } /* End of 'AllIntersect' function */

  }; /* End of 'plane' class */
} /* End of 'gort' namespace */

#endif // __sphere_h_

/* End of 'plane.h' file */
