/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : buffers.h
 * PURPOSE     : Animation project.
 *               Buffers resource header module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 02.07.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __bufers_h_
#define __bufers_h_
#include "def.h"

#define MATERIAL_BIND_POINT 1

/* Project namespace */
namespace gogl
{
  /* buffer class */
  class buffer
  {
  public:
    // OpenGL buffer Id
    UINT BufId = 0;

    // Binding point
    UINT BindingPoint = 0;
  
    // Number of buffer quads
    UINT BufSize = 0;

    /* Buffer create function.
     * ARGUMENTS:
     *   - buffer binding point:
     *       UINT BufBindingPoint;
     *   - buffer data:
     *       const data_type *Data;
     * RETURNS:
     *   (buffer &) self reference.
     */
    template<typename data_type>
      buffer & Create( UINT BufBindingPoint, const data_type *Data  = {} )
      {

        Free();
        BufSize = sizeof(data_type);
        if (BufSize == 0)
          return *this;
        BindingPoint = BufBindingPoint;

        glGenBuffers(1, &BufId);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, BufId);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data_type), Data,
                     GL_DYNAMIC_DRAW);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        Apply();
        return *this;
      } /* End of 'Create' function */

    /* Buffer create function.
     * ARGUMENTS:
     *   - buffer binding point:
     *       UINT BufBindingPoint;
     *   - number of data elements:
     *       INT NumOfElements;
     *   - buffer data:
     *       const data_type *Data;
     * RETURNS:
     *   (buffer &) self reference.
     */
    template<typename data_type>
      buffer & Create( UINT BufBindingPoint, INT NumOfElements,
                       const data_type *Data  = {} )
      {
        Free();
        BufSize = sizeof(data_type) * NumOfElements;
        if (BufSize == 0)
          return *this;
        BindingPoint = BufBindingPoint;

        glGenBuffers(1, &BufId);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, BufId);
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(data_type) * NumOfElements,
                     Data, GL_DYNAMIC_COPY);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
        Apply();
        return *this;
      } /* End of 'Create' function */

    /* Buffer free function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
      glDeleteBuffers(1, &BindingPoint);
    } /* End of 'Free' function */

    /* Buffer update function.
     * ARGUMENTS:
     *   - buffer data:
     *       const data_type *Data;
     *   - start of elements update:
     *       INT Start;
     *   - length of elements, which will be updated:
     *       INT Size;
     * RETURNS: None.
     */
    template<typename data_type>
      VOID Update( const data_type *Data, INT Start = 0, INT Size = -1 )
      {  
        if (BufId == 0)
          return;
        if (Size < 0)
          Size = BufSize;
        if (Start < 0)
          Start = 0;
        if (Start + Size > BufSize)
          Size = BufSize - Start;
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, BufId);
        glBufferSubData(GL_SHADER_STORAGE_BUFFER, Start, Size, Data);
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
      } /* End of 'Update' finction */


    /* Apply buffer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Apply( VOID )
    {
      if (BufId != 0)
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BindingPoint, BufId);
    } /* End of 'Apply' function */

    /* Buffer manager */
    class buffer_manager : public resource_manager<buffer>
    {
    public:
      template<typename data_type>
        buffer * BufferCreate( UINT BufBindingPoint, INT NumOfElements, const data_type *Data  = {} )
        {
          return resource_manager::Add(buffer().Create(BufBindingPoint, NumOfElements, Data));
        }
    }; /* End of 'buffer_manager' class */

  }; /* End of 'buffer' class */
} /* End of 'gogl' namespace */

#endif // __bufers_h_

