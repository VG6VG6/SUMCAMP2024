/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_scene.h
 * PURPOSE     : Raytracing project.
 *               Raytracing declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 27.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_scene_h_
#define __rt_scene_h_
#include <thread>
#include "rt_def.h"

/* Application namespace */
namespace gort
{
  /* Ray tracting namespace. */
  namespace rt
  {
    /* Scene class */
    class scene
    {
    public:
      stock<shape *> Shapes; // Shapes stock
      stock<light *> lights;
      // Color def params
      vec3 
        AmbientColor, 
        BkgColor = {0.30, 0.47, 0.80}, 
        FagColor; 
      DBL FogStart, FogEnd;         // Fog parametrs
      INT RecMaxLevel = 4;
      DBL ColorThresold = 0.0001;
      envi Air = {1.0003, 0.1};
      // Sync flag
      std::atomic_bool IsRenderActive = FALSE;
      std::atomic_bool IsToBeStop = FALSE;
      std::atomic_bool IsReadyToFinish = FALSE;
      std::atomic_int StartRow = 0;

      BOOL Intersect( const ray &R, intr *Intr );
      INT AllIntersect( const ray &R, intr_list *Il );
      INT IsIntersect( const ray &R, intr_list *Il );
      vec3 Shade( const vec3 &V, const envi &Media, intr *I, DBL Weight, INT RecLevel );
      vec3 Trace( const ray &R, const envi &Media, DBL Weight, INT RecLevel );

      /* Obtion add shape to stock function
       * ARGUMENTS:
       *   - new shape:
       *       shape *Shp;
       * RETURN:
       *   (scene &) this scene.
       */
      scene & operator<<( shape *Shp )
      {
        Shapes << Shp;
        return *this;
      } /* End of 'operator<<' function */

      /* Obtion add light to stock function
       * ARGUMENTS:
       *   - new light:
       *       light *lgh;
       * RETURN:
       *   (scene &) this scene.
       */
      scene & operator<<( light *lgh )
      {
        lights << lgh;
        return *this;
      } /* End of 'operator<<' function */

      /* Clear allocated memory function
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID Clear( VOID )
      {
        for (auto x : Shapes)
          delete x;
        for (auto x : lights)
          delete x;
      } /* End of 'Clear' function */

    }; /* End of 'Scene' class */
  } /* End of 'rt' namespaec */
}

#endif // !__rt_scene_h_


/* End of 'rt_scene.h' */