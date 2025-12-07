 /*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_cam.h
 * PURPOSE     : Animation project.
 *               Math camera handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 3.08.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __math_cam_h_
#define __math_cam_h_

/* Math library namespace */
namespace mth
{
  /* Space camera handle class */
  template<typename Type>
    class camera
    {
    public:
      vec3<Type>
        Loc,            // camera location
        Dir, Up, Right, // basis camera directions
        At;             // camera pivot point
      Type
        ProjDist,       // near project plane distance
        FarClip,        // far project plane distance
        Size,           // inner project plane rectangle size
        Wp, Hp;         // project plane size
      INT
        FrameW, FrameH; // Camera frame size in pixels
      matr<Type>
        View,           // view matrix
        Proj,           // projection matrix
        VP;             // View and Proj matrix production


      /* Camera default constructor.
       * ARGUMENTS: None.
       */
      camera( VOID ) :
        Loc(0, 0, 5), Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(0, 0, 0),
        ProjDist(0.1), FarClip(500), Size(0.1), FrameW(30), FrameH(30)
      {
        UpdateProj();
      } /* End of default constructor */

      /* Set camera projection function.
       * ARGUMENTS: 
       *   - new projection parametrs:
       *       Type NewSize, NewProj, NewFarClip;
       * RETURNS:
       *   (camera &) updated camera.
       */
      camera & SetProj( Type NewSize, Type NewProjDist, Type NewFarClip )
      {
        ProjDist = NewProjDist;
        Size = NewSize;
        FarClip = NewFarClip;

        UpdateProj();
        return *this;
      } /* End of 'SetProj' function */

      /* Set camera size function
       * ARGUMENTS: 
       *   - new frame size parametrs:
       *       Type NewFrameW, NewFrameH;
       * RETURNS:
       *   (camera &) updated camera.
       */
      camera & Resize( INT NewFrameW, INT NewFrameH )
      {
        FrameW = NewFrameW;
        FrameH = NewFrameH;

        UpdateProj();
        return *this;
      } /* End of 'Resize' function */

      /* Set camera view params function
       * ARGUMENTS: 
       *   - new view parametrs:
       *       const vec3, L, A, U;
       * RETURNS:
       *   (camera &) updated camera.
       */
      camera & SetLocAtUp( const vec3<Type> &L, 
                           const vec3<Type> &A,
                           const vec3<Type> &U = vec3<Type>(0, 1, 0) )
      {
        Loc = L;
        At = A;
        Up = U;

        Dir = (At - Loc).Normalizing();
        Right = (Dir % Up).Normalizing();
        Up = Right % Dir;

        View = matr<Type>::View(Loc, At, Up);
        UpdateProj();
        return *this;
      }

    private:
      /* Update projection function
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID UpdateProj( VOID )
      {
        Type rx = Size / 2, ry = Size / 2;

        if (FrameW > FrameH)
          rx *= (Type)FrameW / FrameH;
        else
          ry *= (Type)FrameH / FrameW;
        Wp = rx * 2;
        Hp = ry * 2;
        Proj = matr<Type>::Frustum(-rx, rx, -ry, ry, ProjDist, FarClip);
        VP = View * Proj;

      } /* End of 'UpdateProj' function */
    };
}
#endif // __mth_cam_h_
