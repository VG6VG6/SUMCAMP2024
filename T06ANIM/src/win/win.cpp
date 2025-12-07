/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win.cpp
 * PURPOSE     : Animation project.
 *               Window main module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"
#include "win.h"

/* Main application namespace */
namespace gogl
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
    const CHAR* Class = "My window class"; // Set window class

    wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS; // Set window style
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
  hWnd = CreateWindow(Class, "gogl t06anim project",
      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
      nullptr, nullptr, hInstance, reinterpret_cast<VOID *>(this));

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

    while (TRUE) {
      if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        if (msg.message == WM_QUIT)
          break;
        else
        {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
        }
      else
      {
        /* Idle */
      }
    }
  } /* End of 'win::Run' function */

  /* Flip full screen function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::FlipFullScreen( VOID )
  {
    static RECT SaveRC; /* Save old window size */
 
    if (!IsFullScreen)
    {
      HMONITOR hMon;
      MONITORINFOEX moninfo;
      RECT rc;
 
      IsFullScreen = TRUE;
 
      /* Save old window size and position */
      GetWindowRect(hWnd, &SaveRC);
 
      /* Get closest monitor */
      hMon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
      moninfo.cbSize = sizeof(moninfo);
      GetMonitorInfo(hMon, (MONITORINFO *)&moninfo);
 
      rc = moninfo.rcMonitor;
      AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);
 
 
      /* Restore window size and position */
      SetWindowPos(hWnd, HWND_TOP,
        rc.left, rc.top,
        rc.right - rc.left, rc.bottom - rc.top,
        SWP_NOOWNERZORDER);
    }
    else
    {
      IsFullScreen = FALSE;
 
      /* Restore window size and position */
      SetWindowPos(hWnd, HWND_NOTOPMOST,
        SaveRC.left, SaveRC.top,
        SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
        SWP_NOOWNERZORDER);
    }
  } /* End of 'FlipFullScreen' function */

} /* End of 'gogl' namespace */

/* End of 'win.cpp. file */
