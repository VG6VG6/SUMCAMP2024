/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mouse.h
 * PURPOSE     : Animation project.
 *               Input mause handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 */

#ifndef __mouse_h_
#define __mouse_h_
#include "def.h"

/* Application namespace */
namespace gogl
{
  /* Mouse class */
  class mouse
  {
    HWND MhWnd;
  public:
    INT Mx, My, Mz, Mdx, Mdy, Mdz;

    mouse( VOID ) : Mx(0), My(0), Mz(0), Mdx(0), Mdy(0), Mdz(0)
    {
    }
    mouse( const HWND &NhWnd )
    {
      MhWnd = NhWnd;
      Reset();
    }

    /* Reset mouse data function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Reset( VOID )
    {
      Response();
      Mdx = 0, Mdy = 0, Mdz = 0;
    } /* End of 'Reset' function */

    /* Update mouse data function
     * ARGIMENTS: None.
     * RETURNS: None.
     */
    VOID Response( VOID )
    {
      POINT pt;

      GetCursorPos(&pt);
      ScreenToClient(MhWnd, &pt);
 
      Mdx = pt.x - Mx;
      Mdy = pt.y - My;

      Mx = pt.x;
      My = pt.y;

    } /* End of 'Response' function */

  }; /* End of 'input' class */
} /* End of 'gogl' namespace */

#endif // __mouse_h_

/* End of 'mouse.h' file */