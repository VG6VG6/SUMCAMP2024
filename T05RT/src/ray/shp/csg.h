;/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : sphere.h
 * PURPOSE     : Raytracing project.
 *               Sphere class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 26.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __csg_h_
#define __csg_h_
#include "def.h"
#include "../rt_def.h"

/* Application namespace. */
namespace gort
{
  /* Sphere shape class. */
  class csg : public shape
  {
    shape *A, *B;
    INT CSGType;
  public:

    /* CSG constructor, Type(0 - merge, 1 - intersection, 2 - subtrack) */
    csg( shape *Shp1, shape *Shp2, INT Type ) : A(Shp1), B(Shp2), CSGType(Type)
    {
    }
    ~csg()
    {
      delete A;
      delete B;
    }
    /* Get normal function.
     * ARGUMENTS:
     *   - intersection data:
     *       intr *in;
     * RETURNS: None.
     */
    VOID GetNormal( intr *in )
    {
      if (in->I[4])
        return A->GetNormal(in);
      return B->GetNormal(in);
    } /* End of 'GetNormal' function */

    /* Find intersection function
     * ARGUMENTS:
     *   - tracing ray:
     *       ray &R;
     *   - intersectin:
     *      intr *Intr;
     */
    BOOL Intersect( const ray &R, intr *Intr )
    {
      intr InA, InB;

      if (CSGType == 0)
      {
        if (A->Intersect(R, &InA) || B->Intersect(R, &InB))
        {
          if (InA.T > Threshold)
            if (InA.T > InB.T && InB.T > Threshold)
              Intr->T = InB.T, Intr->I[4] = 0;
            else
              Intr->T = InA.T, Intr->I[4] = 1;
          else
            Intr->T = InB.T, Intr->I[4] = 0;
          return TRUE;
        }
        return FALSE;
      }

      if (CSGType == 1)
      {
        intr_list IntrListA, IntrListB;
        DBL tbest = -1;
        if (A->AllIntersect(R, IntrListA) < 1 || B->AllIntersect(R, IntrListB) < 1)
          return FALSE;

        for (auto x : IntrListA)
        {
          x.P = R(x.T);
          if (B->IsInside(x.P) && (tbest == -1 || tbest > x.T))
            tbest = x.T, Intr->I[4] = 1;
        }

        for (auto x : IntrListB)
        {
          x.P = R(x.T);
          if (A->IsInside(x.P) && (tbest == -1 || tbest > x.T))
            tbest = x.T, Intr->I[4] = 0;
        }
        if (tbest < Threshold)
          return FALSE;
        
        Intr->T = tbest;
        return TRUE;
      }
      if (CSGType == 2)
      {
        intr_list IntrListA, IntrListB;
        DBL tbest = -1;
        A->AllIntersect(R, IntrListA);
        B->AllIntersect(R, IntrListB);

        for (auto x : IntrListA)
        {
          x.P = R(x.T);
          if (!B->IsInside(x.P))
            if (tbest == -1 || tbest > x.T)
              tbest = x.T, Intr->I[4] = 1;
        }
        for (auto x : IntrListB)
        {
          x.P = R(x.T);
          if (A->IsInside(x.P) && (tbest == -1 || tbest > x.T))
            tbest = x.T, Intr->I[4] = 0;
        }
        if (tbest < Threshold)
          return FALSE;
        Intr->T = tbest;
        return TRUE;
      }
      return FALSE;
    } /* End of 'Intersect' function */
  }; /* End of 'sphere' class */
} /* End of 'gort' namespace */

#endif // __csg_h_

/* End of 'sphere.h' file */
