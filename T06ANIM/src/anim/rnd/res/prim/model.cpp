/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : model.cpp
 * PURPOSE     : Animation project.
 *               Models resource module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 3.08.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"
#include "model.h"

/* Laod prims from g3dm file function
  * ARGUMENTS:
  *   - pointer to primitives structure:
  *       vg6PRIMS *Prs;
  *  - file name:
  *      CHAR *FileNameæ
  */
gogl::model & gogl::model::Load( std::string FileName )
{
  INT flen, p, t, m;
  std::vector<BYTE> mem;
  std::vector<INT> MtlList;
  BYTE *ptr = mem.data();
  DWORD Sign; /* == "G3DM" */
  DWORD NumOfPrims;
  DWORD NumOfMaterials;
  DWORD NumOfTextures;
  shader *shd;
  if ((shd = Rnd->shader::shader_manager::Find(std::string("g3dm"))) == nullptr)
    shd = Rnd->shader::shader_manager::ShdCreate("g3dm");
 
  /* Open file */
  std::fstream F(FileName, std::fstream::in | std::fstream::binary);
 
  /* Obtain file length */
  F.seekg(0, std::fstream::end);
  flen = (INT)F.tellg();
  F.seekg(0, std::fstream::beg);

  /* Allocate memory and load whole file to memory */
  mem.resize(flen);
  F.read((CHAR *)mem.data(), flen);
  ptr = mem.data();
  /* Signature */
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
    return *this;

  NumOfPrims = *(DWORD *)ptr;
  ptr += 4;
  NumOfMaterials = *(DWORD *)ptr;
  ptr += 4;
  NumOfTextures = *(DWORD *)ptr;
  ptr += 4;

  MtlList.resize(NumOfPrims);

  if (NumOfPrims < 1 || NumOfMaterials < 1 )
    return *this;

  /* Load primitives */
  for (p = 0; p < NumOfPrims; p++)
  {
    DWORD NumOfVertex;
    DWORD NumOfFacetIndexes; /* num of facets * 3 */
    DWORD MtlNo;             /* Material number in table below (in material section) */
    std::vector<vertex::std> V;
    std::vector<INT> I;

    NumOfVertex= *(DWORD *)ptr;
    ptr += 4;
    NumOfFacetIndexes = *(DWORD *)ptr;
    ptr += 4;
    MtlNo = *(DWORD *)ptr;
    ptr += 4;

    V.resize(NumOfVertex);
    memcpy(V.data(), ptr, sizeof(vertex::std) * NumOfVertex);
    ptr += sizeof(vertex::std) * NumOfVertex;

    I.resize(NumOfFacetIndexes);
    memcpy(I.data(), ptr, sizeof(INT) * NumOfFacetIndexes);
    ptr += sizeof(INT) * NumOfFacetIndexes;

    Prims << Rnd->prim::primitive_manager::PrimCreate(topology::base<vertex::std>(prim_type::TRIMESH, V, I));
    MtlList[p] = MtlNo;
  }
  
  /* Load materials */
  for (m = 0; m < NumOfMaterials; m++)
  {
    texture *Tex[8] {};
    struct MtlStr
    {
      CHAR Name[300];      /* Material name */

      /* Illumination coefficients */
      vec3 Ka, Kd, Ks;     /* Ambient, diffuse, specular coefficients */
      FLT Ph;              /* Phong power coefficient – shininess */
      FLT Trans;           /* Transparency factor */
      DWORD Tex[8];        /* Texture references 
                            * (8 time: texture number in G3DM file, -1 if no texture) */
      /* Shader information */
      CHAR ShaderString[300]; /* Additional shader information */
      DWORD Shader;       /* Shader number (uses after load into memory) */
    } *fmat;

    fmat = (MtlStr *)ptr;
    ptr += sizeof(MtlStr);

    for (int tn = 0; tn < 8; tn++)
    {
      Tex[tn] = Rnd->texture::texture_manager::TextureCreate();
      Tex[tn]->TexNoG3DF = fmat->Tex[tn];
    }
    material *mtl = Rnd->material::material_manager::MaterialCreate(fmat->Name, fmat->Ka, fmat->Kd, fmat->Ks, fmat->Ph, fmat->Trans, shd, {Tex[0], Tex[1], Tex[2], Tex[3], Tex[4], Tex[5], Tex[6], Tex[7]});
    for (INT prn = 0; prn < NumOfPrims; prn++)
      if (m == MtlList[prn])
        Prims[prn]->Mtl = mtl;
  }
  /* Load textures */
  for (t = 0; t < NumOfTextures; t++)
  {
    CHAR *Name;
    DWORD W, H, C;

    Name = (CHAR *)ptr;
    ptr += 300;
    W = *(DWORD *)ptr;
    ptr += 4;
    H = *(DWORD *)ptr;
    ptr += 4;
    C = *(DWORD *)ptr;
    ptr += 4;

    for (INT prn = 0; prn < NumOfPrims; prn++)
      for (INT i = 0; i < 8; i++)
        if (Prims[prn]->Mtl->Tex[i]->TexNoG3DF == t)
          Prims[prn]->Mtl->Tex[i]->Create(Name, W, H, C, ptr);
    ptr += W * H * C;
  }
  IsLoad = TRUE;
  return *this;
} /* End of 'Load' fucntion */

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - global transformation matrix:
 *       matr World;
 * RETURNS: None.
 */
VOID gogl::model::Draw( gogl::matr World = gogl::matr::Identity() )
{
  matr m = Trans * World;

  glEnable(GL_BLEND);
  /* Draw all nontransparent primitives */ 
  for (auto pr : Prims)
    if (pr->Mtl->Trans == 1)
      pr->Draw(m);
 
  /* Draw all transparent primitives */ 
  glEnable(GL_CULL_FACE);
 
  /* Draw all front-face-culling */ 
  glCullFace(GL_FRONT);
  for (auto pr : Prims)
    if (pr->Mtl->Trans != 1)
      pr->Draw(m);

  /* Draw all back-face-culling */ 
  glCullFace(GL_BACK);
  for (auto pr : Prims)
    if (pr->Mtl->Trans != 1)
      pr->Draw(m);

  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);
} /* End of 'VG6_RndPrimsDraw' function */


/* En dof 'model.cpp' file */