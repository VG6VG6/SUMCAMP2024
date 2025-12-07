/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : shaders.h
 * PURPOSE     : Animation project.
 *               Shaders resource header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 2.08.2024.
 * NOTE        : None.
 *
 

 */
#ifndef __shaders_h_
#define __shaders_h_
#include "def.h"
#include "../res.h"

/* Project namespace */
namespace gogl
{
  /* shaders class */
  class shader
  {
    //friend render;

    private:
    /* Save text to log file function.
     * ARGUMENTS:
     *   - text 1 to save:
     *       const std::string &Stage;
     *   - text 2 to save:
     *       const std::string &Text;
     * RETURNS: None.
     */
    VOID Log( const std::string &Stage, const std::string &Text );

    /* Text file load to memory function.
     * ARGUMENTS:
     *   - file name:
     *       const std::string &FileName;
     * RETURNS:
     *   (std::string) load text.
     */
    std::string LoadTextFile( const std::string &FileName );

    /* Load shader function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (shader &) self reference.
     */
    shader & Load( VOID );

    /* Free shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    /* Directory watcher class */
    class dir_watcher
    {
    private:
      // Overlapped structure for changing hook
      OVERLAPPED Ovr {};
      // Traching directory handle
      HANDLE hDir {};
      // Read directory changes data buffer
      BYTE Buffer[30 * 47] {};
      // Store path
      std::string Path;

    public:
      /* Start directory watching function.
       * ARGUMENTS:
       *   - directory path:
       *       const std::string &DirPath;
       * RETURNS: None.
       */
      VOID StartWatch( const std::string &DirPath )
      {
        StopWatch();
        ZeroMemory(&Ovr, sizeof(OVERLAPPED));
        Path = DirPath;
        // Open directory
        hDir =
          CreateFile(DirPath.c_str(),
            FILE_LIST_DIRECTORY,
            FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
            nullptr, OPEN_EXISTING,
            FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
            nullptr);

        // Start monitoring
        Ovr.hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        ReadDirectoryChangesW(hDir,
          Buffer, sizeof(Buffer),
          TRUE,
          FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION |
            FILE_NOTIFY_CHANGE_FILE_NAME,
          nullptr,
          &Ovr,
          nullptr);
      } /* End of 'StartWatch' function */

      /* Stop directory watching function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID StopWatch( VOID )
      {
        if (Ovr.hEvent != nullptr)
          CloseHandle(Ovr.hEvent);
        if (hDir != nullptr)
          CloseHandle(hDir);

        ZeroMemory(&Ovr, sizeof(OVERLAPPED));
        hDir = nullptr;
        Path = "";
      } /* End of 'StopWatch' function */

      /* Check if directory is changed function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (BOOL) TRUE if directory contents is changed (and subfolders).
       */
      BOOL IsChanged( VOID )
      {
        if (Ovr.hEvent == nullptr || hDir == nullptr)
          return FALSE;

        INT id = WaitForSingleObject(Ovr.hEvent, 0);
        if (id == WAIT_OBJECT_0)
        {
          // Restart monitoring
          ResetEvent(Ovr.hEvent);
          ReadDirectoryChangesW(hDir,
            Buffer, sizeof(Buffer),
            TRUE,
            FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_CREATION |
              FILE_NOTIFY_CHANGE_FILE_NAME,
            nullptr,
            &Ovr,
            nullptr);
          return TRUE;
        }
        return FALSE;
      } /* End of 'IsChanged' function */
    }; /* End of 'dir_watcher' class */

    dir_watcher Watcher;

  public:
    // Shader name
    std::string Name;

    // Shader program Id
    UINT ProgId;

    /* Shader input attributes and uniforms information structure */
    struct ATTR_INFO
    {
      std::string SType; // String type like shader
      INT Components;    // Number of components
      BOOL IsFloat;      // Float value flag (otherwise integer)
      INT MatrRows;      // For matrix number of rows
      INT Loc;           // Shader attribute location
    }; /* End of 'ATTR_INFO' structure */

    /* Shader buffer block information structure */
    struct BLOCK_INFO
    {
      std::string SType; // String type like shader
      INT Index;         // Buffer block index
      INT Bind;          // Buffer bind point
    }; /* End of 'BLOCK_INFO' structure */

    // Attributes and uniforms information
    std::map<std::string, ATTR_INFO> Attributes, Uniforms;
    // Shader storage blocks informations (type, index, bind point)
    std::map<std::string, BLOCK_INFO> SSBOBuffers;

    /* Class default constructor */
    shader( VOID );

    /* Class constructor.
     * ARGUMENTS:
     *   - shader file name prefix:
     *       const std::string &FileNamePrefix;
     */
    shader( const std::string &FileNamePrefix )
    {
      Watcher.StopWatch();
      Watcher.StartWatch("bin/shaders/" + FileNamePrefix);
      Name = FileNamePrefix;
    } /* End of 'gogl::shader::shader' function */

    /* Class destructor */
    ~shader( VOID );

    /* Apply shader function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (UINT) shader program Id;
     */
    UINT Apply( VOID );

    /* Update shader function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID )
    {
      if (Watcher.IsChanged())
      {
        Free();
        Load();
        UpdateInfo();
        Watcher.StartWatch("bin/shaders/" + Name);
      }
    } /* End of 'gogl::shader::Update' function */

    /* Update shader internal data info function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateInfo( VOID );

    /* Shaders manager */
    class shader_manager : public resource_manager<shader, std::string>
    {
    private:
      dir_watcher Watcher;
    public:

      shader_manager( VOID )
      {
        Watcher.StartWatch("bin/shaders");
      }

      /* Create shader function.
       * ARGUMENTS:
       *   - shader file name prefix:
       *       const std::string &FileNamePrefix;
       * RETURNS:
       *   (shader *) created primitive interface.
       */
      shader * ShdCreate( const std::string &FileNamePrefix )
      {
        shader tmp = shader(FileNamePrefix).Load();
        tmp.UpdateInfo();
        return resource_manager::Add(tmp);
      } /* End of 'ShdCreate' function */

      /* Find shader function.
       * ARGUMENTS:
       *   - shader file name prefix:
       *       const std::string &FileNamePrefix;
       * RETURNS:
       *   (shader *) created primitive interface.
       */
      shader * ShdFind( const std::string &FileNamePrefix )
      {
        return resource_manager::Find(FileNamePrefix);
      } /* End of 'ShdCreate' function */

      /* Class destructor */
      ~shader_manager( void )
      {
        Watcher.StopWatch();
      } /* End of '~shader_manager' function */

      /* Update all shaders in stock function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID Update( VOID )
      {
        if (Watcher.IsChanged())
        {
          for (auto &shd : Stock)
            shd.second.Update();
        }
      } /* End of 'Update' function */

    }; /* End of 'shader_manager' function */
  }; /* End of 'shader' class */
} /* End of 'gogl' namespace */

#endif // __shaders_h_
