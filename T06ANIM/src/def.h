/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : def.h
 * PURPOSE     : Animation project.
 *               Default handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 

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

/* Base includes */
#include <iostream>
#include <functional>
#include <fstream>
#include <cstdio>
#include "mth/mth.h"
#include <vector>
#include <map>

/* Base large integer types */
typedef unsigned long long UINT64;
typedef long long INT64;

/* Application namespace */
namespace gogl
{
  /* Math type definition */
  typedef mth::vec2<FLT>   vec2;
  typedef mth::vec3<FLT>   vec3;
  typedef mth::vec4<FLT>   vec4;
  typedef mth::matr<FLT>   matr;
  typedef mth::camera<FLT> camera;

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

    /* UBO camera buffer send to shader */
    struct CamUBOStruct
    {
      FLT MatrView[16];
      FLT MatrProj[16];
      FLT MatrVP[16];
      vec4 CamLocFrameW;
      vec4 CamDirProjDist;
      vec4 CamRightWp;
      vec4 CamUpHp;
      vec4 CamAtFrameH;
    } UBOCam;

    /* UBO sync buffer send to shader */
    struct SyncUBOStruct
    {
      vec4 SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime;
    } UBOSync;

    /* UBO prim buffer send to shader */
    struct PrimUBOStruct
    {
      FLT MatrWVP[16];
      FLT MatrW[16];
      FLT MatrWInv[16];
      vec4 RndIsWireIsAny;
    } UBOPrim;

    /* UBO material buffer send to shader */
    struct MtlUBOStruct
    {
      vec4 Ka;
      vec4 KdTrans;
      vec4 KsPh;
      bool TextureFlags[8];
    } UBOMtl;
} /* End of 'gogl' namespace */

#endif // __def_h_

/* End of 'def.h' file */
