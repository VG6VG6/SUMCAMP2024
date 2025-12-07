/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : def.h
 * PURPOSE     : Raytracing project.
 *               Default handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 23.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __def_h_
#define __def_h_

#ifdef WIN32
#include <commondf.h>
#else
#define WIN32
#include <commondf.h>
#undef WIN32
#endif // !WIN32

#define BOOL bool

/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
#  define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static struct __Dummy
{
  /* Structure constructor */
  __Dummy( VOID )
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;
#endif /* _DEBUG */
                         
#ifdef _DEBUG
#  ifdef _CRTDBG_MAP_ALLOC
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#  endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

#include "mth/mth.h"

#include <vector>

/* base large integer types */
typedef unsigned long long UINT64;
typedef long long INT64;

/* Project namespace */
namespace gort
{
  /* Math type definition */
  typedef mth::vec2<DBL>   vec2;
  typedef mth::vec3<DBL>   vec3;
  typedef mth::vec4<DBL>   vec4;
  typedef mth::matr<DBL>   matr;
  typedef mth::ray<DBL>    ray;
  typedef mth::camera<DBL> camera;

  /* Stock class */
  template<typename Type>
    class stock : public std::vector<Type>
    {
    public:
      stock & operator<<( const Type &X )
      {
        this->push_back(X);
        return *this;
      }
      
      template<class WalkType>
        void Walk( WalkType W )
        {
          for (auto &x : *this)
            W(x);
        }
    }; /* End of 'stock' class */

} /* End of 'gort' namespace */

#endif // __def_h_


