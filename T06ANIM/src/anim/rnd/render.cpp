/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : render.cpp
 * PURPOSE     : Animation project.
 *               Render header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 4.08.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"
#include "render.h"

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
                               const VOID *UserParam )
  {
    INT len = 0;
    static CHAR Buf[10000];
 
    /* Ignore non-significant error/warning codes */
    if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204)
      return;
    len += sprintf(Buf + len, "Debug message (%i) %s\n", Id, Message);
 
    switch (Source)
    {
    case GL_DEBUG_SOURCE_API:
      len += sprintf(Buf + len, "Source: API\n");
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      len += sprintf(Buf + len, "Source: Window System\n");
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      len += sprintf(Buf + len, "Source: Shader Compiler\n");
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      len += sprintf(Buf + len, "Source: Third Party\n");
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      len += sprintf(Buf + len, "Source: Application\n");
      break;
    case GL_DEBUG_SOURCE_OTHER:
      len += sprintf(Buf + len, "Source: Other\n");
      break;
    }
 
    len += sprintf(Buf + len, "\n");
 
    switch (Type)
    {
    case GL_DEBUG_TYPE_ERROR:
      len += sprintf(Buf + len, "Type: Error");
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      len += sprintf(Buf + len, "Type: Deprecated Behaviour");
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      len += sprintf(Buf + len, "Type: Undefined Behaviour");
      break; 
    case GL_DEBUG_TYPE_PORTABILITY:
      len += sprintf(Buf + len, "Type: Portability");
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      len += sprintf(Buf + len, "Type: Performance");
      break;
    case GL_DEBUG_TYPE_MARKER:
      len += sprintf(Buf + len, "Type: Marker");
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      len += sprintf(Buf + len, "Type: Push Group");
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      len += sprintf(Buf + len, "Type: Pop Group");
      break;
    case GL_DEBUG_TYPE_OTHER:
      len += sprintf(Buf + len, "Type: Other");
      break;
    }
    len += sprintf(Buf + len, "\n");
 
    switch (Severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
      len += sprintf(Buf + len, "Severity: high");
      break;
    case GL_DEBUG_SEVERITY_MEDIUM:
      len += sprintf(Buf + len, "Severity: medium");
      break;
    case GL_DEBUG_SEVERITY_LOW:
      len += sprintf(Buf + len, "Severity: low");
      break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
      len += sprintf(Buf + len, "Severity: notification");
      break;
    }
 
    len += sprintf(Buf + len, "\n\n");
 
    OutputDebugString(Buf); 
  } /* End of 'glDebugOutput' function */

    /* Render init function
     * ARGUMENTS:
     *   - Window handler
     *       (HWND) hWnd;
     * RETURNS: (BOOL) TRUE in correct initializatoin. FALSE atherwise.
     */
    BOOL render::Init( VOID )
    {
      /* OpenGL initialization */
      INT i;
      UINT nums;
      PIXELFORMATDESCRIPTOR pfd = {0};
      HGLRC hRC;
      INT PixelAttribs[] =
      {
        WGL_DRAW_TO_WINDOW_ARB, TRUE,
        WGL_SUPPORT_OPENGL_ARB, TRUE,
        WGL_DOUBLE_BUFFER_ARB, TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 32,
        0
      };
      INT ContextAttribs[] =
      {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
                                      /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
        0
      };

      /* Prepare frame compatible device contesxt */
      hDC = GetDC(hWnd);
 
      /* OpenGL init: pixel format setup */
      pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
      pfd.nVersion = 1;
      pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
      pfd.cColorBits = 32;
      pfd.cDepthBits = 32;
      i = ChoosePixelFormat(hDC, &pfd);
 
      DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
      SetPixelFormat(hDC, i, &pfd);
 
      /* OpenGL init: rendering context setup */
      hGLRC = wglCreateContext(hDC);
      wglMakeCurrent(hDC, hGLRC);

      /* Initialize extesions (though GLEW) */
      if (glewInit() != GLEW_OK)
        return FALSE;
      wglSwapIntervalEXT(0);
  
      /* Enable a new OpenGL profile support */
      wglChoosePixelFormatARB(hDC, PixelAttribs, NULL, 1, &i, &nums);
      hRC = wglCreateContextAttribsARB(hDC, NULL, ContextAttribs);
 
      wglMakeCurrent(nullptr, nullptr);
      wglDeleteContext(hGLRC);
 
      hGLRC = hRC;
      wglMakeCurrent(hDC, hGLRC);


    #ifdef _DEBUG 

      glEnable(GL_DEBUG_OUTPUT);
      glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
      glDebugMessageCallback(glDebugOutput, NULL);
      glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE,
        0, NULL, GL_TRUE);
    #endif /* _DEBUG */

      /* Render parameters setup */
      glClearColor(0.28, 0.47, 0.8, 1);
      glEnable(GL_DEPTH_TEST);

      Cam.SetProj(0.1, 0.1, 300);
      Cam.SetLocAtUp(vec3(5), vec3(0), vec3(0, 1, 0));

      /* Create buffers */
      CamUBOStruct UBOCam;
      PrimUBOStruct UBOPrim;
      SyncUBOStruct UBOSync;
      MtlUBOStruct UBOMtl;
      CamUBO = buffer::buffer_manager::BufferCreate(0, 1, &UBOCam);
      SyncUBO = buffer::buffer_manager::BufferCreate(1, 1, &UBOSync);
      PrimUBO = buffer::buffer_manager::BufferCreate(2, 1, &UBOPrim);
      MtlUBO = buffer::buffer_manager::BufferCreate(3, 1, &UBOMtl);

      return TRUE;
    } /* End of 'Init' function */

    /* Edit render parametrs function
     * ARGUMENTS:
     *   - Render window size:
     *     (INT) NewW, NewH;
     * RETURNS: None.
     */
    VOID render::Resize( INT NewW, INT NewH )
    {
      /* Reset GL drawing window */
      glViewport(0, 0, NewW, NewH);

      /* Setup projection */
      Cam.Resize(NewW, NewH);
    } /* End of 'Resize' function */

    /* Render finish function. Delete all params.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID render::Close( VOID )
    {
      /* Deinitialization OpenGL */
      wglMakeCurrent(NULL, NULL);
      wglDeleteContext(hGLRC);
      ReleaseDC(hWnd, hDC);
    } /* End of 'render::Close' function */

    /* Start render function. Clear frame.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID render::FrameStart( VOID )
    {
      /* Clear frame */
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      shader::shader_manager::Update();
      CamUBOStruct CamBuf;
      CamBuf.CamAtFrameH = vec4(Cam.At, Cam.FrameH);
      CamBuf.CamDirProjDist = vec4(Cam.Dir, Cam.ProjDist);
      CamBuf.CamLocFrameW = vec4(Cam.Loc, Cam.FrameW);
      CamBuf.CamRightWp = vec4(Cam.Right, Cam.Wp);
      CamBuf.CamUpHp = vec4(Cam.Up, Cam.Hp);
      memcpy(CamBuf.MatrProj, Cam.Proj.M, sizeof(FLT) * 16);
      memcpy(CamBuf.MatrView, Cam.View.M, sizeof(FLT) * 16);
      memcpy(CamBuf.MatrVP,   Cam.VP.M,   sizeof(FLT) * 16);
      CamUBO->Update(&CamBuf);
    } /* End of 'render::FrameStart' function */

    /* Copy frame(drawing) function
     * ARGUMENST: None;
     * RETURNS: None.
     */
    VOID render::FrameEnd( VOID )
    {
      glFinish();
      SwapBuffers(hDC);
    } /* End of 'render::FrameEnd' function */
} /* End of 'gogl' namespace */


/* End of 'render.cpp' file */