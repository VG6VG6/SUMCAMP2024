/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mtl.cpp
 * PURPOSE     : Animation project.
 *               Materials resource module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 04.08.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"
#include "mtl.h"

/* Application namespace */
namespace gogl
{
  material::material_manager::material_manager( VOID )
  {
  } /* End of 'material::material_manager::material_manager' function */

  /* Material creation function.
  * ARGUMENTS:
  *   - material name:
  *       const std::string &NewName;
  *   - illumination coefficients (ambient. diffuse, specular):
  *       const color3 &NewKa, &NewKd, &NewKs;
  *   - Phong shininess coefficient:
  *       FLT NewPh;
  *   - transparency coefficient:
  *       FLT NewTrans;
  *   - shader pointer:
  *       shader *NewShd;
  *   - textures list:
  *       std::initializer_list<texture *> Textures;
  * RETURNS:
  *   (material &) self reference.
  */
  material & material::Create( const std::string &NewName,
                               const vec3 &NewKa,
                               const vec3 &NewKd,
                               const vec3 &NewKs,
                               FLT NewPh, FLT NewTrans,
                               shader *NewShd,
                               std::initializer_list<texture *> Textures ) 
  {
    INT i = 0;

    Name = NewName;
    Ka = NewKa;
    Kd = NewKd;
    Ks = NewKs;
    Ph = NewPh;
    Trans = NewTrans;
    Shd = NewShd;
    for (auto tex_ : Textures)
    {
      Tex[i] = tex_, i++;
      if (i >= 8)
        break;
    }
      
    BUF_MTL Buffer;
    Buffer.Ka = vec4(Ka, 0);
    Buffer.KdTrans = vec4(Kd, Trans);
    Buffer.KsPh = vec4(Ks, Ph);
    for (INT i = 0; i < 8; i++)
      Buffer.IsTex[i] = Tex[i] != nullptr ? 1 : 0;
    if (BufferMtl == nullptr)
      BufferMtl = new buffer;
    BufferMtl->Create(3, &Buffer);

    return *this;
  } /* End of 'material::Create' function */

  /* Apply material function.
  * ARGUMENTS: None.
  * RETURNS:
  *   (shader *) shader interface;
  */
  shader * material::Apply( VOID )
  {
    BUF_MTL Buffer;
    Buffer.Ka = vec4(Ka, 0);
    Buffer.KdTrans = vec4(Kd, Trans);
    Buffer.KsPh = vec4(Ks, Ph);
    for (INT i = 0; i < 8; i++)
      Buffer.IsTex[i] = FALSE;

    for (INT i = 0; i < 8; i++)
    {
      BOOL IsTex = FALSE;
      if (Tex[i] != nullptr)
        if (Tex[i]->TexNoG3DF != -1)
        {
          Buffer.IsTex[i] = TRUE;

          glActiveTexture(GL_TEXTURE0 + i);
          glBindTexture(GL_TEXTURE_2D, Tex[i]->TexNo);
        }
    }
    BufferMtl->Update(&Buffer);
    BufferMtl->Apply();
    return Shd;
  } /* End of 'material::Apply' function */
} /* End of 'gogl' namespace */

/* End of 'mtl.cpp' file */