/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : dir.h
 * PURPOSE     : Raytracing project.
 *               Dir light handler module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 27.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __dir_h_
#define __dir_h_
#include "../rt_def.h"

/* Main aplication namespace */
namespace gort
{
  /* Direstion light class */
  namespace lght
  {
    class direction : public gort::light
    {
    public:
      vec3 Ld;     // light direction
      vec3 LColor; // light color
      direction( VOID )
      {
      }
      direction( const vec3 &Direction = {0, -1, 0}, const vec3 &Color = {1, 1, 1})
      {
        Ld = Direction.Normalizing();
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
        L->L = Ld;
        L->Dist = 1000000;
        L->Color = LColor;
        return 1;
      } /* End of 'Shadow' function */
    };
  } /* End of 'light' namespace */
} /* End of 'gort' namespace */


#endif /* __dir_h_ */

/* End of 'dir.h' file */
