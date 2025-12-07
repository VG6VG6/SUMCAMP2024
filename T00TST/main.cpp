/* FILE NAME: main.cpp
 * PROGRAMMER: VG6
 * LAST UPDATE: 19.07.2024
 * PURPOSE: Create windows window.
 */

#undef UNICODE
#include <Windows.h>

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
  HDC hDC;
  PAINTSTRUCT ps;
  static HDC hMemDC;
  static INT W, H;
  static DWORD *Bits;
  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 30, 100, NULL);
    return 0;
  case WM_SIZE:
    BITMAPINFOHEADER bmih;
    static HBITMAP hBm;

    W = LOWORD(lParam);
    H = HIWORD(lParam);
    
    if (hBm != NULL)
      DeleteObject(hBm);
    
    memset(&bmih, 0, sizeof(bmih));
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biBitCount = 32;
    bmih.biPlanes = 1;
    bmih.biCompression = BI_RGB;
    bmih.biWidth = W;
    bmih.biHeight = -H;

    bmih.biSizeImage = W * H * 4;
    bmih.biClrUsed = 0;
    bmih.biClrImportant = 0;
    bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 0;

    hBm = CreateDIBSection(NULL, (BITMAPINFO *)&bmih, DIB_RGB_COLORS,
              (VOID **)&Bits, NULL, 0);

    SelectObject(hMemDC, hBm);
    /*
    hDC = GetDC(hWnd);
    hBM = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    */
    return 0;
  case WM_TIMER:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    Ellipse(hMemDC, W / 2, H / 2, W, H);
    Ellipse(hMemDC, 0, 0, W / 2, H / 2);
    /*
    if (W > 30 && H > 30)
      Bits[30 * W + 30] = 0x00FF0000;
    */
    BitBlt(hDC, 0, 0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 0;
  case WM_DESTROY:
    DeleteDC(hMemDC);
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

