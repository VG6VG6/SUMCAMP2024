/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_scene.cpp
 * PURPOSE     : Raytracing project.
 *               Raytracing scene module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 27.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gort.h"
#include "rt_def.h"
#include "rt_scene.h"

/* Application namespace. */
namespace gort
{
  /* Scene ray intersection calculation function
   * ARGUMENTS:
   *   - ray to intersect:
   *       ray &R;
   *   - intersection data:
   *       intr *In;
   * RETURNS:
   *   (BOOL) TRUE if find shape, FALSE otherwise.
   */
  BOOL rt::scene::Intersect( const ray &R, intr *In )
  {
    intr best_intr;
    best_intr.T = -1;

    for (auto shp : Shapes )
    {
      intr current_intr;
      current_intr.Shp = shp;
      if (shp->Intersect(R, &current_intr) && (best_intr.T == -1 || current_intr.T < best_intr.T))
        best_intr = current_intr;
    }
    if (best_intr.T == -1)
      return FALSE;
    *In = best_intr;
    return TRUE;
  } /* End of 'rt::scene::Intersect' function */

  /* Finding all intersection function
   * ARGUMENTS:
   *   - tracing ray:
   *       ray &R;
   *   - intersection contnainer:
   *       intr_list &Il;
   * RETURNS:
   *   (INT) Count of intersection.
   */
  INT rt::scene::AllIntersect( const ray &R, intr_list *Il )
  {
    intr in;
    for (auto shd : Shapes)
      if (shd->Intersect(R, &in))
        Il->operator<<(in);
    return Il->size();
  } /* End of 'rt::scene::AllIntersect' function */

  /* Check intersection function
   * ARGUMENTS:
   *   - tracing ray:
   *       ray &R;
   *   - intersection contnainer:
   *       intr_list &Il;
   * RETURNS:
   *   (INT) Count of intersection.
   */
  INT rt::scene::IsIntersect( const ray &R, intr_list *Il )
  {
    intr in;
    for (auto shd : Shapes)
      if (shd->Intersect(R, &in))
      {
        in.Shp = shd;
        Il->operator<<(in);
        return Il->size();
      }
    return 0;
  } /* End of 'rt::scene::AllIntersect' function

  /* Tracing ray function
    * ARGUMENTS:
    *   - ray to trace:
    *       ray &R;
    * RETURNS:
    *   (vec3) pixel color;
    */
  vec3 rt::scene::Trace( const ray &R, const envi &Media, DBL Weight, INT RecLevel )
  {
    vec3 color = BkgColor;
    intr best_intr;

    if (Intersect(R, &best_intr))
      if (RecLevel < RecMaxLevel)
      {
        RecLevel++;
        if (!best_intr.IsP)
        {
          best_intr.P = R(best_intr.T);
          best_intr.IsP = TRUE;
        }
        if (!best_intr.IsN)
          best_intr.Shp->GetNormal(&best_intr);
        color = Shade(R.Dir, Media, &best_intr, Weight, RecLevel );
        color *= exp(-best_intr.T * Media.Decay);
        RecLevel--;
      }
    return color;
} /* End of rt'::scene::Trace' function */

  /* Fake light function
   * ARGUMENTS:
   *   - ray direction:
   *       vec3 &V;
   *   - shape material:
   *       envi &Media;
   *   - intersection data:
   *       intr *In;
   * RETURNS: 
   *   (vec3) result color.
   */
  vec3 rt::scene::Shade( const vec3 &V, const envi &Media, intr *I, DBL Weight, INT RecLevel )
  {
    shade_info si {I->P, I->N, I->Shp, I->Shp->Material, Media, {1, 0, 0}, {0, 1, 0}};
    //modifiers

    // face forward (si.N):
    DBL vn = V & si.N;
    BOOL IsEnter = TRUE;
    if (vn > 0)
    {
      vn = -vn;
      si.N = -si.N;
      IsEnter = FALSE;
    }

    vec3 color;
    if (I->IsPlane)
    {
      if ((INT)std::floor(si.P[0] + 1000) % 2 == 0 && (INT)std::floorf(si.P[2] + 1000) % 2 == 1 || (INT)std::floor(si.P[0] + 1000) % 2 == 1 && (INT)std::floorf(si.P[2] + 1000) % 2 == 0)
        color = si.Surf.Ka.K * AmbientColor;
      else
        color = (-si.Surf.Ka.K + 1) * AmbientColor;
    }
    else
      color = si.Surf.Ka.K * AmbientColor;
    vec3 R = V + si.N * (2 * (-V & si.N));
    for (auto Lgh : lights)
    {
      light_info li;
      DBL sh = Lgh->Shadow(si.P, &li);

      // cast shadow
      intr_list il;
      if (IsIntersect(ray(si.P + -li.L * Threshold, -li.L), &il) > 0 &&
          il[0].T < li.Dist)
      {
        if (il[0].Shp->Material.Kt.MaxComponent() > Threshold)
          color += il[0].Shp->Material.Kt.K * Trace(ray(si.P + -li.L * Threshold, -li.L), Media, Weight, RecLevel);
        continue; // point in shadow
      }
      // diffuse
      DBL nl = si.N & li.L;
      if (nl > Threshold)
      {
        //color += si.Surf.Kd.K * li.Color * nl; // ??? * sh
        color += si.Surf.Kd.K * li.Color * nl * sh;

        // specular
        if (DBL rl = R & -li.L; rl > Threshold)
          //color += si.Surf.Ks.K * li.Color * pow(rl, si.Surf.Ph); // ??? * sh
          color += si.Surf.Ks.K * li.Color * pow(rl, si.Surf.Ph) * sh;
      }
    }
    // Reflection other scene shapes
    if (si.Surf.Kr.IsUsage && coef(si.Surf.Kr.K * Weight).IsUsage)
      color += si.Surf.Kr.K * Trace(ray(si.P + R * Threshold, R), Media, Weight, RecLevel);

    // Refracted ray accounting
    if (DBL w = si.Surf.Kt.MaxComponent() * Weight; w > ColorThresold)
    {
      DBL eta = IsEnter ?
                si.Media.RefractionCoef / Media.RefractionCoef :
                Air.RefractionCoef / Media.RefractionCoef;
      DBL a1 = -V & si.N;
      vec3 T = (V - si.N * (V & si.N)) * eta - si.N * sqrt(1 - (1 - cos(a1) * cos(a1)) * eta * eta);

      color += si.Surf.Kt.K * Trace(ray(si.P + (T * Threshold), T),
                                    IsEnter ? si.Media : Air, w, RecLevel);
    }
    return color;
  } /* End of 'rt::scene::Shade' function */

  /* Shape class destructor. */
  shape::~shape()
  {
  } /* End of '~shape' destrictor  */

  BOOL shape::Intersect( const ray &R, intr *Intr )
  {
    return FALSE;
  }
  VOID shape::GetNormal( intr *In )
  {
    In->N = vec3(0);
  }
}

 /* End of 'rt_scene' file */