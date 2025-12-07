/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : keyboard.h
 * PURPOSE     : Animation project.
 *               Input keyboard handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 */

#ifndef __keyboard_h_
#define __keyboard_h_
#include "def.h"

/* Application namespace */
namespace gogl
{
  /* Keyboard class */
  class keyboard
  {
  public:
    BYTE Keys[256];      /* Keys status in this frame */
    BYTE KeysOld[256];   /* Keys status in prevent frame */
    BYTE KeysClick[256]; /* One clicks keys */

    keyboard() : Keys{0}, KeysOld{0}, KeysClick{0}
    {
      
    }

    /* Update keyboard data function
     * ARGUMENTS: None.
     * RETURNS:None.
     */
    VOID Response( VOID )
    {
      memcpy(KeysOld, Keys, 256);  /* Copy old keys */

      GetKeyboardState(Keys);

      for (INT i = 0; i < 256; i++)
      {
        Keys[i] >>= 7;
        KeysClick[i] = Keys[i] && !KeysOld[i];   /* Check onec click */
      }
    } /* End of 'Response' function */

    /* Reset keyboard data function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Reset( VOID )
    {
      ZeroMemory(Keys, 256);
      ZeroMemory(KeysOld, 256);
      ZeroMemory(KeysClick, 256);
    }

  }; /* End of 'input' class */
} /* End of 'gogl' namespace */

#endif // __keyboard_h_

/* End of 'mth_matr.h' file */