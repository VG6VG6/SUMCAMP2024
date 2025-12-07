/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_def.h
 * PURPOSE     : Raytracing project.
 *               Math define handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 23.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_def_h
#define __mth_def_h

#include <cmath>
#include <iostream>

#ifdef WIN32
#include <commondf.h>
#else
#define WIN32
#include <commondf.h>
#undef WIN32
#endif // !WIN32

#define R2D(a) ((a) / PI * 180)
#define D2R(a) ((a) / 180 * PI)

typedef FLOAT FLT;
typedef DOUBLE DBL;

/* Math library namespace */
namespace mth
{
  template<typename Type> class vec2;
  template<typename Type> class vec3;
  template<typename Type> class vec4;
  template<typename Type> class matr;
  template<typename Type> class camera;
  template<typename Type> class ray;
}


#endif /* __mth_def_h */

/* End of 'mth_def.h' file */
