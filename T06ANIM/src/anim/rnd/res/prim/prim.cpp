/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : prim.cpp
 * PURPOSE     : Animation project.
 *               Primmitive resource module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 4.08.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"

/* Draw primitive function.
  * ARGUMENTS:
  *   - transformation 'world' matrix:
  *       MATR World;
  * RETURNS: None.
  */
VOID gogl::prim::Draw( gogl::matr World )
{
  gogl::matr
    w = Transform * World;
  UINT ProgId;

  if ((ProgId = Mtl->Apply()->ProgId) == 0)
    return;

  gogl::PrimUBOStruct pr;

  memcpy(pr.MatrW, w.M, sizeof(FLT) * 16);
  memcpy(pr.MatrWInv, w.Inverse().M, sizeof(FLT) * 16);
  memcpy(pr.MatrWVP, (w * Rnd->Cam.VP).M, sizeof(FLT) * 16);
  pr.RndIsWireIsAny = vec4();
  Rnd->PrimUBO->Update(&pr);
  Rnd->PrimUBO->Apply();
  glUseProgram(ProgId);
  glEnable(GL_DEPTH_TEST);

  glBindVertexArray(VA);
  if (IBuf == 0)
      glDrawArrays((INT)Type, 0, NumOfElements);
    else
    {
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
      glDrawElements((INT)Type, NumOfElements, GL_UNSIGNED_INT, NULL);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

  glDisable(GL_DEPTH_TEST);
  glBindVertexArray(0);
  glUseProgram(0);
} /* End of 'Draw' function */

/* End of 'prim.cpp' file */