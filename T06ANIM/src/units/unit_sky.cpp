/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : unit_sky.cpp
 * PURPOSE     : Animation project.
 *               Unit sample module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 4.08.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"

class unit_sky : public gogl::unit
{
public:
  gogl::prim *Sky;
  /* Unit constructor */
  unit_sky( VOID )
  {
    gogl::topology::base<gogl::vertex::point> P;
    gogl::vertex::point A;
    A.P = gogl::vec3(0, 0, 0);
    P.V.push_back(A);
    P.Type = gogl::prim_type::POINTS;
    Sky = gogl::anim::GetRef().PrimCreate(P);

    gogl::texture *tex = gogl::anim::GetRef().TextureCreate("bin/images/sky33.bmp");
    tex->TexNoG3DF = 7;
    Sky->Mtl = gogl::anim::GetRef().MaterialCreate("Sky sphere material", {}, {}, {}, 0, 0, gogl::anim::GetRef().ShdCreate("skysphere"), {tex});
  } /* End of unit constructor */

  /* Unit destructor */
  ~unit_sky( VOID )
  {
  } /* End of unit destructor */

  /* Render unit function.
   * ARGUMENTS:
   *   - animation context:
   *       gogl::anim *Ani;
   * RETURNS: None.
   */ 
  VOID Render( gogl::anim *Ani ) override
  {
    Sky->Draw(gogl::matr::Identity());
  } /* End of 'Render' function */

  /* Response unit function.
   * ARGUMENTS:
   *   - animation context:
   *       gogl::anim *Ani;
   * RETURNS: None.
   */ 
  VOID Response( gogl::anim *Ani ) override
  {
  } /* End of 'Response' function */
}; /* End of 'unit_sky' class */

static gogl::anim::unit_register<unit_sky> _("Unit Sky");

/* End of 'unit_sky.cpp' file */