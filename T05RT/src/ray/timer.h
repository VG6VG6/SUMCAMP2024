/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : timer.h
 * PURPOSE     : Raytracing project.
 *               Timer handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 26.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __timer_h_
#define __timer_h_
#include "def.h"
#include <time.h>

struct timer
{
  DBL SyncTime, FPS;
 
  timer() : FPS(300), SyncTime(0)
  {
  }

  void update( void )
  {
    long t;
    static long StartTime = -1, FPSTime, FrameCount;
 
    t = clock();
    if (StartTime == -1)
      StartTime = FPSTime = t;
    SyncTime = (t - StartTime) / (double)CLOCKS_PER_SEC;
    FrameCount++;
    if (t - FPSTime > 3 * CLOCKS_PER_SEC)
    {
      FPS = FrameCount / ((t - FPSTime) / (double)CLOCKS_PER_SEC);
      FPSTime = t;
      FrameCount = 0;
    }
  }
};
#endif // !__timer_h_

