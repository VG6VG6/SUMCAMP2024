/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : anim.cpp
 * PURPOSE     : Animation project.
 *               Animation module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 31.07.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"
#include "anim.h"

/* Application namespace */
namespace gogl
{
  static class anim_start
  {
  public:
    /* Class constructor */
    anim_start( VOID )
    {
      anim::Get()->Create();
    } /* End of 'anim_start' function */
  } _;

  /* Start processing window
  * ARGUMENTS: None.
  * RETURNS: None.
  */
  VOID anim::Run( VOID )
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
        Render();
      }
    }
  } /* End of 'win::Run' function */

  /* WM_CREATE window message handle function.
   * ARGUMENTS:
   *   - structure with creation data:
   *       CREATESTRUCT *CS;
   * RETURNS:
   *   (BOOL) TRUE to continue creation window, FALSE to terminate.
   */
  BOOL anim::OnCreate( CREATESTRUCT *CS )
  {
    SetTimer(win::hWnd, 30, 2, nullptr);
    if (!render::Init())
      return FALSE;

    return TRUE;
  } /* End of 'anim::OnCreate' function */

  /* WM_DESTROY window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::OnDestroy( VOID )
  {
  } /* End of 'win::OnDestroy' function */

  /* WM_SIZE window message handle function.
   * ARGUMENTS:
   *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
   *       UINT State;
   *   - new width and height of client area:
   *       INT W, H;
   * RETURNS: None.
   */
  VOID anim::OnSize( UINT State, INT W, INT H )
  {
    render::Resize(W, H);
    InvalidateRect(win::hWnd, nullptr, FALSE);
    SendMessage(win::hWnd, WM_TIMER, 30, 0);
  } /* End of 'win::OnSize' function */

  /* WM_MOUSEWHEEL window message handle function.
   * ARGUMENTS:
   *   - mouse window position:
   *       INT X, Y;
   *   - mouse wheel relative delta value:
   *       INT Z;
   *   - mouse keys bits (see MK_*** bits constants):
   *       UINT Keys;
   * RETURNS: None.
   */
  VOID anim::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
  {
    input::mouse::Mdz = Z;
    input::mouse::Mz += Z;
  } /* End of 'win::OnMouseWheel' function */

  /* WM_PAINT window message handle function.
   * ARGUMENTS:
   *   - window device context:
   *       HDC hDC;
   *   - paint message structure pointer:
   *       PAINTSTRUCT *PS;
   * RETURNS: None.
   */
  VOID anim::OnPaint( HDC hDC, PAINTSTRUCT *PS )
  {
  } /* End of 'win::OnPaint' function */ 


  /* WM_ACTIVATE window message handle function.
   * ARGUMENTS:
   *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
   *       UINT Reason;
   *   - handle of active window:
   *       HWND hWndActDeact;
   *   - minimized flag:
   *       BOOL IsMinimized;
   * RETURNS: None.
   */
  VOID anim::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
  {
    IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
    input::ResetAll();
  } /* End of 'win::OnActivate' function */

  /* WM_TIMER window message handle function.
   * ARGUMENTS:
   *   - specified the timer identifier.
   *       INT Id;
   * RETURNS: None.
   */
  VOID anim::OnTimer( INT Id ) 
  {
    Render();
  } /* End of 'win::OnTimer' function */

  /* WM_RBUTTONDOWN and WM_LBUTTONDOWN window message handle function.
  * ARGUMENTS:
  *   - is click was double
  *       BOOL IsDoubleClick;
  *   - mouse position:
  *       INT X, Y;
  *   - mouse keys:
  *       UINT Keys;
  * REURNS: None.
  */
  VOID anim::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
  {
    if (IsDoubleClick)
        FlipFullScreen();
  } /* End of 'win::OnButtonDown' function */

  /* WM_RBUTTONUP and WM_LBUTTONUP window message handle function.
  * ARGUMENTS:
  *   - mouse position:
  *       INT X, Y;
  *   - mouse keys:
  *       UINT Keys;
  * REURNS: None.
  */
  VOID anim::OnButtonUp( INT X, INT Y, UINT Keys )
  {
  
  } /* End of 'win::OnButtonUp' function */

  /* WM_MOUSEMOVE window message handle function.
  * ARGUMENTS: 
  *   - mouse position:
  *       INT X, Y;
  *   - mouse keys:
  *       UINT Keys;
  * RETURNS: None.
  */
  VOID anim::OnMouseMove( INT X, INT Y, UINT Keys )
  {
  } /* End of 'win::OnMouseMove' function */

  /* WM_EXITSIZEMOVE window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::OnExitSizeMove( VOID )
  {
    IsActive = TRUE;
  } /* End of 'win::OnExitSizeMove' function */

  /* WM_ENTERSIZEMOVE window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::OnEnterSizeMove( VOID )
  {
    IsActive = FALSE;
  } /* End of 'win::OnEnterSizeMove' function */

  /* Render scene function
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID anim::Render( VOID )
  {
    if (IsActive)
      input::ResponseAll();
    else
      input::timer::Response();
    FrameStart();
    /* request input */
    Units.Walk([this]( unit * Uni )
    {
      Uni->Response(this);
    });
    
    Units.Walk([this]( unit * Uni )
    {
      Uni->Render(this);
    });
    FrameEnd();
    input::mouse::Mdz = 0;
  } /* End of 'Render' function */

  /* Copy frame to screen.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
  VOID anim::CopyFrame( VOID )
  {
  } /* End of 'CopyFrame' function */

} /* End of 'gogl' namespace */

/* End of 'anim.cpp' file */

