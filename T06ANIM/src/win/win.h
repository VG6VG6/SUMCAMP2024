/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win.h
 * PURPOSE     : Animation project.
 *               Window class handler module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __win_h_
#define __win_h_
#include <Windows.h>

/* Application namespace */
namespace gogl
{
  /* Window class */
  class win
  {
  protected:
    HWND hWnd;           // window handle
    HINSTANCE hInstance; // application handle
  private:
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );
    BOOL IsFullScreen;
    RECT FullScreenSaveRect;
    INT MouseWheel;
  public:
    INT W, H;            // window size
    BOOL IsActive;

    /* Window default constrictor
     * ARGUMENTS:
     *   - handle of application instance:
     *       HINSTANCE hInst;
    */
    win( HINSTANCE hInst = GetModuleHandle(nullptr) ) : hInstance(hInst), W(0), H(0), IsFullScreen(FALSE), MouseWheel(0), IsActive(FALSE)
    {
    } /* End of window constrictor */

    /* Virtual window destructor */
    virtual ~win( VOID );

    /* Window creation function
     * ARGIMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Create( VOID );

    /* Start dispatch window messages function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Run( VOID );

    /* 
     * 
     */
    //virtual VOID Idle( VOID );
    /* Flip full screen function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FlipFullScreen( VOID );

  private:
    /* Message cracks function */
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

#endif // __win_h_

/* End of 'win.h' file */
