/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_def.h
 * PURPOSE     : Raytracing project.
 *               Raytracing default declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 27.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __tr_def_h_
#define __tr_def_h_
#include "def.h"

#include <vector>

/* Application namespace. */
namespace gort
{
  const DBL Threshold = 0.0000001;
  class shape;

  /* intr class */
  class intr
  {
  public:
    DBL T;      // Intersection ray distance
    vec3 N;     // Intersection normal
    vec3 P;     // Point of inntersection
    shape *Shp; // Intersected shape
    INT I[5];   // Addon information
    DBL D[5];   // Addon information
    vec3 V[5];   // Addon information
    BOOL IsP;
    BOOL IsN;
    BOOL IsPlane = FALSE;
    enum ENTER_TYPE
    {
      Enter,
      Stay,
      Leave,
    } EnterFlag;
    /* Intersection constructors */
    intr( VOID )
    {
    }
    intr( shape *shp, DBL NT, ENTER_TYPE Type) : Shp(shp), T(NT), EnterFlag(Type)
    {
    }
  }; /* End of 'intr' class */

  /* Environment class */
  class envi
  {
  public:
    DBL RefractionCoef;  // Refraction coefficient
    DBL Decay;           // Environment media decay coefficient
  }; /* End of 'envi' class */

  /* light info class */
  class light_info
  {
  public:
    vec3 L;
    vec3 Color;
    DBL Dist;
  }; /* End of 'light_info' class */

  /* light class */
  class light
  {
  protected:
  public:
    DBL Cc, Cl, Cq;
    vec3 Color;
    /* Shading pixel function
     * ARGUMENTS:
     *   - possition
     *       vec3 &P;
     *   - light to do shade:
     *       light_info *L;
     * RETURN:
     *   (DBL) Shading coefficient.
     */
    virtual DBL Shadow( const vec3 &P, light_info *L )
    {
      return 0;
    }
  }; /* End of 'light' class */

  /* Shading coefficient store class */
  class coef
  {
  public:
    // Coefficient color value
    vec3 K;
    // Coefficient usage flag
    BOOL IsUsage;

    /* Class constructor */
    coef( VOID ) : IsUsage(FALSE)
    {
    } /* End of 'coef' function */

    /* Class constructor.
     * AGUMENTS:
     *   - color all components value:
     *       DBL C;
     */
    coef( DBL C ) : K(C, C, C), IsUsage(C > Threshold)
    {
    } /* End of 'coef' function */

    /* Class constructor.
     * AGUMENTS:
     *   - color component values:
     *       DBL X, Y, Z;
     */
    coef( DBL X, DBL Y, DBL Z ) :
      K(X, Y, Z),
      IsUsage(X > Threshold ||
              Y > Threshold ||
              Z > Threshold)
    {
    } /* End of 'coef' function */

    /* Class constructor.
     * AGUMENTS:
     *   - color value:
     *       const vec3 &C;
     */
    coef( const vec3 &C ) :
      K(C),
      IsUsage(C[0] > Threshold ||
              C[1] > Threshold ||
              C[2] > Threshold)
    {
    } /* End of 'coef' function */

    /* Coefficient set from vec3 function.
     * AGUMENTS:
     *   - color value:
     *       const vec3 &C;
     * RETURNS:
     *   (coef &) self reference.
     */
    coef & operator=( const vec3 &C )
    {
      K = C;
      IsUsage = C[0] > Threshold ||
                C[1] > Threshold ||
                C[2] > Threshold;
      return *this;
    } /* End of 'operator=' constructor */

    DBL MaxComponent( VOID )
    {
      return max(K[0], max(K[1], K[2]));
    }

    /* Coefficient to vec3 color conversion function.
     * AGUMENTS: None.
     * RETURNS:
     *   (vec3) color value.
     */
    operator vec3( VOID ) const
    {
      return K;
    } /* End of 'operator color' function */
  };

    /* Surface material store class */
  class surface
  {
  public:
    // Illumination coefficients
    coef Ka {0.1}, Kd {0.9}, Ks {0.0};
    // Bui Tong Phong coefficient
    DBL Ph = 47;
    // Secondary rays coefficients
    coef Kr {0}, Kt {0};
  }; /* End of 'surface' class */

  /* Shade information struct */
  struct shade_info
  {
  public:
    vec3 P;
    vec3 N;
    shape *Shp;
    surface Surf;
    envi Media;
    vec3 Du, Dv;
  };
  /* Set intr_list container */
  typedef stock<intr> intr_list;

  /* Shape class */
  class shape
  {
  public:
    envi Media;
    surface Material;
    virtual ~shape( VOID );
    virtual BOOL Intersect( const ray &R, intr *Intr );
    virtual VOID GetNormal( intr *in );
    virtual INT IsIntersect( const ray &R, intr_list &Il )
    {
      return 0;
    }
    virtual INT AllIntersect( const ray &R, intr_list &Il )
    {
      return 0;
    }
    virtual BOOL IsInside( const vec3 &P )
    {
      return 0;
    }
    VOID SetEnvi( const DBL Dec, const DBL RefrCoef )
    {
      Media.Decay = Dec;
      Media.RefractionCoef = RefrCoef;
    }
  } ; /* End of 'shape' class*/

}

#endif // __tr_def_h_


/* End of 'tr_def.h' file */