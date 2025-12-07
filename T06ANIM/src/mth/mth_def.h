/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_def.h
 * PURPOSE     : Animation project.
 *               Math define handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __mth_def_h_
#define __mth_def_h_

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


#endif /* __mth_def_h_ */

/* End of 'mth_def.h' file */
