/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : quadrics.h
 * PURPOSE     : Raytracing project.
 *               Quadrics shape class declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 24.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#ifndef __quadrics_h_
#define __quadrics_h_
#include "def.h"
#include "../rt_def.h"
/* Application namespace. */
namespace gort
{
  /* quadrics shape class. */
  class quadrics : public shape
  {
    DBL A, B, C, D,
           E, F, G,
              H, I,
                 J;
    matr Matrix;

  public:
    quadrics( DBL NA, DBL NB, DBL NC, DBL ND, DBL NE, 
              DBL NF, DBL NG, DBL NH, DBL NI, DBL NJ) : A(NA), B(NB), C(NC), D(ND), E(NE),
                                                        F(NF), G(NG), H(NH), I(NI), J(NJ)
    {
      Matrix = matr(A, B, C, D,
                     B, E, F, G,
                     C, F, H, I,
                     D, G, I, J);
    }

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection data:
     *       intr *in;
     * RETURNS: None.
     */
    VOID GetNormal( intr *in )
    {} /* End of 'GetNormal' function */

  }; /* End of 'quadrics' class */
} /* End of 'gotr' namespace */

#endif // !__quadrics_h_



/* End of 'quadrics.h' file */