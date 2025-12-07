/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : point.h
 * PURPOSE     : Raytracing project.
 *               point light handler module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 27.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __point_h_
#define __point_h_
#include "../rt_def.h"

/* Main aplication namespace */
namespace gort
{
  /* Direstion light class */
  namespace lght
  {
    class point : public gort::light
    {
    public:
      DBL LPower;     // light power
      vec3 LP;     // light position
      vec3 LColor; // light color

      point( const vec3 &Position = vec3(2, 2, 0), DBL Power = 10, const vec3 &Color = {1, 1, 1})
      {
        LPower = Power;
        LP = Position;
        LColor = Color;
      }
      /* Shading pixel function
       * ARGUMENTS:
       *   - possition
       *       vec3 &P;
       *   - light to do shade:
       *       light_info *L;
       * RETURN:
       *   (DBL) Shading coefficient.
       */
      DBL Shadow( const vec3 &P, light_info *L ) override
      {
        L->L = (LP - P).Normalize();
        L->Dist = !(LP - P);
        L->Color = LColor;

        return LPower / L->Dist;
      } /* End of 'Shadow' function */
    };
  } /* End of 'light' namespace */
} /* End of 'gort' namespace */


#endif /* __point_h_ */

/* End of 'point.h' file */
