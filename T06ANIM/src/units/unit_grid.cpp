/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : unit_grid.cpp
 * PURPOSE     : Animation project.
 *               Unit sample module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 4.08.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"
#include "anim/rnd/grid.h"

class unit_grid : public gogl::unit
{
public:
  gogl::prim *PrGrid;

  /* Unit constructor */
  unit_grid( VOID )
  {
    gogl::grid Grid(gogl::anim::Get());
    Grid.LoadHeightDield("bin/images/HM/heightmap.bmp");
    if (gogl::anim::Get()->ShdFind("default") == nullptr)
      gogl::anim::Get()->ShdCreate("default");
    if (gogl::anim::Get()->MaterialFind("default") == nullptr)
      gogl::anim::Get()->MaterialCreate("default", gogl::vec3(0.1), gogl::vec3(0.3), gogl::vec3(0.5), 90, 1, gogl::anim::Get()->ShdFind("default"), {});
    Grid.AutoNormals();
    PrGrid = Grid.CreatePrim();
    PrGrid->Transform = gogl::matr::Translate(gogl::vec3(-Grid.Weiht / 2, -15, -Grid.Height / 2)) * gogl::matr::Scale(gogl::vec3(.5));
  } /* End of unit constructor */
  /* Unit destructor */
  ~unit_grid( VOID )
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
    PrGrid->Draw(gogl::matr::Identity());
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

static gogl::anim::unit_register<unit_grid> _("Unit Grid");

/* End of 'unit_grid.cpp' */