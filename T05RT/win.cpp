/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win.cpp
 * PURPOSE     : Raytracing project.
 *               ????????  module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 24.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gort.h"
#include <Windows.h>
#include "win/win.h"

namespace gort
{
  /* Window destructor */
  win::~win( VOID )
  {
  
  } /* End of 'win' destructor */

  /* Window creation function
   * ARGIMENTS: None.
   * RETURNS: None.
   */
  VOID win::Create( VOID )
  {
    WNDCLASS wc;
    HWND hWnd;
    const CHAR* Class = "My window class";

    wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(win *);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_ERROR);
    wc.lpszMenuName = NULL;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = win::WinFunc;
    wc.lpszClassName = Class;

    if (!RegisterClass(&wc))
    {
      MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
      return;
    }
    /* Create window */
#ifdef NDEBUG
  hWnd = CreateWindow(Class, "gort t05rt project",
      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800,
      nullptr, nullptr, hInstance, reinterpret_cast<VOID *>(this));
#else
  hWnd = CreateWindow(Class, "DEBUG gort t05rt project",
      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
      nullptr, nullptr, hInstance, reinterpret_cast<VOID *>(this));
#endif // !NDEBUG


    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);
  
  } /* End of 'win::Create' function */

  /* Start processing window
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::Run( VOID )
  {
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  } /* End of 'win::Run' function */
}

/* End of 'win.cpp' file */