/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win.h
 * PURPOSE     : Raytracing project.
 *               Window class handler module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 23.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __win_h_
#define __win_h_

#include "gort.h"
#include <Windows.h>

namespace gort
{
  /* Window class */
  class win
  {
  protected:
    HWND hWnd;           // window handle
    INT W, H;            // window size
    HINSTANCE hInstance; // application handle
  private:
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam );

    BOOL IsFullScreen;
    RECT FullScreenSaveRect;
    INT MouseWheel;
  public:
    BOOL IsActive;

    win( HINSTANCE hInst = GetModuleHandle(nullptr) ) : hInstance(hInst), W(0), H(0), IsFullScreen(FALSE), MouseWheel(0), IsActive(FALSE)
    {
    }
    virtual ~win( VOID );
    virtual VOID Create( VOID );
    virtual VOID Run( VOID );
    VOID FlipFullScreen( VOID );

  private:
    // message cracks
    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax );
    virtual BOOL OnCreate( CREATESTRUCT *CS );
    virtual VOID OnDestroy( VOID );
    virtual BOOL OnEraseBkgnd( HDC hDC );
    virtual VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps );
    virtual VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
    virtual VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
    virtual VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );
    virtual VOID OnButtonUp( INT X, INT Y, UINT Keys );
    virtual VOID OnMouseMove( INT X, INT Y, UINT Keys );
    virtual VOID OnSize( UINT State, INT W, INT H );
    virtual VOID OnTimer( INT Id );
    virtual VOID OnDropFiles( HDROP hDrop );
    virtual VOID OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem );
    virtual LRESULT OnNotify( INT Id, NMHDR *NoteHead );
    virtual VOID OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify );
    virtual VOID OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags);
    virtual VOID OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu );
    virtual VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos );
    virtual VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos );
    virtual VOID OnExitSizeMove( VOID );
    virtual VOID OnEnterSizeMove( VOID );
    virtual LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam );
  };
}

#endif // !__win_h_

/* End of 'win.h' file */