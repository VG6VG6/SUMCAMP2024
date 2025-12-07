/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : g3dm.h
 * PURPOSE     : Raytracing project.
 *               Triabgle shape class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 24.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __g3dm_h_
#define __g3dm_h_
#include <map>
#include "../rt_def.h"

/* Application namespace. */
namespace gort
{
   /* prim shape class. */
  class prim : public shape
  {
  public:
    stock<triangle> triangles;
    INT MtlNo;

    vec3 MinBB, MaxBB;
    prim()
    {
    }
    /* Add triangle in primitive function
     * ARGUMENTS:
     *   - new element of primitive
     *       triangle &elem;
     * RETURNSL None.
     */
    VOID operator<<( triangle elem )
    {
      triangles << elem;
    }

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection data:
     *       intr *in;
     * RETURNS: None.
     */
    VOID GetNormal( intr *in )
    {
    } /* End of 'GetNormal' function */
    BOOL VirtualBoxIntersect( const ray &R, intr *Intr, const vec3 &Max, const vec3 &Min )
    {
      INT tnear_no = -1, tfar_no = -1;
      DBL tnear = -1, tfar = -1, t = -1;

      for (INT i = 0; i < 3; i++)
      {
        if (std::fabs(R.Dir[i]) < Threshold)
        {
          if (R.Org[i] < Min[i] || R.Org[i] > Max[i])
            return FALSE;
        }
        else
        {
          if (R.Dir[i] > Threshold)
          {
            if (R.Org[i] > Max[i])
              return FALSE;
            if (R.Org[i] < Min[i])
            {
              t = (Min[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear < t)
                tnear_no = i * 2, tnear = t;
            }
            t = (Max[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar > t)
              tfar_no = i * 2 + 1, tfar = t;
          }
          else
          {
            if (R.Org[i] < Min[i])
              return FALSE;
            if (R.Org[i] > Max[i])
            {
              t = (Max[i] - R.Org[i]) / R.Dir[i];
              if (tnear_no == -1 || tnear < t)
                tnear_no = i * 2, tnear = t;
              
            }
            t = (Min[i] - R.Org[i]) / R.Dir[i];
            if (tfar_no == -1 || tfar > t)
              tfar_no = i * 2 + 1, tfar = t;
            
          }
        }
      }
      if (tnear_no != -1)
      {
        if (tnear > tfar)
          return FALSE;
        Intr->T = tnear;
        Intr->I[0] = tnear_no;
        return TRUE;
      }
      Intr->T = tfar;
      return TRUE;
    } /* End of 'Intersection' function */

    BOOL Intersect( const ray &R, intr *Intr )
    {
      intr best_intr, in;
      BOOL IsNotFind = TRUE;
      if (VirtualBoxIntersect(R, Intr, MaxBB, MinBB))
        for (INT i = 0; i < triangles.size(); i++)
        {
          triangle &elem = triangles[i];
          if (elem.Intersect(R, &in))
          {
            if (IsNotFind || best_intr.T > in.T)
              best_intr = in, IsNotFind = FALSE, Intr->I[4] = i;
          }
        }
      if (IsNotFind)
        return FALSE;
      *Intr = best_intr;
      return TRUE;
    }
  }; /* End of 'prim' class */

  /* obj shape class. */
  class g3dm : public shape
  {
  public:
    CHAR Path[200];
    stock<prim> *prims;
    g3dm( const CHAR *FileName, const surface &mtl )
    {
      strncpy(Path, FileName, 200);
      prims = new stock<prim>;
      Material = mtl;
      ParseG3DM();
    }
    ~g3dm()
    {
      delete prims;
    }

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection data:
     *       intr *in;
     * RETURNS: None.
     */
    VOID GetNormal( intr *in )
    {
    } /* End of 'GetNormal' function */

    BOOL Intersect( const ray &R, intr *Intr )
    {
      intr best_intr, in;
      BOOL IsNotFind = TRUE;
      for (prim &elem : *prims)
      {
        if (elem.Intersect(R, &in))
        {
          if (IsNotFind || best_intr.T > in.T)
            best_intr = in, IsNotFind = FALSE;
        }
      }
      if (IsNotFind)
        return FALSE;
      *Intr = best_intr;
      return TRUE;
    }

  private:

  struct Vertex
    {
      mth::vec3<FLT> P;
      mth::vec2<FLT> T;
      mth::vec3<FLT> N;
      mth::vec4<FLT> C;
    };
    
    BOOL ParseG3DM( VOID )
    {
      FILE *F;
      INT flen, p;//, t, m;
      BYTE *mem, *ptr;
      DWORD Sign; /* == "G3DM" */
      DWORD NumOfPrims;
      DWORD NumOfMaterials;
      DWORD NumOfTextures;

      /* Open file */
      if ((F = fopen(Path, "rb")) == NULL)
        return FALSE;

      /* Obtain file length */
      fseek(F, 0, SEEK_END);
      flen = ftell(F);
      rewind(F);

      /* Allocate memory and load whole file to memory */
      mem = new BYTE[flen];
      fread(mem, 1, flen, F);
      fclose(F);

      ptr = mem;
      /* Signature */
      Sign = *(DWORD *)ptr;
      ptr += 4;
      if (Sign != *(DWORD *)"G3DM")
      {
        free(mem);
        return FALSE;
      }
      NumOfPrims = *(DWORD *)ptr;
      ptr += 4;
      NumOfMaterials = *(DWORD *)ptr;
      ptr += 4;
      NumOfTextures = *(DWORD *)ptr;
      ptr += 4;

      /* Load primitives */
      for (p = 0; p < NumOfPrims; p++)
      {
        DWORD NumOfVertex;
        DWORD NumOfFaceIndexes;
        DWORD MtlNo;
        Vertex *V;
        INT *Ind;
        prim primitive;

        NumOfVertex = *(DWORD *)ptr, ptr += 4;
        NumOfFaceIndexes = *(DWORD *)ptr, ptr += 4;
        MtlNo = *(DWORD *)ptr, ptr += 4;
        V = (Vertex *)ptr, ptr += sizeof(Vertex) * NumOfVertex;
        Ind = (INT *)ptr, ptr += sizeof(INT) * NumOfFaceIndexes;

        primitive.MtlNo = MtlNo;
        for (int tr = 0; tr < NumOfFaceIndexes; tr += 3)
        {
          vec3 P0 = vec3(V[Ind[tr + 0]].P[0], V[Ind[tr + 0]].P[1], V[Ind[tr + 0]].P[2]);
          vec3 P1 = vec3(V[Ind[tr + 1]].P[0], V[Ind[tr + 1]].P[1], V[Ind[tr + 1]].P[2]);
          vec3 P2 = vec3(V[Ind[tr + 2]].P[0], V[Ind[tr + 2]].P[1], V[Ind[tr + 2]].P[2]);
          triangle A = triangle(P0, P1, P2,
                                vec3(V[Ind[tr + 0]].N[0], V[Ind[tr + 0]].N[1], V[Ind[tr + 0]].N[2]),
                                vec3(V[Ind[tr + 1]].N[0], V[Ind[tr + 1]].N[1], V[Ind[tr + 1]].N[2]),
                                vec3(V[Ind[tr + 2]].N[0], V[Ind[tr + 2]].N[1], V[Ind[tr + 2]].N[2]));
          if (NumOfMaterials < 1)
            A.Material = Material;
          primitive << A;
        }
        /* Get min max BB */
        primitive.MaxBB = vec3(V[0].P[0], V[0].P[1],V[0].P[2]);
        primitive.MinBB = primitive.MaxBB;
        for (int i = 0; i < NumOfVertex; i++)
        {
          if (V[i].P[0] > primitive.MaxBB[0])
            primitive.MaxBB[0] = V[i].P[0];
          if (V[i].P[1] > primitive.MaxBB[1])
            primitive.MaxBB[1] = V[i].P[1];
          if (V[i].P[2] > primitive.MaxBB[2])
            primitive.MaxBB[2] = V[i].P[2];

          if (V[i].P[0] < primitive.MinBB[0])
            primitive.MinBB[0] = V[i].P[0];
          if (V[i].P[1] < primitive.MinBB[1])
            primitive.MinBB[1] = V[i].P[1];
          if (V[i].P[2] < primitive.MinBB[2])
            primitive.MinBB[2] = V[i].P[2];
        }
        *prims << primitive;
      }

#if 0
      /* Load materials */
      for (INT m = 0; m < NumOfMaterials; m++)
      {
        struct mtl
        {
          CHAR Name[300]; /* Material name */
          /* Illumination coefficients */
          vec3 Ka, Kd, Ks;     /* Ambient, diffuse, specular coefficients */
          FLT Ph;              /* Phong power coefficient – shininess */
          FLT Trans;           /* Transparency factor */
          DWORD Tex[8];        /* Texture references 
                               * (8 time: texture number in G3DM file, -1 if no texture) */
          /* Shader information */
          CHAR ShaderString[300]; /* Additional shader information */
          DWORD Shader;           /* Shader number (uses after load into memory) */
        } *fmat;

        for (auto &pr : *prims)
        {
          if (pr.MtlNo == m)
          {
            fmat = (mtl *)ptr;
            ptr += sizeof(*fmat);
            strncpy(pr.Material.Name, fmat->Name, 199);
            pr.Material.Ka = fmat->Ka;
            pr.Material.Kd = fmat->Kd;
            pr.Material.Ks = fmat->Ks;
            pr.Material.Ph = fmat->Ph;
            break;
          }
        }
      }
#endif
      free(mem);
      return TRUE;
      }
    }; /* End of 'g3dm' class */
} /* End of 'gotr' namespace */

#endif // __g3dm_h_



/* End of 'g3dm.h' file */

