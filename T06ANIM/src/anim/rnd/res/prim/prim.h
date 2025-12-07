/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : prim.h
 * PURPOSE     : Animation project.
 *               Primmitive resource header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 3.08.2024.
 * NOTE        : None.
 *
 

 */
#ifndef __prim_h_
#define __prim_h_
#include "def.h"
#include "../../render.h"
#include "../res.h"

/* Project namespace */
namespace gogl
{
  class render;
  /* Primitive handle class */
  class prim
  {
    friend class render;
  private:
    prim_type Type {};    // Primitive type
    UINT VA {};           // Primitive vertex array
    UINT VBuf {};         // Vertex buffer
    UINT IBuf {};         // Index buffer
    INT NumOfElements {}; // Number of elements for OpenGL
  public:
    matr Transform {};    // Primitive transformation matrix
    render *Rnd;
    material *Mtl {};     // Material pointer
    vec3
      Min {},             // Minimal primitive position
      Max {};             // Maximal primitive position

    /* class constructor */
    prim( VOID )
    {
    }
    prim( render *NRnd ) : Rnd(NRnd)
    {
    }

    /* Primitive creation function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &T;
     * RETURNS:
     *   (prim &) self reference.
     */
    template<class vertex>
      prim & Create( const topology::base<vertex> &T )
        {
          Free();
          Type = T.Type;
          if (T.V.size() > 0)
          {
            glGenVertexArrays(1, &VA);
            glBindVertexArray(VA);
            glGenBuffers(1, &VBuf);
            glBindBuffer(GL_ARRAY_BUFFER, VBuf);

            glBufferData(GL_ARRAY_BUFFER, 48 * T.V.size(), T.V.data(), GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, FALSE, 48,
                                  (VOID *)0);                                /* position */
            glVertexAttribPointer(1, 2, GL_FLOAT, FALSE, 48,
                                  (VOID *)12);                      /* texture coords */
            glVertexAttribPointer(2, 3, GL_FLOAT, FALSE, 48,
                                  (VOID *)20);         /* normal */
            glVertexAttribPointer(3, 4, GL_FLOAT, FALSE, 48,
                                  (VOID *)32);         /* color */

            /* enable attribs (layout) */
            glEnableVertexAttribArray(0);
            glEnableVertexAttribArray(1);
            glEnableVertexAttribArray(2);
            glEnableVertexAttribArray(3);

            /* disenable vertex array */
            glBindVertexArray(0);
          }
          if (T.I.size() > 0)
          {
            glGenBuffers(1, &IBuf);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * T.I.size(), T.I.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            NumOfElements = T.I.size();
          }
          else
            NumOfElements = T.V.size();
          Transform = matr::Identity();

          return *this;
        } /* End of 'Create' function */

      /* Free primitive memory function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID Free( VOID )
      {
        if (VA != 0)
        {
          glBindVertexArray(VA);
          glBindBuffer(GL_ARRAY_BUFFER, 0);
          glDeleteBuffers(1, &VBuf);
          glBindVertexArray(0);
          glDeleteVertexArrays(1, &VA);
        }
        if (IBuf != 0)
          glDeleteBuffers(1, &IBuf);

      } /* End of 'Free' function */

    /* Primitive vertex normals evaluate function.
     * ARGUMENTS:
     *   - primitive base vertex:
     *       const topology::base<vertex> &T;
     * RETURNS: None.
     */
    template<class vertex>
    VOID AutoNormals( const topology::base<vertex> &T )
    {
      INT i;
 
      /* Set all vertex normals to zero */
      for (i = 0; i < T.V.size(); i++)
        T.V[i].N = vec3(0);
 
      /* Eval normal for every facet */
      for (i = 0; i < T.I.size(); i += 3)
      {
        INT
          n0 = T.I[i], n1 = T.I[i + 1], n2 = T.I[i + 2];
        vec3
          p0 = T.V[n0].P,
          p1 = T.V[n1].P,
          p2 = T.V[n2].P,
          N = ((p1 - p0) % (p2 - p0)).Normalizing();
 
        T.V[n0].N = T.V[n0].N + N;
        T.V[n1].N = T.V[n1].N + N;
        T.V[n2].N = T.V[n2].N + N;
      }
 
      /* Normalize all vertex normals */
      for (i = 0; i < T.V.size(); i++)
        T.V[i].N = T.V[i].N.Normalizing();

    } /* End of 'AutoNormals' function */

    /* Draw primitive function.
      * ARGUMENTS:
      *   - transformation 'world' matrix:
      *       MATR World;
      * RETURNS: None.
      */
    VOID Draw( matr World );

    /* Primitive manager */
    class primitive_manager : public resource_manager<prim>
    {
      render *RndPoint;
    public:
      primitive_manager( render *NRnd ) : RndPoint(NRnd)
      {
      }
      /* Create primitive function.
        * ARGUMENTS:
        *   - topology base reference:
        *       const topology::base &Tpl;
        * RETURNS:
        *   (prim *) created primitive interface.
        */
      template<class vertex_type>
        prim * PrimCreate( const topology::base<vertex_type> &Tpl )
        {
          return resource_manager::Add(prim(RndPoint).Create(Tpl));
        } /* End of 'PrimCreate' function */

      /* Free primitive function.
        * ARGUMENTS:
        *   - primitive pointer:
        *       prim *Pr;
        * RETURNS: None.
        *   (prim *) created primitive interface.
        */
      VOID PrimFree( prim *Pr )
      {
        resource_manager::Delete(Pr);
      } /* End of 'PrimFree' function */

    }; /* End of 'primitive_manager' class */

  }; /* End of 'prim' class */

} /* end of 'gogl' namespace */	

#endif // __prim_h_

/* End of 'prim.h' file */
