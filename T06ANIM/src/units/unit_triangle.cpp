/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : unit_triangle.cpp
 * PURPOSE     : Animation project.
 *               Unit sample module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 4.08.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"

class unit_triangle : public gogl::unit
{
public:
  gogl::model *car, *drone;

  /* Unit constructor */
  unit_triangle( VOID )
  {
    car = gogl::anim::GetRef().LoadModel(std::string("bin/models/x6.g3dm"));
    drone = gogl::anim::GetRef().LoadModel(std::string("bin/models/Drone.g3dm"));
    car->Trans = gogl::matr::RotateX(-90);
  } /* End of unit constructor */
  /* Unit destructor */
  ~unit_triangle( VOID )
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
    drone->Draw(gogl::matr::Translate(gogl::vec3(5, 15 + sin(Ani->Time) * 5, 0)));
    car->Draw(gogl::matr::RotateY(Ani->Time * 45) * gogl::matr::Translate(gogl::vec3(0, 15 + sin(Ani->Time) * 5, 0)));
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
};

static gogl::anim::unit_register<unit_triangle> _("Unit Triangle");

/* End of 'unit_triangle.cpp' */