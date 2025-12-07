/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : topology.h
 * PURPOSE     : Animation project.
 *               Topology resource header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 1.08.2024.
 * NOTE        : None.
 *
 

 */
#ifndef __topology_h_
#define __topology_h_
#include "def.h"
#include "../res.h"

/* Project namespace */
namespace gogl
{
/* Primitive shape representation type */
  enum struct prim_type
  {
    TRIMESH = GL_TRIANGLES,       /* Triangle mesh */
    POINTS = GL_POINTS,           /* Points collection */
    LINES = GL_LINES,             /* Strip of triangles */
    TRISTRIP = GL_TRIANGLE_STRIP, /* Triangle strip */
    LINESTRIP = GL_LINE_STRIP,    /* Line strip */
    PATCH = GL_PATCHES            /* Patch */
  }; /* End of 'prim_type' enum */

  /* Vertex collection namespace */
  namespace vertex
  {
    /* Standard vertex representation type */
    struct std
    {
      vec3 P;  /* Vertex position */
      vec2 T;  /* Vertex texture coordinates */
      vec3 N;  /* Normal at vertex */
      vec4 C;  /* Vertex color */
    }; /* End of 'std' structure */

    /* The only point vertex representation type */
    struct point
    {
      vec3  P;  /* Vertex position */
    }; /* End of 'point' structure */

  } /* end of 'vertex' namespace */

  /* Topology structures namespase */
  namespace topology
  {
    /* Base topology class */
    template<class vertex_type>
      class base
      {
      public:
        prim_type Type = prim_type::TRIMESH;

        /* Vertex array */
        std::vector<vertex_type> V;
        /* Index array */
        std::vector<INT> I;

      public:
        /* Class default constructor */
        base( VOID )
        {
        } /* End of 'base' function */

        /* Class constructor.
         * ARGUMENTS:
         *   - primitive type:
         *       prim_type NewType;
         *   - vertex array:
         *       const std::vector<vertex_type> &NewV;
         *   - index array:
         *       const std::vector<INT> &NewI;
         */
        base( prim_type NewType,
              const std::vector<vertex_type> &NewV = {},
              const std::vector<INT> &NewI = {} ) :
          Type(NewType), V(NewV), I(NewI)
        {
        } /* End of 'base' function */
      }; /* End of 'base' class */

    /* Trimesh topology class */
    template<class vertex_type>
      class trimesh : public base<vertex_type>
      {
      public:
        /* Class constructor.
         * ARGUMENTS:
         *   - vertex array:
         *       const std::vector<vertex> &NewV;
         *   - index array:
         *       const std::vector<INT> &NewI;
         */
        trimesh( const std::vector<vertex_type> &NewV,
                 const std::vector<INT> &NewI = {} ) :
          base<vertex_type>(prim_type::TRIMESH, NewV, NewI)
        {
        } /* End of 'trimesh' function */

        VOID EvalNormals( VOID );
        VOID EvalTangentSpace( VOID );
      }; /* End of 'trimesh' class */

  } /* end of 'topology' namespace */
} /* end of 'gogl' namespace */	

#endif // __topology_h_

/* End of 'topology.h' file */
