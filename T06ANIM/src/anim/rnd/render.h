/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : render.h
 * PURPOSE     : Animation project.
 *               Render header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 1.08.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __render_h_
#define __render_h_

#pragma comment(lib, "opengl32")

#define GLEW_STATIC
#include <glew.h>
#include <wglew.h>
#include <gl/wglext.h>

#include "def.h"
#include "res/res.h"

/* Application namespace */
namespace gogl
{
  /* Debug output function.
   * ARGUMENTS:
   *   - source APi or device:
   *       UINT Source;
   *   - error type:
   *       UINT Type;
   *   - error message id:
   *       UINT Id, 
   *   - message severity:
   *       UINT severity, 
   *   - message text length:
   *       INT Length, 
   *   - message text:
   *       CHAR *Message, 
   *   - user addon parameters pointer:
   *       VOID *UserParam;
   * RETURNS: None.
   */
  VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                               INT Length, const CHAR *Message,
                               const VOID *UserParam );
  /* Render class */
  class render : public prim::primitive_manager, public shader::shader_manager, public texture::texture_manager, 
                 public material::material_manager, public model::model_manager, public buffer::buffer_manager
  {
  private:
    HWND &hWnd;
    HDC hDC;
    HGLRC hGLRC;

  public:

    camera Cam;

    buffer 
      *CamUBO,
      *SyncUBO,
      *PrimUBO,
      *MtlUBO;

    render( HWND &hNewWnd ) : hWnd(hNewWnd), primitive_manager(this), model_manager(this)
    {
    }
    ~render( VOID )
    {
    }
 
    /* Render init function
     * ARGUMENTS:
     *   - Window handler
     *       (HWND) hWnd;
     * RETURNS: (BOOL) TRUE in correct initializatoin. FALSE atherwise.
     */
    BOOL Init( VOID );
 
    /* Render finish function. Delete all params.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID );

    /* Edit render parametrs function
     * ARGUMENTS:
     *   - Render window size:
     *     (INT) NewW, NewH;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH );
 
    /* Start renderfunction. Clear frame.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameStart( VOID );

    /* Copy frame(drawing) function
     * ARGUMENST: None;
     * RETURNS: None.
     */
    VOID FrameEnd( VOID );

    /* Primitive draw function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     *   - transformation matrix:
     *       const matr &World;
     * RETURNS: None.
     */
    VOID Draw( const prim *Pr, const matr &World = matr::Identity() );
  }; /* End of 'render' class */
} /* End of 'gogl' namespace */


#endif // __render_h_


/* End of 'render.h' file */