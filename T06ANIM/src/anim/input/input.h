/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : input.h
 * PURPOSE     : Animation project.
 *               Input handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 4.08.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __input_h_
#define __input_h_
#include "keyboard.h"
#include "mouse.h"
#include "timer.h"

/* Application namespace */
namespace gogl
{
  class input : public keyboard, public mouse, public timer
  {
  public:
    input( const HWND &hWnd ) : mouse(hWnd)
    {
    }
    /* Update keyboard data function
     * ARGUMENTS: None.
     * RETURNS:None.
     */
    VOID ResponseAll( VOID )
    {
      keyboard::Response();
      mouse::Response();
      timer::Response();
    } /* End of 'Response' function */

    /* Update keyboard data function
     * ARGUMENTS: None.
     * RETURNS:None.
     */
    VOID ResetAll( VOID )
    {
      keyboard::Reset();
      mouse::Reset();
      //timer::Reset();
    } /* End of 'Response' function */
  }; /* End of 'input' class */
} /* End of 'gogl' namespace */

#endif // __input_h_

/* End of 'mth_matr.h' file */