/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : shaders.cpp
 * PURPOSE     : Animation project.
 *               Shaders resource module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 3.08.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"
#include "shaders.h"

/* Application namespace */
namespace gogl
{
  /* Save text to log file function.
   * ARGUMENTS:
   *   - text 1 to save:
   *       const std::string &Stage;
   *   - text 2 to save:
   *       const std::string &Text;
   * RETURNS: None.
   */
  VOID shader::Log( const std::string &Stage, const std::string &Text )
  {
    std::ofstream("bin/shaders/~SHD{VG6}30.LOG", std::ios_base::app) << // anim::Path + 
      Name << "\n" << Stage << ":\n" << Text << "\n";
  } /* End of 'gogl::shader::Log' function */

  /* Shader class destructor function.
   * ARGUMENTS: None.
   */
  gogl::shader::~shader( VOID )
  {
  
  } /* End of 'shader' destructor */

  /* Default shader constructor function.
   * ARGUMENTS: None.
   */
  gogl::shader::shader( VOID )
  {
  } /* Ened of 'gogl::shader::shader' function */

  /* Text file load to memory function.
   * ARGUMENTS:
   *   - file name:
   *       const std::string &FileName;
   * RETURNS:
   *   (std::string) load text.
   */
  std::string gogl::shader::LoadTextFile( const std::string &FileName )
  {
    std::ifstream f(FileName); // anim::Path + 

    return std::string((std::istreambuf_iterator<char>(f)),
                       std::istreambuf_iterator<char>());
  } /* End of 'gogl::shader::LoadTextFile' function */

  static const CHAR CommonShaderIncludes[] =
  R"separator(
  #version 460

  layout(std140, binding = 0) buffer Camera
  {
    mat4 MatrView;
    mat4 MatrProj;
    mat4 MatrVP;
    vec4 CamLocFrameW;
    vec4 CamDirProjDist;
    vec4 CamRightWp;
    vec4 CamUpHp;
    vec4 CamAtFrameH;
  };
  #define CamLoc CamLocFrameW.xyz
  #define FrameW CamLocFrameW.w
  #define CamDir CamDirProjDist.xyz
  #define ProjDist CamDirProjDist.w
  #define CamRight CamRightWp.xyz
  #define Wp CamRightWp.w
  #define CamUp CamUpHp.xyz
  #define Hp CamUpHp.w
  #define CamAt CamAtFrameH.xyz
  #define FrameH CamAtFrameH.w


  layout(std140, binding = 1) buffer Syncronization
  {
    vec4 SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime;
  };

  #define Time SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime.z

  layout(std140, binding = 2) buffer Primitive
  {
    mat4 MatrWVP;
    mat4 MatrW;
    mat4 MatrWInv;
    vec4 RndIsWireIsAny;
  };

  layout(std140, binding = 3) buffer Material
  {
    vec4 BufKa;
    vec4 BufKdTrans;
    vec4 BufKsPh;
    bool BufTextureFlags[8];
  };
  #define Ka BufKa.xyz
  #define Kd BufKdTrans.xyz
  #define Trans BufKdTrans.w
  #define Ks BufKsPh.xyz
  #define Ph BufKsPh.w
  #define IsTex0 BufTextureFlags[0]
  #define IsTex1 BufTextureFlags[1]
  #define IsTex2 BufTextureFlags[2]
  #define IsTex3 BufTextureFlags[3]
  #define IsTex4 BufTextureFlags[4]
  #define IsTex5 BufTextureFlags[5]
  #define IsTex6 BufTextureFlags[6]
  #define IsTex7 BufTextureFlags[7]
  )separator";

  /* Load shader function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (shader &) self reference.
   */
  gogl::shader & gogl::shader::Load( VOID )
  {
    std::string txt;
    BOOL isok = TRUE;
    struct shaders
    {
    public:
      std::string Name;   /* Shader name */
      INT Type;           /* Shader OpenGL type (see GL_***_SHADER) */
      std::string Define; /* Mandatory define and shader version */
      INT Id;             /* Result shader OpenGL Id */
    };
    shaders shds[] =
    {
      {"vert", GL_VERTEX_SHADER, "\n#version 460\n#define VERTEX_SHADER 1\n"},
      {"frag", GL_FRAGMENT_SHADER, "\n#version 460\n#define FRAGMENT_SHADER 1\n"},
      {"geom", GL_GEOMETRY_SHADER, "\n#version 460\n#define GEOMETRY_SHADER 1\n"},
      {"ctrl", GL_TESS_CONTROL_SHADER, "\n#version 460\n#define TESS_CONTROL_SHADER_PATCHES 1\n"},
      {"eval", GL_TESS_EVALUATION_SHADER, "\n#version 460\n#define TESS_EVALUATION_SHADER_INVOCATIONS 1\n"}
    };
    static CHAR Buf[30000];
    INT NoofS = sizeof(shds) / sizeof(shds[0]), i = 0, txt_size = 0, res;

    txt_size++;  // skip #version

    /* Load 'commondf.glsl' *
    if ((txt[txt_size + 1] = LoadTextFile("bin/shaders/includes/commondf.glsl")).c_str() != nullptr)
    {
      txt[txt_size++] = "\n#line 1 \"commondf.glsl\"\n";
      txt_size++;

    }
    /**/
    for (auto &shd : shds)
    {
      //txt = shd.Define;
      /* Load text file */
      std::string txt = LoadTextFile("bin/shaders/" + Name + "/" + shd.Name + ".glsl");

      const CHAR *Src[] = {CommonShaderIncludes, txt.c_str()};
      if (txt == "")
      {
        if (i >= 2)
          continue;
        Log("Load shaders files",  Name + "/" + shds[i].Name + "\nError load file!\n");
        isok = FALSE;
        break;
      }
      i++;
      /* Create shader */
      if ((shd.Id = glCreateShader(shd.Type)) == 0)
      {
        Log("Error shader creation", Name + "/" + shds[i].Name);
        isok = FALSE;
        break;
      }
      /* Send text to shader for compile */
      glShaderSource(shd.Id, 2, Src, nullptr);
    
      /* Compile shader */
      glCompileShader(shd.Id);
      glGetShaderiv(shd.Id, GL_COMPILE_STATUS, &res);
      if (res != 1)
      {
        glGetShaderInfoLog(shd.Id, sizeof(Buf), &res, Buf);
        Log("Compile shader", Name + "/" + shd.Name + "\n" +Buf);
        isok = FALSE;
        break;
      }
    }
    /* Create program */
    if (isok)
      if ((ProgId = glCreateProgram()) == 0)
      {
        Log("Error program creation: ", Name);
        isok = FALSE;
      }
      else
      {
        /* Attach shaders to program */
        for (auto shd : shds)
          if (shd.Id != 0)
            glAttachShader(ProgId, shd.Id);
 
        /* Link program */
        glLinkProgram(ProgId);
        glGetProgramiv(ProgId, GL_LINK_STATUS, &res);
        if (res != 1)
        {
          glGetProgramInfoLog(ProgId, sizeof(Buf), &res, Buf);
          Log("Link program error", Name + "\n" + Buf);
          isok = FALSE;
        }
      }
 
    if (!isok)
    {
      /* Handle errors */
 
      /* Delete shaders */
      for (auto shd : shds)
        if (shd.Id != 0)
        {
          if (ProgId != 0)
            glDetachShader(ProgId, shd.Id);
          glDeleteShader(shd.Id);
        }
      /* Delete program */
      if (ProgId != 0)
        glDeleteProgram(ProgId);
      ProgId = 0;
    }
    return *this;
  } /* End of 'gogl::shader::Load' function */

  /* Free shader function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID gogl::shader::Free( VOID )
  {
    UINT shds[5] {};
    INT n, i;
 
    if (ProgId == 0)
      return;
    /* Delete shaders */
    glGetAttachedShaders(ProgId, 5, &n, shds);
    /* Delete shaders */
    for (i = 0; i < n; i++)
      if (shds[i] != 0 && glIsShader(shds[i]))
      {
        glDetachShader(ProgId, shds[i]);
        glDeleteShader(shds[i]);
      }
    /* Delete program */
    glDeleteProgram(ProgId);
    ProgId = 0;
  } /* End of 'gogl::shader::Free' function */

  /* Update shader internal data info function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID shader::UpdateInfo( VOID )
  {
    // Map of OpenGL attribute types
    static std::map<INT, std::tuple<std::string, INT, BOOL, INT>> attr_types
    {
      {GL_FLOAT, {"float", 1, TRUE, 0}},
      {GL_FLOAT_VEC2, {"vec2", 2, TRUE, 0}},
      {GL_FLOAT_VEC3, {"vec3", 3, TRUE, 0}},
      {GL_FLOAT_VEC4, {"vec4", 4, TRUE, 0}},
      {GL_FLOAT_MAT2, {"mat2", 4, TRUE, 2}},
      {GL_FLOAT_MAT3, {"mat3", 9, TRUE, 3}},
      {GL_FLOAT_MAT4, {"mat4", 16, TRUE, 4}},
      {GL_FLOAT_MAT2x3, {"mat2x3", 6, TRUE, 2}},
      {GL_FLOAT_MAT2x4, {"mat2x4", 8, TRUE, 2}},
      {GL_FLOAT_MAT3x2, {"mat3x2", 6, TRUE, 3}},
      {GL_FLOAT_MAT3x4, {"mat3x4", 12, TRUE, 3}},
      {GL_FLOAT_MAT4x2, {"mat4x2", 8, TRUE, 4}},
      {GL_FLOAT_MAT4x3, {"mat4x3", 12, TRUE, 4}},
      {GL_INT, {"int", 1, FALSE, 0}},
      {GL_INT_VEC2, {"ivec2", 2, FALSE, 0}},
      {GL_INT_VEC3, {"ivec3", 3, FALSE, 0}},
      {GL_INT_VEC4, {"ivec4", 4, FALSE, 0}},
      {GL_UNSIGNED_INT, {"uint", 1, FALSE, 0}},
      {GL_UNSIGNED_INT_VEC2, {"uvec2", 2, FALSE, 0}},
      {GL_UNSIGNED_INT_VEC3, {"uvec3", 3, FALSE, 0}},
      {GL_UNSIGNED_INT_VEC4, {"uvec4", 4, FALSE, 0}},
    };

    std::vector<std::tuple<INT,
                           std::function<INT( INT, const CHAR * )>,
                           std::function<VOID( UINT, UINT, INT, INT *, INT *, GLenum *, CHAR * )>,
                           std::map<std::string, ATTR_INFO>&>> data
    {
      {GL_ACTIVE_ATTRIBUTES, glGetAttribLocation, glGetActiveAttrib, Attributes},
      {GL_ACTIVE_UNIFORMS, glGetUniformLocation, glGetActiveUniform, Uniforms},
    };

    // Fill shader attributes/uniforms info
    for (auto d : data)
    {
      INT Count;
      glGetProgramiv(ProgId, std::get<0>(d), &Count);
      std::get<3>(d).clear();
      for (INT i = 0; i < Count; i++)
      {
        CHAR name[300];
        INT size;
        GLenum type;

        std::get<2>(d)(ProgId, i, sizeof(name), nullptr, &size, &type, name);
        auto attr_info = attr_types[type];
        INT loc = std::get<1>(d)(ProgId, name);

        std::get<3>(d)[name] =
        {
          std::get<0>(attr_info),
          std::get<1>(attr_info),
          std::get<2>(attr_info),
          std::get<3>(attr_info),
          loc
        };
      }
    }

    INT CountSSBO;
    glGetProgramInterfaceiv(ProgId, GL_SHADER_STORAGE_BLOCK, GL_ACTIVE_RESOURCES,
                            &CountSSBO);
    SSBOBuffers.clear();
    for (INT i = 0; i < CountSSBO; i++)
    {
      CHAR name[300];
      glGetProgramResourceName(ProgId, GL_SHADER_STORAGE_BLOCK,
                               i, sizeof(name), nullptr, name);
      INT idx = glGetProgramResourceIndex(ProgId, GL_SHADER_STORAGE_BLOCK, name);

      GLenum prop[] {GL_BUFFER_BINDING};
      INT bind;
      glGetProgramResourceiv(ProgId, GL_SHADER_STORAGE_BLOCK,
                             idx, 1, prop, 1, NULL, &bind);
      SSBOBuffers[name] = {name, idx, bind};
    }

    // Fill shader UBO blocks info
    // INT CountUniformBlocks;
    // glGetProgramiv(ProgId, GL_ACTIVE_UNIFORM_BLOCKS, &CountUniformBlocks);
    // std::map<std::string, std::tuple<std::string, INT, INT, INT>> Blocks;
    // for (INT i = 0; i < CountUniformBlocks; i++)
    // {
    //   CHAR name[300];
    //   glGetActiveUniformBlockName(ProgId, i, sizeof(name), nullptr, name);
    // 
    //   INT idx = glGetUniformBlockIndex(ProgId, name);
    //   INT size;
    //   glGetActiveUniformBlockiv(ProgId, idx, GL_UNIFORM_BLOCK_DATA_SIZE, &size);
    //   INT bind;
    //   glGetActiveUniformBlockiv(ProgId, idx, GL_UNIFORM_BLOCK_BINDING, &bind);
    //   Blocks[name] = {name, idx, size, bind};
    // }
  } /* End of 'gogl::shader::UpdateInfo' function */
} /* End of 'gogl' namespace */


/* End of 'shaders.cpp' file */