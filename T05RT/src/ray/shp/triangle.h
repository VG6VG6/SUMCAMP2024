/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : triangle.h
 * PURPOSE     : Raytracing project.
 *               Triabgle shape class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 24.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __triangle_h_
#define __triangle_h_
#include "def.h"
#include "../rt_def.h"

/* Application namespace. */
namespace gort
{
  /* triangle shape class. */
  class triangle : public shape
  {
    vec3 P0, P1, P2;
    vec3 N, N1, N2, N3;
    DBL D;
    vec3 U1, V1;
    DBL u0, v0;
  
  public:
    triangle( const vec3 &Pos0, const vec3 &Pos1, const vec3 &Pos2 )
    {
      vec3 S1, S2;

      P0 = Pos0, P1 = Pos1, P2 = Pos2;
      S1 = P1 - P0;
      S2 = P2 - P0;
      N = (S1 % S2).Normalizing();
      D = N & P0;

      U1 = (S1 * (S2 & S2) - S2 * (S1 & S2)) / (((S1 & S1) * (S2 & S2)) - (S1 & S2) * (S1 & S2));
      u0 = P0 & U1;

      V1 = (S2 * (S1 & S1) - (S1 * (S1 & S2))) / (((S2 & S2) * (S1 & S1)) - ((S1 & S2) * (S1 & S2)));
      v0 = P0 & V1;
    }
    triangle( const vec3 &Pos0, const vec3 &Pos1, const vec3 &Pos2, const vec3 &Norm1, const vec3 &Norm2, const vec3 &Norm3 ) : N1{Norm1}, N2{Norm2}, N3{Norm3}
    {
      vec3 S1, S2;

      P0 = Pos0, P1 = Pos1, P2 = Pos2;
      S1 = P1 - P0;
      S2 = P2 - P0;
      N = (S1 % S2).Normalizing();
      D = N & P0;

      U1 = (S1 * (S2 & S2) - S2 * (S1 & S2)) / (((S1 & S1) * (S2 & S2)) - (S1 & S2) * (S1 & S2));
      u0 = P0 & U1;

      V1 = (S2 * (S1 & S1) - (S1 * (S1 & S2))) / (((S2 & S2) * (S1 & S1)) - ((S1 & S2) * (S1 & S2)));
      v0 = P0 & V1;
    }
    /* Get normal function.
     * ARGUMENTS:
     *   - intersection data:
     *       intr *in;
     * RETURNS: None.
     */
    VOID GetNormal( intr *in )
    {
      in->N = N1 * (1 - in->D[0] - in->D[1]) + N2 * in->D[0] + N3 * in->D[1];
    } /* End of 'GetNormal' function */

    BOOL Intersect( const ray &R, intr *Intr )
    {
      DBL u, v;
      DBL ND = N & R.Dir;
      if (fabs(ND) <= Threshold)
        return FALSE;

      Intr->T =(D - (N & R.Org)) / ND;
      if (Intr->T < Threshold)
        return FALSE;

      Intr->P = R(Intr->T);
      u = (Intr->P & U1) - u0;
      v = (Intr->P & V1) - v0;
      Intr->D[0] = u;
      Intr->D[1] = v;
      if (u >= 0 && v >= 0 && (u + v) <= 1)
      {
        Intr->Shp = this;
        return TRUE;
      }
      return FALSE;
    }
  }; /* End of 'triangle' class */
} /* End of 'gotr' namespace */

#endif // !__triangle_h_



/* End of 'triangle.h' file */

