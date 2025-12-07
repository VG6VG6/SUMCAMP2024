/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mtl.h
 * PURPOSE     : Animation project.
 *               Materials resource header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 04.08.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __mtl_h_
#define __mtl_h_

#include "def.h"
#include "../../render.h"
#include "../resource.h"

/* Project namespace */
namespace gogl
{
  /* material class */
  class material
  {
    private:
    // Material buffer data type
    struct BUF_MTL
    {
      vec4 Ka;       // Ambient
      vec4 KdTrans;  // Diffuse + Transparency
      vec4 KsPh;     // Specular + Phong
      INT IsTex[8];  // Is teture load
    }; /* End of 'BUF_MTL' structure */

  public:
    // Material name
    std::string Name;

    // Illumination coefficients (anbient, diffuse, specular)
    vec3 Ka, Kd, Ks;
    // Phong coefficient and transparency value
    FLT Ph, Trans;
    // Shader pointer
    shader *Shd {};
    // Texture pointers
    texture *Tex[8] {};

    // Material data buffer
    buffer *BufferMtl {};

    /* Class default constructor */
    material( VOID )
    {
    } /* End of 'material' function */

    /* Class destructor */
    ~material( VOID )
    {
    } /* End of '~material' function */

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
    material & Create( const std::string &NewName,
                       const vec3 &NewKa = vec3(0.1),
                       const vec3 &NewKd = vec3(0.9),
                       const vec3 &NewKs = vec3(0.0),
                       FLT NewPh = 30, FLT NewTrans = 1,
                       shader *NewShd = nullptr,
                       std::initializer_list<texture *> Textures = {} );

    /* Material destroy function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
      delete[] BufferMtl;
    }

    /* Apply material function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (shader *) shader interface;
     */
    shader * Apply( VOID );

    /* Update material buffer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID );

    /* Materials manager */
    class material_manager : public resource_manager<material, std::string>
    {
    public:

      /* material_manager constructor */
      material_manager( VOID );

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
      material * MaterialCreate(const std::string &NewName,
                              const vec3 &NewKa = vec3(0.1),
                              const vec3 &NewKd = vec3(0.9),
                              const vec3 &NewKs = vec3(0.0),
                              FLT NewPh = 30, FLT NewTrans = 1,
                              shader *NewShd = nullptr,
                              std::initializer_list<texture *> Textures = {})
      {
        return resource_manager::Add(material().Create(NewName, NewKa, NewKd, NewKs, NewPh, NewTrans, NewShd, Textures));
      } /* End of 'MaterialCreate' function */

      /* Get material function.
       * ARGUMENTS:
       *   - material name:
       *       const std::string &NewName;
       * RETURNS:
       *   (material &) self reference.
       */
      material * MaterialFind( const std::string &NewName )
      {
        return resource_manager::Find(NewName);
      } /* End of 'MaterialCreate' function */

      /* class destructor */
      ~material_manager( VOID )
      {
        for (auto elem : Stock)
          elem.second.Free();
      } /* End of 'material_manager' class destructor */
    }; /* End of 'material_manager' class */

  }; /* End of 'material' class */
} /* End of 'gogl' namespace */

#endif // !__mtl_h_


/* End of 'mtl.h' file */
