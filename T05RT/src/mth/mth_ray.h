/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_ray.h
 * PURPOSE     : Raytracing project.
 *               Math ray handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 23.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __math_ray_h
#define __math_ray_h
#include "def.h"

/* Math library namespace */
namespace mth
{
  template<typename Type>
    class ray
    {
    public:
      vec3<Type> Org, Dir; // ray vectors

      /* Ray constructors */
      ray( VOID )
      {
      }
      ray( const vec3<Type> &O, const vec3<Type> &D ) : Dir(D.Normalizing())
      {
        Org = O;
      }

      /* Calculate point from ray function
       * ARGUMENTS: 
       *   - distance from 0 till infinity:
       *       Type T;
       * RETURNS: 
       *   (vec3) result point from ray.
       */
      vec3<Type> operator()( Type T ) const
      {
        return Org + Dir * T;
      } /* End of 'operator()' function */

    }; /* End of 'ray' class */
} /* End of 'mth' namespace */

#endif // !__math_ray_h

/* END OF 'mth_tay.h' FILE */
