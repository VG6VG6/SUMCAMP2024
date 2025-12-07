/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_win.h
 * PURPOSE     : Raytracing project.
 *               Ray tracing handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 26.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_win_h
#define __rt_win_h
#include "def.h"

#include <iostream>
#include "win/win.h"
#include "frame.h"
#include "rt_scene.h"
#include "shp/shapes.h"
#include "lgh/lights.h"
#include "timer.h"

#define RENDER_SECONDS 5
#define COUNT_IN_SECOND 48

/* Aplication namespace. */
namespace gort
{
  /* Ray tracing window class */
  class rt_win : public win
  {
  public:
    frame Frm;         // Ray tracing window frame
    camera Cam;        // Camera
    rt::scene Scene;   // Scene class
    timer Time;        // Timer class

    // Background brush
    HBRUSH hBrBack;

    // Mouse store coordinates
    INT MouseX, MouseY;
 
    // Image data
    INT
      ImgW = 1280, ImgH = 720,        // Image size
      ImgX = 0, ImgY = 0,              // Image position
      ImgZoom = 1,                     // Image zoom factor
      ImgZoomW = 1280, ImgZoomH = 720; // Image zoomed size

    /* Ray tracing window destructor */
    ~rt_win()
    {
      Scene.Clear();
    }
  private:
    /* Update frame image drawing data function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID )
    {
      // Correct image position
    
      // Horizontal
      if (ImgZoomW <= W)
        // inside
        ImgX = (W - ImgZoomW) / 2;
      else
      {
        // shift left border
        if (ImgX + ImgZoomW < W)
          ImgX = W - ImgZoomW;
        // shift right border
        if (ImgX > 0)
          ImgX = 0;
      }
      // Vertical
      if (ImgZoomH <= H)
        // inside
        ImgY = (H - ImgZoomH) / 2;
      else
      {
        // shift top border
        if (ImgY + ImgZoomH < H)
          ImgY = H - ImgZoomH;
        // shift bottom border
        if (ImgY > 0)
          ImgY = 0;
      }
 
      // Correct scroll bars
      auto scrl =
        [this]( INT ScrollType, INT &ImgPos, INT &ImgSize, INT &WinSize )
        {
          SCROLLINFO ScrollInfo {sizeof(SCROLLINFO), SIF_PAGE | SIF_POS | SIF_RANGE};
    
          if (ImgSize > WinSize)
            SetScrollPos(hWnd, ScrollType, -ImgPos, FALSE);
    
          // Update horizontal/vertical scroll bar data
          if (Frm.W == 0 || Frm.H == 0 || ImgSize <= WinSize)
          {
            // Remove horizontal/vertical scroll bar
            ScrollInfo.nMin = ScrollInfo.nMax = 0;
            SetScrollInfo(hWnd, ScrollType, &ScrollInfo, TRUE);
          }
          else
          {
            GetScrollInfo(hWnd, ScrollType, &ScrollInfo);
            ScrollInfo.nPos = -ImgPos; /// !!!
            ScrollInfo.nMin = 0;
            ScrollInfo.nMax = ImgSize;
            ScrollInfo.nPage = WinSize;
            SetScrollInfo(hWnd, ScrollType, &ScrollInfo, TRUE);
          }
        };
      scrl(SB_HORZ, ImgX, ImgZoomW, W);
      scrl(SB_VERT, ImgY, ImgZoomH, H);
    } /* End of 'Update' function */

    /* Flip full screen function.
     * ARGUMENTS:
     *   - window handle:
     *       HWND hWnd;
     * RETURNS: None.
     */
    VOID FlipFullScreen( HWND hWnd )
    {
      static BOOL IsFullScreen = FALSE; /* store current mode */
      static RECT SaveRC;               /* save old window size */
 
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

    /* Ray tracing frame resize function
     * ARGUMENTS: 
     *   - new frame size:
     *       (INT) NewW, NewH;
     * ARGUMENTS: None.
     */
    VOID Resize( INT NewW, INT NewH )
    {
      Frm.Resize(NewW, NewH);
      Cam.Resize(NewW, NewH);
    }

    /* Render ray tacing frame function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID )
    {
      Cam.SetLocAtUp(vec3(sin(Time.SyncTime) * 5, 17, -20), vec3(0, 0, 0), vec3(0, 1, 0));
      INT n = std::thread::hardware_concurrency() - 1;
#ifndef NDEBUG
      //n = 1;
      std::cout << "Debug mode." << std::endl;
#endif /* NDEBUG */
      std::vector<std::thread> Ths;
      Ths.resize(n);
      Scene.StartRow = 0;
      for (INT i = 0; i < n; i++)
      {
        Ths[i] = std::thread(
        [&]( VOID )
          {
            INT y = 0;
            while (y < Frm.H)
            {
              y = Scene.StartRow++;
              for (INT xs = 0; xs < Frm.W; xs++)
              {
                if (Scene.IsToBeStop)
                  return;
                ray R = Cam.FrameRay(xs + 0.5, y - 0.5);
                vec3 color = Scene.Trace(R, Scene.Air, 1, 0);
                Frm.PutPixel(xs, y, frame::ToRGB(color[0], color[1], color[2]));
              }
            }
          });
      }
      for (INT i = 0; i < n; i++)
        Ths[i].join();
    } /* End of 'Render' function */

    /* Render ray tacing frame function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID RenderAnti( VOID )
    {
      Cam.SetLocAtUp(vec3(sin(Time.SyncTime) * 5, 17, -20), vec3(0, 0, 0), vec3(0, 1, 0));
      INT n = std::thread::hardware_concurrency() - 1;
#ifndef NDEBUG
      //n = 1;
      std::cout << "Debug mode." << std::endl;
#endif /* NDEBUG */
      std::vector<std::thread> Ths;
      Ths.resize(n);
      Scene.StartRow = 0;
      for (INT i = 0; i < n; i++)
      {
        Ths[i] = std::thread(
        [&]( VOID )
          {
            INT y = 0;
            while (y < Frm.H)
            {
              y = Scene.StartRow++;
              for (INT xs = 0; xs < Frm.W; xs++)
              {
                if (Scene.IsToBeStop)
                  return;
                ray R = Cam.FrameRay(xs + 0.5, y - 0.5);
                vec3 color = Scene.Trace(R, Scene.Air, 1, 0);
                Frm.PutPixel(xs, y, frame::ToRGB(color[0], color[1], color[2]));
              }
            }
          });
      }
      for (INT i = 0; i < n; i++)
        Ths[i].join();
    } /* End of 'Render' function */

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H ) override
    {
      if (Frm.W != 0 && Frm.H != 0)
      {
        ImgX = (W - ImgZoomW) / 2;
        ImgY = (H - ImgZoomH) / 2;
        Update();
        //Resize(W, H);
        InvalidateRect(hWnd, nullptr, FALSE);
      }
    } /* End of 'OnSize' function */

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    VOID OnPaint( HDC hDC, PAINTSTRUCT *PS ) override
    {
      SelectObject(hDC, GetStockObject(NULL_PEN));
      if (hBrBack != nullptr)
        SelectObject(hDC, hBrBack);
      else
        SelectObject(hDC, GetStockObject(GRAY_BRUSH));
      if (Frm.W != 0 && Frm.H != 0)
      {
        // Draw left rect
        if (ImgX > 0)
          Rectangle(hDC, 0, ImgY, ImgX + 1, ImgY + ImgZoomH + 1);
        // Draw top rect
        if (ImgY > 0)
          Rectangle(hDC, 0, 0, W + 1, ImgY + 1);
        // Draw right rect
        if (W - ImgX - ImgZoomW  > 0)
          Rectangle(hDC, ImgX + ImgZoomW, ImgY, W + 1, ImgY + ImgZoomH + 1);
        // Draw bottom rect
        if (H - ImgY - ImgZoomH > 0)
          Rectangle(hDC, 0, ImgY + ImgZoomH, W + 1, H + 1);
        Frm.Draw(hDC, ImgX, ImgY, ImgZoomW, ImgZoomH);
      }
      else
        Rectangle(hDC, 0, 0, W + 1, H + 1); 
      // Frm.Draw(hDC, 0, 0, Frm.W, Frm.H);
    } /* End of 'OnPaint' function */ 

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id ) override
    {
      if (Id == 30)
      {
        static INT cnt = 0;
        if (cnt < RENDER_SECONDS * COUNT_IN_SECOND)
        {
          if (!Scene.IsRenderActive)
          {
            Time.SyncTime = cnt * 1.0 / COUNT_IN_SECOND;
            Scene.IsRenderActive = TRUE;
            Scene.IsToBeStop = FALSE;
            Scene.IsReadyToFinish = FALSE;
            std::cout << "Start render scene" << std::endl;
            std::thread Th;
            Th = std::thread(
              [&]( VOID )
              {
                LONG tt = clock();
                Render();
                tt = clock() - tt;
                INT Seconds = (INT)((DBL)tt / CLOCKS_PER_SEC);

                std::cout <<
                  std::fixed << (DBL)tt / CLOCKS_PER_SEC <<
                  " :: " << std::setfill('0') << std::setw(2) <<
                                                  Seconds / 60 / 60 <<
                  ":" << std::setfill('0') << std::setw(2) <<
                                                  Seconds / 60 % 60 <<
                  ":" << std::setfill('0') << std::setw(2) <<
                                                  Seconds % 60 << "\r";
                
                Frm.SaveTGA(std::string("bin/images/Saves/") + std::to_string(cnt) + std::string(".tga"), "VG6 Ray Tracing", 
                  {Seconds / 60 / 60, Seconds / 60 % 60, Seconds % 60});
                std::cout << "Scene rendered" << Seconds / 60 / 60 << ", " << Seconds / 60 % 60 << ", " << Seconds % 60 << std::endl;
                InvalidateRect(hWnd, NULL, FALSE);
                UpdateWindow(hWnd);
                Scene.IsRenderActive = FALSE;
                Scene.IsReadyToFinish = TRUE;
                if (!Scene.IsToBeStop)
                  SendMessage(hWnd, WM_TIMER, 30, 0);
              });
            Th.detach();
            cnt++;
          }
        }
      }
      InvalidateRect(hWnd, NULL, FALSE);
    } /* End of 'OnTiner' function */

    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS ) override
    {
      SetTimer(hWnd, 0, 100, nullptr);
      Resize(200 * 16, 200 * 9);
      ImgZoomW = 400;
      ImgZoomH = 300;
      return 1;
    } /* End of 'OnCreate' function */

    /* WM_MOUSEWHEEL window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse wheel delta value (120 points per rotate):
     *       INT Z;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys ) override
    {
      INT
        OldZoomW = ImgZoomW,
        OldZoomH = ImgZoomH;
 
      if (Z > 0 && ImgZoom < 13 && (ImgZoom < 0 || (UINT64)ImgW * ImgH * ((ImgZoom + 1) * (ImgZoom + 1)) <= 1000000000LL))
        ImgZoom++, ImgZoom = ImgZoom == 0 ? 1 : ImgZoom;
      else if (Z < 0 && ImgZoom > -12)
        ImgZoom--, ImgZoom = (ImgZoom == 0 || ImgZoom == -1) ? -2 : ImgZoom;
      if (ImgZoom > 0)
        ImgZoomW = ImgW * ImgZoom, ImgZoomH = ImgH * ImgZoom;
      else
        ImgZoomW = ImgW / -ImgZoom, ImgZoomH = ImgH / -ImgZoom;
 
      if (OldZoomW != ImgZoomW)
        ImgX = -(INT)(((DOUBLE)ImgZoomW * (-ImgX + X) / OldZoomW - X));
      if (OldZoomH != ImgZoomH)
        ImgY = -(INT)(((DOUBLE)ImgZoomH * (-ImgY + Y) / OldZoomH - Y));
 
      Update();
      InvalidateRect(hWnd, nullptr, FALSE);
    } /* End of 'OnMouseWheel' function */
 
    /* WM_*BUTTONDOWN window message handle function.
     * ARGUMENTS:
     *   - double click flag:
     *       BOOL IsDoubleClick;
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) override
    {
      if (IsDoubleClick)
        FlipFullScreen(hWnd);
      SetCapture(hWnd);
      MouseX = X;
      MouseY = Y;
 
      if (Keys & MK_MBUTTON)
      {
        X -= ImgX;
        Y -= ImgY;
        if (ImgZoom < 0)
        {
          X *= -ImgZoom;
          Y *= -ImgZoom;
        }
        else
        {
          X /= ImgZoom;
          Y /= ImgZoom;
        }
        printf("c: %08X x:%5d y:%5d\n", Frm.GetPixel(X, Y), X, Y);
        ray r = Cam.FrameRay(X + 0.5, Y + 0.5);
        vec3 c = Scene.Trace(r, Scene.Air, 1, 0);
 
        printf("Render (%d,%d):RGB(%.3f,%.3f,%.3f)\n", X, Y, c[0], c[1], c[2]);
      }
    } /* End of 'OnButtonDown' function */
 
    /* WM_*BUTTONUP window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonUp( INT X, INT Y, UINT Keys ) override
    {
      ReleaseCapture();
    } /* End of 'OnButtonUp' function */
 
    /* WM_MOUSEMOVE window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnMouseMove( INT X, INT Y, UINT Keys ) override
    {
      if (Keys & MK_LBUTTON)
      {
        ImgX += X - MouseX;
        ImgY += Y - MouseY;
        MouseX = X;
        MouseY = Y;
        Update();
        InvalidateRect(hWnd, NULL, FALSE);
      }
      if (Keys & MK_RBUTTON)
      {
        X -= ImgX;
        Y -= ImgY;
        if (ImgZoom < 0)
        {
          X *= -ImgZoom;
          Y *= -ImgZoom;
        }
        else
        {
          X /= ImgZoom;
          Y /= ImgZoom;
        }
        printf("c: %08X x:%5d y:%5d\n", Frm.GetPixel(X, Y), X, Y);
      }
    } /* End of 'OnMouseMove' function */
 
    /* WM_HSCROLL message handle function.
     * ARGUMENTS:
     *   - handle of scroll window or nullptr for window scroll bars:
     *       HWND hWndCtl;
     *   - scrool bar request code (see SB_***):
     *      UINT Code;
     *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
     *      INT Pos;
     * RETURNS: None.
     */
    VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos ) override
    {
      switch (Code)
      {
      case SB_LINEDOWN:
        ImgX--;
        break;
      case SB_LINEUP:
        ImgX++;
        break;
      case SB_PAGEDOWN:
        ImgX -= W;
        break;
      case SB_PAGEUP:
        ImgX += W;
        break;
      case SB_THUMBTRACK:
        ImgX = -Pos;
        break;
      }
      Update();
      InvalidateRect(hWnd, NULL, FALSE);
    } /* End of 'OnHScroll' function */
 
    /* WM_VSCROLL message handle function.
     * ARGUMENTS:
     *   - handle of scroll window or nullptr for window scroll bars:
     *       HWND hWndCtl;
     *   - scrool bar request code (see SB_***):
     *      UINT Code;
     *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
     *      INT Pos;
     * RETURNS: None.
     */
    VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos ) override
    {
      switch (Code)
      {
      case SB_LINEDOWN:
        ImgY--;
        break;
      case SB_LINEUP:
        ImgY++;
        break;
      case SB_PAGEDOWN:
        ImgY -= H;
        break;
      case SB_PAGEUP:
        ImgY += H;
        break;
      case SB_THUMBTRACK:
        ImgY = -Pos;
        break;
      }
      Update();
      InvalidateRect(hWnd, NULL, FALSE);
    } /* End of 'OnVScroll' function */

  /* Window message universal handle function.
   * Should be returned 'DefWindowProc' call result.
   * ARGUMENTS:
   *   - message type (see WM_***):
   *      UINT Msg;
   *   - message 'word' parameter:
   *      WPARAM wParam;
   *   - message 'long' parameter:
   *      LPARAM lParam;
   * RETURNS:
   *   (LRESULT) message depende return value.
   */
  LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam )
  {
    switch(Msg)
    {
      case WM_KEYDOWN:
        if (wParam == 'C')
        {
          Frm.Fill(0x00302908);
        }
        if (wParam == 'R')
        {
          if (!Scene.IsRenderActive)
          {
            Scene.IsRenderActive = TRUE;
            Scene.IsToBeStop = FALSE;
            Scene.IsReadyToFinish = FALSE;
            std::cout << "Start render scene" << std::endl;
            Time.update();
            std::thread Th;
            Th = std::thread(
              [&]( VOID )
              {
                LONG tt = clock();
                Render();
                tt = clock() - tt;
                INT Seconds = (INT)((DBL)tt / CLOCKS_PER_SEC);

                std::cout <<
                  std::fixed << (DBL)tt / CLOCKS_PER_SEC <<
                  " :: " << std::setfill('0') << std::setw(2) <<
                                                 Seconds / 60 / 60 <<
                  ":" << std::setfill('0') << std::setw(2) <<
                                                 Seconds / 60 % 60 <<
                  ":" << std::setfill('0') << std::setw(2) <<
                                                 Seconds % 60 << "\r";
                
                Frm.AutoSaveTGA("CGSG forever!!!",
                  {Seconds / 60 / 60, Seconds / 60 % 60, Seconds % 60});
                std::cout << "Scene rendered. Time: " << Seconds / 60 / 60 << ", " << Seconds / 60 % 60 << ", " << Seconds % 60 << std::endl;
                InvalidateRect(hWnd, NULL, FALSE);
                UpdateWindow(hWnd);
                Scene.IsRenderActive = FALSE;
                Scene.IsToBeStop = FALSE;
                Scene.IsReadyToFinish = TRUE;
              });
            Th.detach();
          }
        }
        else if (wParam == 'A')
        {
          SendMessage(hWnd, WM_TIMER, 30, lParam);
        }
        else if (wParam == VK_ESCAPE)
        {
          if (!Scene.IsRenderActive)
            DestroyWindow(hWnd);
          else
            Scene.IsToBeStop = TRUE;
        }
        else if (wParam == VK_F11)
        {
          FlipFullScreen(hWnd);
        }
        return 0;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
  } /* End of 'win::OnMessage' function */
  /* WM_DESTROY window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID OnDestroy( VOID ) override
  {
    if (!Scene.IsRenderActive)
    {
      DeleteObject(hBrBack);
      KillTimer(hWnd,30);
      PostQuitMessage(30);
    }
    else
      Scene.IsToBeStop = TRUE;
  } /* End of 'win::OnDestroy' function */
  };
}

#endif //__rt_win_h

/* End of 'rt_win.h;' file */
