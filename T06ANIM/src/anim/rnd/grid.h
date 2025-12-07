/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : grid.h
 * PURPOSE     : Animation project.
 *               Grid header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 4.08.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __GRID_H_
#define __GRID_H_

#include "def.h"
/* Application namespace */
namespace gogl
{
  /* grid class */
  class grid
  {
    INT W, H;                       // grid size
    topology::base<vertex::std> T;  // array of grid vertex
    anim *Ani;
  public:
    INT &Weiht = W, &Height = H;
    /* class constructor 
     * ARGUMENTS:
     *   - animation context:
     *       anim *NAni;
     *   - grid size:
     *       INT NewW, NewH;
     */
    grid( anim *NAni, INT NewW, INT NewH ) : W(NewW), H(NewH), Ani(NAni)
    {
      T.V.resize(W * H);
      for (INT z = 0; z < H; z++)
        for (INT x = 0; x < W; x++)
        {
          T.V[z * W + x].P = vec3(x, 0, z);
          T.V[z * W + x].N = vec3(0, 1, 0);
          T.V[z * W + x].T = vec2(x / (W - 1.0), z / (H - 1.0));
          T.V[z * W + x].C = vec4(1, 0, 0, 1);
        }
    }
    /* class constructor 
     * ARGUMENTS:
     *   - animation context:
     *       anim *NAni;
     */
    grid( anim *NAni ) : W(0), H(0), Ani(NAni)
    {
    }
    /* default class constuctor */
    grid( VOID ) : W(0), H(0)
    {
    }

    /* Create grid function.
     * ARGUMENTS: None.
     * RETURNS: 
     *   (prim *) pointer to primmitie.
     */
    prim * CreatePrim( VOID )
    {
      INT i, j, k;
      prim *Pr;
      if (W < 1 || H < 1)
        return nullptr;
      T.I.resize((H - 1) * (W * 2 + 1) - 1);

      for (i = 0, k = 0; i < H - 1; i++)
      {
        for (j = 0; j < W; j++)
        {
          T.I[k++] = (i + 1) * W + j;
          T.I[k++] = i * W + j;
        }
        if (i != H - 2)
          T.I[k++] = (i + 1) * W + (W - 1);
        i++;
        if (i >= H - 1)
          break;
        for (j = W - 1; j >= 0; j--)
        {
          T.I[k++] = (i + 1) * W + j;
          T.I[k++] = i * W + j;
        }
        if (i != H - 2)
          T.I[k++] = (i + 1) * W;
      }
      T.Type = prim_type::TRISTRIP;
      Pr = Ani->PrimCreate(T);
      Pr->Mtl = Ani->MaterialFind("default");

      return Pr;
    } /* End of 'CreatePrim' function */

    grid * LoadHeightDield( const std::string &FileName )
    {
      //HBITMAP hBm;
      BITMAP Bm;
      HANDLE Handle;
      FLT max_height = 50;
      if ((Handle = LoadImage(NULL, FileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
      {
        GetObject(Handle, sizeof(Bm), &Bm);

        H = Bm.bmHeight;
        W = Bm.bmWidth;
        T.V.resize(W * H);
        for (INT y = 0; y < H; y++)
          for (INT x = 0; x < W; x++)
          {
            BYTE *rgb = (BYTE *)Bm.bmBits + y * Bm.bmWidthBytes + x * (Bm.bmBitsPixel / 8);

            FLT h = max_height * rgb[1] / 255.0;

            T.V[y * W + x].P = vec3(x, h, y);
            T.V[y * W + x].C =
              vec4(rgb[2] / 255.0, rgb[1] / 255.0, rgb[0] / 255.0, 1);
          }
        DeleteObject(Handle);
      }
      return this;
    }

    /* Build grid normals function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID AutoNormals( VOID )
    {
      INT i, j;

      /* reset all  normals */
      for (i = 0; i < W * H; i++)
        T.V[i].N = vec3(0);

      for (i = 0; i < H - 1; i++)
        for (j = 0 ; j < W - 1; j++)
        {
          vertex::std
             *P00 = T.V.data() + i * W + j,
             *P01 = T.V.data() + i * W + j + 1,
             *P10 = T.V.data() + (i + 1) * W + j,
             *P11 = T.V.data() + (i + 1) * W + j + 1;
          vec3 N;

          N = ((P00->P - P10->P) % (P11->P - P10->P)).Normalizing();
          P00->N = P00->N + N;
          P10->N = P10->N + N;
          P11->N = P11->N + N;

          N = ((P11->P - P01->P) % (P00->P - P01->P)).Normalizing();
          P00->N = P00->N + N;
          P01->N = P01->N + N;
          P11->N = P11->N + N;
        }
      /* normalize all */
      for (i = 0; i < W * H; i++)
        T.V[i].N.Normalize();
    } /* End of 'VG6_RndGridAutoNormals' function */

  }; /* End of 'grid' class */
} /* End of 'gogl' namespace */

#endif // __GRID_H_


/* End of 'grid.h' file */