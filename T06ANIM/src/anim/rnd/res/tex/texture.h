/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : texture.h
 * PURPOSE     : Animation project.
 *               Textures resource header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 02.07.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __texture_h__
#define __texture_h__

#include "def.h"
#include "../resource.h"

/* Project namespace */
namespace gogl
{
  /* texture class */
  class texture
  {
    public:
    // Texture name
    std::string Name;

    // Image size
    INT W = 0, H = 0;

    // OpenGL texture Id
    UINT TexNo = 0;

    // texture number in g3df file
    INT TexNoG3DF = -1;

    /* Class default constructor */
    texture( VOID )
    {
    } /* End of 'texture' function */

    /* Class constructor.
     * ARGUMENTS:
     *   - texture file name:
     *       const std::string &FileName;
     */
    texture( const std::string &FileName ) : Name(FileName)
    {
    } /* End of 'texture' function */

    /* Texture create function.
     * ARGUMENTS:
     *   - texture name:
     *       const std::string &NewName;
     *   - image size:
     *       INT NewW, NewH;
     *   - components count:
     *       INT BytesPerPixel;
     *   - image pixel data:
     *       VOID *Pixels;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & Create( const std::string &NewName, INT NewW, INT NewH,
                      INT BytesPerPixel, BYTE *Pixels, BOOL IsMips = TRUE )
    {
      INT mips;

      W = NewW;
      H = NewH;
      Name = NewName;
      /* Setup OpenGL texture */
      glGenTextures(1, &TexNo);
      glBindTexture(GL_TEXTURE_2D, TexNo);

      if (IsMips)
      {
        mips = log(W > H ? W : H) / log(2);
        mips = mips < 1 ? 1 : mips;

        glTexStorage2D(GL_TEXTURE_2D, mips,
          BytesPerPixel == 4 ? GL_RGBA8 : BytesPerPixel == 3 ? GL_RGB8 : GL_R8, W, H);
      }

      if (Pixels != NULL)
      {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, 
                        BytesPerPixel == 4 ? GL_BGRA : BytesPerPixel == 3 ? GL_BGR : GL_LUMINANCE, GL_UNSIGNED_BYTE, Pixels);
      }
      if (IsMips)
        glGenerateMipmap(GL_TEXTURE_2D);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST //GL_LINEAR_MIPMAP_LINEAR
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_NEAREST //GL_LINEAR

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      glBindTexture(GL_TEXTURE_2D, 0);

      return *this;
    } /* End of 'Create' function */

    /* Texture create function.
     * ARGUMENTS:
     *   - texture file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & Create( const std::string &FileName )
    {
      image img(FileName);

      return Create(FileName, img.W, img.H, 4, img.RowsB[0][0], TRUE);
    } /* End of 'Create' function */

    /* Apply texture function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID )
    {
      glBindTexture(GL_TEXTURE_2D, TexNo);
    } /* End of 'Apply' function */

    /* Texture manager */
    class texture_manager : public resource_manager<texture>
    {
    public:

      /* Create texture by file function.
       * ARGUMENTS: Noen.
       * RETURNS:
       *   (texture *) pointer to new texture.
      */
      texture * TextureCreate( VOID )
      {
        return resource_manager::Add(texture());
      } /* End of 'TextureCreate' function */

      /* Create texture by file function.
       * ARGUMENTS:
       *   - path to texture image:
       *       const std::string &FileName;
       * RETURNS:
       *   (texture *) pointer to new texture.
      */
      texture * TextureCreate( const std::string &FileName )
      {
        return resource_manager::Add(texture(FileName).Create(FileName));
      } /* End of 'TextureCreate' function */

      /* Texture create function.
       * ARGUMENTS:
       *   - texture name:
       *       const std::string &NewName;
       *   - image size:
       *       INT NewW, NewH;
       *   - components count:
       *       INT BytesPerPixel;
       *   - image pixel data:
       *       VOID *Pixels;
       * RETURNS:
       *   (texture &) self reference.
       */
      texture * TextureCreate( const std::string &NewName, INT NewW, INT NewH,
                               INT BytesPerPixel, BYTE *Pixels, BOOL IsMips = TRUE )
      {
        return resource_manager::Add(texture(NewName).Create(NewName, NewW, NewH, BytesPerPixel, Pixels, IsMips));
      } /* End of 'TextureCreate' function */

      /* class cinstuctor */
      texture_manager( VOID )
      {
      }

      /* class destructor */
      ~texture_manager( VOID )
      {}
    };

  }; /* End of 'texture' class */
} /* End of 'gogl' namespace */

#endif // __texture_h__

/* End of 'texture.h' file */