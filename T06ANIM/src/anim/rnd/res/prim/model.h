/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : model.h
 * PURPOSE     : Animation project.
 *               Models resource header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 1.08.2024.
 * NOTE        : None.
 *
 

 */
#ifndef __model_h_
#define __model_h_
#include "gogl.h"
#include "../res.h"

/* Project namespace */
namespace gogl
{
  /* Models class */
  class model
  {
    friend class render;
  private:
    render *Rnd;
    stock<prim *> Prims; // primitives contsiner
  public:
    matr Trans;          // transparenty model matrix
    vec3 MinBB, MaxBB;   // min and max model point position
    BOOL IsLoad = FALSE; // is model load correct

    /* Default constructor */
    model( VOID ) 
    {
      Trans = matr::Identity();
    }
    model( render *NRnd ) :Rnd(NRnd)
    {
      Trans = matr::Identity();
    }

    /* Laod prims from g3dm file function
     * ARGUMENTS:
     *   - pointer to primitives structure:
     *       vg6PRIMS *Prs;
     *  - file name:
     *      CHAR *FileNameæ
     */
    model & Load( std::string FileName );

    /* Draw array of primitives function.
     * ARGUMENTS:
     *   - global transformation matrix:
     *       matr World;
     * RETURNS: None.
     */
    VOID Draw( matr World );

    /* Model manager */
    class model_manager : public resource_manager<model>
    {
      render *Rnd;
    public:
      /* class constructor */
      model_manager()
      {
      }

      model_manager( render *RndRef )
      {
        Rnd = RndRef;
      }

      /* Create primitive function.
       * ARGUMENTS:
       *   - topology base reference:
       *       const topology::base &Tpl;
       * RETURNS:
       *   (prim *) created primitive interface.
       */
      //template<class vertex_type>
        model * LoadModel( const std::string FileName )
        {
          model tmp = model(Rnd).Load(FileName);
          if (tmp.IsLoad)
            return resource_manager::Add(tmp);
          else
            return nullptr;
        } /* End of 'PrimCreate' function */
    }; /* End of 'model_manager' class */
  }; /* End of 'model' class */
} /* End of 'gogl' namespace */

#endif // __model_h_

/* End of 'model.h' file */
