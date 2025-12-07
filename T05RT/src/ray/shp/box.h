/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : box.h
 * PURPOSE     : Raytracing project.
 *               Box shape class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 24.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __box_h_
#define __box_h_
#include "def.h"
#include "../rt_def.h"
/* Application namespace. */
namespace gort
{
  /* box shape class. */
  class box : public shape
  {
    vec3 B1, B2;
  public:
    box( const vec3 &NB1, const vec3 &NB2 )
    {
      B1 = NB1;
      B2 = NB2;
    }
    box( const vec3 &NB1, const vec3 &NB2, surface Mtl )
    {
      B1 = NB1;
      B2 = NB2;
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
      switch (in->I[0])
      {
      case 0:
        in->N = vec3(1, 0, 0);
        break;
      case 1:
        in->N = vec3(-1, 0, 0);
        break;
      case 2:
        in->N = vec3(0, 1, 0);
        break;
      case 3:
        in->N = vec3(0, -1, 0);
        break;
      case 4:
        in->N = vec3(0, 0, 1);
        break;
      case 5:
        in->N = vec3(0, 0, -1);
        break;
      }
    } /* End of 'GetNormal' function */

    BOOL Intersect( const ray &R, intr *Intr )
    {
      INT tnear_no = -1, tfar_no = -1;
      DBL tnear = -1, tfar = -1, t = -1;

      for (INT i = 0; i < 3; i++)
      {
        if (std::fabs(R.Dir[i]) < Threshold)
        {
          if (R.Org[i] < B1[i] || R.Org[i] > B2[i])
            return FALSE;
        }
        else
        {
          if (R.Dir[i] > Threshold)
          {
            if (R.Org[i] > B2[i])
              return FALSE;
            if (R.Org[i] < B1[i])
            {
              t = (B1[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear < t)
                tnear_no = i * 2, tnear = t;
            }
            t = (B2[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar > t)
              tfar_no = i * 2 + 1, tfar = t;
          }
          else
          {
            if (R.Org[i] < B1[i])
              return FALSE;
            if (R.Org[i] > B2[i])
            {
              t = (B2[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear < t)
                tnear_no = i * 2, tnear = t;
              
            }
            t = (B1[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar > t)
              tfar_no = i * 2 + 1, tfar = t;
            
          }
        }
      }
      if (tnear_no != -1)
      {
        if (tnear > tfar)
          return FALSE;
        Intr->T = tnear;
        Intr->I[0] = tnear_no;
        return TRUE;
      }
      Intr->T = tfar;
      Intr->I[0] = tfar_no;
      return TRUE;
    } /* End of 'Intersection' function */

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
      INT tnear_no = -1, tfar_no = -1;
      DBL tnear = -1, tfar = -1, t = -1;

      for (INT i = 0; i < 3; i++)
      {
        if (std::fabs(R.Dir[i]) < Threshold)
        {
          if (R.Org[i] < B1[i] || R.Org[i] > B2[i])
            return 0;
        }
        else
        {
          if (R.Dir[i] > Threshold)
          {
            if (R.Org[i] > B2[i])
              return 0;
            if (R.Org[i] < B1[i])
            {
              t = (B1[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear - t < Threshold)
                tnear_no = i * 2, tnear = t;
            }
            t = (B2[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar - t > Threshold)
              tfar_no = i * 2 + 1, tfar = t;
          }
          else
          {
            if (R.Org[i] < B1[i])
              return 0;
            if (R.Org[i] > B2[i])
            {
              t = (B2[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear - t < Threshold)
                tnear_no = i * 2, tnear = t;
              
            }
            t = (B1[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar - t > Threshold)
              tfar_no = i * 2 + 1, tfar = t;
            
          }
        }
      }
      if (tnear_no != -1)
      {
        if (tnear - tfar > Threshold)
          return 0;
        in.T = tnear;
        in.I[0] = tnear_no;
        in.Shp = (shape *)this;
        Il << in;
      }
      if (tfar > Threshold)
      {
        in.T = tfar;
        in.I[0] = tfar_no;
        in.Shp = (shape *)this;
        Il << in;
      }
      return Il.size();
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
      if ((B1[0] >= P[0] && B2[0] <= P[0]) ||
          (B2[0] >= P[0] && B1[0] <= P[0]))
        if ((B1[1] >= P[1] && B2[1] <= P[1]) ||
            (B2[1] >= P[1] && B1[1] <= P[1]))
          if ((B1[2] >= P[2] && B2[2] <= P[2]) ||
              (B2[2] >= P[2] && B1[2] <= P[2]))
            return TRUE;
      return FALSE;
    } /* End of 'IsInside' function */
  }; /* End of 'box' class */
} /* End of 'gotr' namespace */

#endif // !__box_h_

/* End of 'box.h' file */
