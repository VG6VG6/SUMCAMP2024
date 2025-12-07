/* FILE NAME: t03newf.cpp         *
 * PROGRAMMER: VG6
 * LAST UPDATE: 20.07.2024
 * PURPOSE: Draw fractals.
 */

#undef UNICODE
#include <Windows.h>
#include <thread>

#include "cmpl.h"
#include "frame.h"

#define WND_CLASS_NAME "My T00TST window"

/* Window handler function
 * ARGUMENTS:
 *   - window deskriptor:
 *       HWND hWnd;
 *   - message type:
 *       UINT Msg;
 *   - message parametrs:
 *       WPARAM wParam, LPARAM lParam;
 * RETURNS:
 *   (LRESULT) Message error code.
 */
LRESULT CALLBACK MyWindowFunc(HWND hWnd, UINT Msg,
  WPARAM wParam, LPARAM lParam)
{
  HDC hDc;
  PAINTSTRUCT ps;
  static HDC hMemDc;
  static INT W, H;
  static DWORD *Bits;
  static frame Frame;
  static Timer Time;
  static std::thread Th;
  static Control Ctrl;
  static INT Mx, My, Mz;

  struct deal
  {
    Timer *Time;
    deal( Timer *tmr )
    {
      Time = tmr;
    }
    void operator()( void )
    {
      while( true )
        Frame.ThreadRender(NewtonStepen(), *Time, 16);
    }
  };

  
  switch (Msg)
  {
  case WM_CREATE:
    hDc = GetDC(hWnd);
    hMemDc = CreateCompatibleDC(hDc);
    Th = std::thread(deal(&Time));
    Th.detach();
    ReleaseDC(hWnd, hDc);
    SetTimer(hWnd, 30, 100, NULL);
    return 0;
  case WM_SIZE:
    W = LOWORD(lParam);
    H = HIWORD(lParam);
    InvalidateRect(hWnd, NULL, FALSE);
    SendMessage(hWnd, WM_TIMER, wParam, lParam);
    return 0;
  case WM_TIMER:
    Time.update();
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    hDc = BeginPaint(hWnd, &ps);
    Rectangle(hDc, -1, -1, W, H);
    Frame.Draw(hDc);
    BitBlt(hDc, 0, 0, W, H, hMemDc, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 0;
  case WM_MOUSEWHEEL:
    Mz = (SHORT)HIWORD(wParam);
    Ctrl.Zoom(Mz);
    return 0;
  case WM_MOUSEMOVE:
    Mx = (SHORT)LOWORD(lParam);
    My = (SHORT)HIWORD(lParam);
    Ctrl.Move(Mx, My);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

/* Main programm function.
 * ARGUMENTS:
 *   - 
 *   
 * RETURNS: 
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;

  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, IDI_ERROR);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }
  /* Create window */
  hWnd =
    CreateWindow(WND_CLASS_NAME,
      "VG6 first cpp window",
      WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, CW_USEDEFAULT,
      1200, 600,
      NULL,
      NULL,
      hInstance,
      NULL);

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return (INT)msg.wParam;
} /* End of 'WinMain' function*/

/* End of 't03newf.cpp' file */
