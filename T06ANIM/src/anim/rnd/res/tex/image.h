/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : image.h
 * PURPOSE     : Animation project.
 *               Image resurse handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 31.07.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __image_h_
#define __image_h_
#include "def.h"
#include <fstream>
#include <wincodec.h>

namespace gogl
{
  class image
  {
  private:
    // Image size in pixels
    INT Width = 0, Height = 0;
    // Image pixel data
    std::vector<BYTE> Pixels;
  public:
    // Rows access pointer by DWORD
    std::vector<DWORD *> RowsD;
    // Rows access pointer by BYTE quads
    std::vector<BYTE (*)[4]> RowsB;

    // Image size references
    const INT &W = Width, &H = Height;

    /* Class default construtor */
    image( VOID )
    {
    } /* End of 'image' function */

    /* Class construtor.
     * ARGUMENTS:
     *   - image file name:
     *       const std::string &FileName;
     */
    image( const std::string &FileName )
    {
      HBITMAP hBm;
      if ((hBm = (HBITMAP)LoadImage(nullptr, FileName.c_str(),
                                    IMAGE_BITMAP, 0, 0,
                                    LR_LOADFROMFILE)) != nullptr)
      {
        // Case of BMP file
 
        /* Create contextes */
        HDC hDC = GetDC(nullptr);
        HDC hMemDC = CreateCompatibleDC(hDC);
        HDC hMemDC1 = CreateCompatibleDC(hDC);
        SelectObject(hMemDC, hBm);
        ReleaseDC(nullptr, hDC);

        BITMAP bm;
        GetObject(hBm, sizeof(bm), &bm);

        BITMAPINFOHEADER bmih;

        Width = bm.bmWidth;
        Height = bm.bmHeight;

        /* Build DIB section */
        memset(&bmih, 0, sizeof(bmih));
        bmih.biSize = sizeof(BITMAPINFOHEADER);
        bmih.biBitCount = 32;                   /* BGRx - DWORD */
        bmih.biPlanes = 1;                      /* always */
        bmih.biCompression = BI_RGB;            /* 0 - no compression */
        bmih.biWidth = bm.bmWidth;              /* width */
        bmih.biHeight = -bm.bmHeight;          /* height + first coded row is 0 */
        bmih.biSizeImage = bm.bmWidth * bm.bmHeight * 4; /* image size in bytes */

        VOID *Bits;
        HBITMAP hImage = CreateDIBSection(nullptr, (BITMAPINFO *)&bmih,
                           DIB_RGB_COLORS, (VOID **)&Bits, nullptr, 0);
        SelectObject(hMemDC1, hImage);

        /* Draw load image to DIB */
        BitBlt(hMemDC1, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);
        DeleteDC(hMemDC);
        DeleteDC(hMemDC1);

        Pixels.resize(bmih.biSizeImage);
        CopyMemory(&Pixels[0], Bits, bmih.biSizeImage); // Pixels.data()
        DeleteObject(hImage);
        DeleteObject(hBm);

        // Make alpha channel
        for (INT i = 3; i < Width * Height * 4; i += 4)
          Pixels[i] = 255;
      }
      else
      {
        std::fstream f(FileName, std::fstream::in | std::fstream::binary);

        if (f.is_open())
        {
          // Case of G24/G32
          INT fw = 0, fh = 0;
          f.read((CHAR *)&fw, 2);
          f.read((CHAR *)&fh, 2);
          f.seekg(0, std::fstream::end);
          INT flen = f.tellg();
          if (flen == 4 + fw * fh * 3)
          {
            // G24
            f.seekg(4, std::fstream::beg);
            Pixels.resize(fw * fh * 4);
            Width = fw;
            Height = fh;
            for (INT r = 0, p = 0; r < fh; r++)
              for (INT c = 0; c < fw; c++)
              {
                BYTE rgb[3];
                f.read((CHAR *)rgb, 3);
                Pixels[p++] = rgb[0];
                Pixels[p++] = rgb[1];
                Pixels[p++] = rgb[2];
                Pixels[p++] = 255;
              }
          }
          else if (flen == 4 + fw * fh * 4)
          {
            // G32
            f.seekg(4, std::fstream::beg);
            Pixels.resize(fw * fh * 4);
            Width = fw;
            f.read((CHAR *)Pixels.data(), 4 * fw * fh);
          }
          else
            Load(FileName);
          f.close();
        }
      }
      // Setup row pointers
      INT i;
      RowsD.resize(Height);
      i = 0;
      for (auto &r : RowsD)
        r = (DWORD *)&Pixels[i++ * Width * 4];
      RowsB.resize(Height);
      i = 0;
      for (auto &r : RowsB)
        r = (BYTE (*)[4])&Pixels[i++ * Width * 4];
    } /* End of 'image' function */

    /* Class copying construtor.
     * ARGUMENTS:
     *   - const reference to copy object:
     *       const image &Img;
     */
    image( const image &Img ) :
      Width(Img.Width), Height(Img.Height), 
      W(Width), H(Height), Pixels(Img.Pixels)
    {
      // Setup row pointers
      INT i;
      RowsD.resize(Height);
      i = 0;
      for (auto &r : RowsD)
        r = (DWORD *)&Pixels[i++ * Width * 4];
      RowsB.resize(Height);
      i = 0;
      for (auto &r : RowsB)
        r = (BYTE (*)[4])&Pixels[i++ * Width * 4];
    } /* End of 'image' function *

    /* Class move construtor.
     * ARGUMENTS:
     *   - move reference to copy object:
     *       image &&Img;
     */
    image( image &&Img ) :
      Width(Img.Width), Height(Img.Height), 
      W(Width), H(Height), Pixels(std::move(Img.Pixels))
    {
      // Setup row pointers
      INT i;
      RowsD.resize(Height);
      i = 0;
      for (auto &r : RowsD)
        r = (DWORD *)&Pixels[i++ * Width * 4];
      RowsB.resize(Height);
      i = 0;
      for (auto &r : RowsB)
        r = (BYTE (*)[4])&Pixels[i++ * Width * 4];
      Img.Width = Img.Height = 0;
    } /* End of 'image' function */

    /* Set image size function.
     * ARGUMENTS:
     *   - image size:
     *       INT iw, ih;
     * RETURNS:
     *   (BOOL) ???TRUE if memory alloc correct, FALSE otherwise.
    */
    BOOL Create( INT iw, INT ih )
    {
      Pixels.resize(iw * ih * 4);
      return TRUE;
    } /* End of 'Create' function */

    /* Load image by winapi function.
    * ARGUMENTS:
    *   - path to image:
    *       std::string_view FileNmae;
    * RETURNS: None.
    */
    VOID Load( std::string_view FileName )
    {
      // Windows Imaging Component factory
      static IWICImagingFactory2 *WicFactory;

      if (WicFactory == nullptr)
      {
        CoInitialize(nullptr);
        CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&WicFactory));
      }

      // Load through Window Image Component
      if (WicFactory != nullptr)
      {
        IWICBitmapDecoder *Decoder {};
        std::wstring FileNameW {FileName.begin(), FileName.end()};

          // Create decoder (loader)
        WicFactory->CreateDecoderFromFilename(FileNameW.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &Decoder);
        if (Decoder != nullptr)
        {
          IWICBitmapFrameDecode *Frame {};
          Decoder->GetFrame(0, &Frame);
          UINT fw = 0, fh = 0;

          if (Frame != nullptr)
          {
            Frame->GetSize(&fw, &fh);
            if (fw != 0 && fh != 0)
            {
              // Converting image format to standard - RGBA with 8-bits per pixel
              IWICFormatConverter *Convert {};
              WicFactory->CreateFormatConverter(&Convert);

              if (Convert != nullptr)
              {
                // Converter initialization
                Convert->Initialize(Frame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);

                // Size checking
                Convert->GetSize(&fw, &fh);
                if (fw != 0 && fh != 0 && Create(fw, fh))
                {
                  // Copying image pixels to container pixel array
                  WICRect Rect {0, 0, static_cast<INT>(fw), static_cast<INT>(fh)};
                  Convert->CopyPixels(&Rect, fw * 4, fw * fh * 4, Pixels.data());
                  Height = fh;
                  Width = fw;
                }
                Convert->Release();
              }
            }
            Frame->Release();
          }
          Decoder->Release();
        }
      }
    } /* End of 'Load' function */
  }; /* End of image class */
} /* end of 'gogl' namespace */

#endif // __image_h_
/* End of 'image.h' file */
