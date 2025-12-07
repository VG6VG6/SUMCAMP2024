/* FILE NAME: frame.h
 * PROGRAMMER: VG6
 * LAST UPDATE: 20.07.2024
 * PURPOSE: Draw.
 */
#ifndef _FRAME_H
#define _FRAME_H

#include <Windows.h>
#include <thread>

#define MY_RGB(r,g,b)   ((COLORREF)(((BYTE)(r)<<16|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b)))))

struct frame
{
  static const int H = 800, W = 800; // Frame size 
  DWORD Image[H][W] {};              // Frame color array
  int Threads;
  std::thread *Ts;

  frame()
  {
    Threads = std::thread::hardware_concurrency() - 1;
    Ts = new std::thread[Threads];
  }
  ~frame()
  {
    for (int t = 0; t < Threads; t++)
      Ts[t].detach();
    delete[] Ts;
  }

  /* Put pixel to window
   * ARGUMENTS:
   *   - pixel possition:
   *       INT X, Y;
   *   - pixel color:
   *       DWORD Color;
   * RETURNS: None.
   */
  VOID PutPixel( INT x, INT y, DWORD Color )
  {
    if (x > W || x < 0 || y > H || y < 0)
      return;
    Image[y][x] = Color;
  } /* End of 'PutPixel' function */

  /* Render frame function.
   * ARGUMENTS:
   *   - callback for level evaluation:
   *       func F;
   *   - const lick to timer struct:
   *       const Timer &Time;
   *   - const count of Newton fractal fi need:
   *       const int step = 3;
   * RETURNS: None.
   */
  template<typename func>
  VOID render( func F, const Timer &Time, const int step = 3 )
  {
    int n;
    
    for (int y = 0; y < H; y++)
      for (int x = 0; x < W; x++)
      {
        n = F(x, y, W, H, Time, step);
        Image[y][x] = MY_RGB(n * 30 * 255.0, n * 47 / 255.0, n * 90 / 255.0);
      }
  } /* End of 'render' function */

  /* Thread render frame function.
   * ARGUMENTS:
   *   - callback for level evaluation:
   *       func F;
   *   - const lick to timer struct:
   *       const Timer &Time;
   *   - const count of Newton fractal fi need:
   *       const int step = 3;
   * RETURNS: None.
   */
  template<typename func>
  VOID ThreadRender( func F, Timer &Time, int step = 3 )
  {
    for (int t = 0; t < Threads; t++)
      Ts[t] = std::thread(RenderRow<func>, F, t, Threads, std::ref(*this), std::ref(Time), step);

    for (int t = 0; t < Threads; t++)
      Ts[t].join();
  } /* End of 'ThreadRender' function */

  template<typename func>
    static void RenderRow( func F, int StartRow, int SkipRow, frame &Frm, Timer &Time, int step )
    {
      int n;

      for (int y = StartRow; y < Frm.H; y += SkipRow)
        for (int x = 0; x < Frm.W; x++)
        {
          n = F(x, y, Frm.W, Frm.H, Time, step);
          //Frm.Image[y][x] = MY_RGB(n * 30 * 255.0, n * 47 / 255.0, n * 90 / 255.0);
          Frm.Image[y][x] = MY_RGB(n * 10, 0, 0);
        }
    }

  /* Draw image function 
   * ARGUMENTS:
   *   -  
   *     HDC hDc
   * RETURNS None.
   */
  VOID Draw( HDC hDC )
  {
    BITMAPINFOHEADER bmih;

    memset(&bmih, 0, sizeof(bmih));
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biBitCount = 32;
    bmih.biPlanes = 1;
    bmih.biWidth = W;
    bmih.biHeight = -H;
    SetDIBitsToDevice(hDC, 0, 0, W, H, 0, 0, 0, H, Image, (BITMAPINFO *)&bmih, DIB_RGB_COLORS);
  }
};

#endif /* _FRAME_H */
/* End of 'fame.h' file */