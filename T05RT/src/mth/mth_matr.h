/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_matr.h
 * PURPOSE     : Raytracing project.
 *               Math matrix handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 23.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_matr_h
#define __mth_matr_h
#include "mth_def.h"

namespace mth // Space math namespace
{
  /* Matrix representation type */
  template<typename Type>
  class matr
  {
    template<typename Type1> friend class vec3;
  private:
    mutable Type InvM[4][4];
    mutable Type TransM[4][4];
    mutable bool IsInverseEvaluated;
    mutable bool IsTranspositionEvaluated;
  public:
    Type M[4][4];

    /* Matr default constructor
     * ARGUMETS: None.
     */
    matr() : IsInverseEvaluated(false), IsTranspositionEvaluated(false)
    {
    } /* End of 'matr' default constrictor */

    /* Matrix constructor 4x4
     * ARGUMENTS:
     *   - matrix elements:
     *       Type A00, A01, A02, A03,
     *            A10, A11, A12, A13,
     *            A20, A21, A22, A23,
     *            A30, A31, A32, A33;
    */
    matr( Type A00, Type A01, Type A02, Type A03,
          Type A10, Type A11, Type A12, Type A13,
          Type A20, Type A21, Type A22, Type A23,
          Type A30, Type A31, Type A32, Type A33) : IsInverseEvaluated(false), IsTranspositionEvaluated(false), M{{A00, A01, A02, A03},
                                                                                                                  {A10, A11, A12, A13},
                                                                                                                  {A20, A21, A22, A23},
                                                                                                                  {A30, A31, A32, A33}}
    {
    } /* End of 'matr' constructor */

    /* Matrix constructor 4x4
     * ARGUMENTS:
     *   - matrix elements:
     *       Type A[4][4];
    */
    matr( Type A[4][4] ) : IsInverseEvaluated(false), IsTranspositionEvaluated(false), M{{A[0][0], A[0][1], A[0][2], A[0][3]},
                                                                                         {A[1][0], A[1][1], A[1][2], A[1][3]},
                                                                                         {A[2][0], A[2][1], A[2][2], A[2][3]},
                                                                                         {A[3][0], A[3][1], A[3][2], A[3][3]}}
    {
    } /* End of 'matr' constructor */

    /* Get identity matrix function
     * ARGUMENTS: None.
     * RETURN:
     *   (matr) identity matrix.
     */
    matr<Type> MatrIdentity( VOID )
    {
      return (Identity());
    } /* End of 'MatrIdentity' function*/

    private:

    /* Counting matrix (3x3) determination function
     * ARGUMENTS: 
     *   - matrix elements:
     *       Type A00, A01, A02,
     *            A10, A11, A12,
     *            A20, A21, A22;
     * RETURNS:
     *   (Type) determination of matrix.
     */
    Type Determ3x3(Type A00, Type A01, Type A02,
                   Type A10, Type A11, Type A12,
                   Type A20, Type A21, Type A22) const
    {
      return (A00 * A11 * A22 + A01 * A12 * A20 + A02 * A10 * A21 - 
              A00 * A12 * A21 - A01 * A10 * A22 - A02 * A11 * A20 );
    } /* End of 'Determ3x3' function */

    /* Get/calculate inverse matrix functoinon.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EvaluareInverseMatrix( VOID )
    {
      if (IsInverseEvaluated)
        return;
      IsInverseEvaluated = true;

      matr r;
      Type det = Determ();

      if (det == 0)
      {
        r = Identity();
        std::memcpy(InvM, r.M[0], 16 * sizeof(Type));
        return;
      }

      /* Build adjoint matrix */
      r.M[0][0] = + Determ3x3(M[1][1], M[1][2], M[1][3],
                              M[2][1], M[2][2], M[2][3],
                              M[3][1], M[3][2], M[3][3]) / det;
      r.M[1][0] = - Determ3x3(M[1][0], M[1][2], M[1][3],
                              M[2][0], M[2][2], M[2][3],
                              M[3][0], M[3][2], M[3][3]) / det;
      r.M[2][0] = + Determ3x3(M[1][0], M[1][1], M[1][3],
                              M[2][0], M[2][1], M[2][3],
                              M[3][0], M[3][1], M[3][3]) / det;
      r.M[3][0] = - Determ3x3(M[1][0], M[1][1], M[1][2],
                              M[2][0], M[2][1], M[2][2],
                              M[3][0], M[3][1], M[3][2]) / det;

      r.M[0][1] = - Determ3x3(M[0][1], M[0][2], M[0][3],
                              M[2][1], M[2][2], M[2][3],
                              M[3][1], M[3][2], M[3][3]) / det;
      r.M[1][1] = + Determ3x3(M[0][0], M[0][2], M[0][3],
                              M[2][0], M[2][2], M[2][3],
                              M[3][0], M[3][2], M[3][3]) / det;
      r.M[2][1] = - Determ3x3(M[0][0], M[0][1], M[0][3],
                              M[2][0], M[2][1], M[2][3],
                              M[3][0], M[3][1], M[3][3]) / det;
      r.M[3][1] = + Determ3x3(M[0][0], M[0][1], M[0][2],
                              M[2][0], M[2][1], M[2][2],
                              M[3][0], M[3][1], M[3][2]) / det;

      r.M[0][2] = + Determ3x3(M[0][1], M[0][2], M[0][3],
                              M[1][1], M[1][2], M[1][3],
                              M[3][1], M[3][2], M[3][3]) / det;
      r.M[1][2] = - Determ3x3(M[0][0], M[0][2], M[0][3],
                              M[1][0], M[1][2], M[1][3],
                              M[3][0], M[3][2], M[3][3]) / det;
      r.M[2][2] = + Determ3x3(M[0][0], M[0][1], M[0][3],
                              M[1][0], M[1][1], M[1][3],
                              M[3][0], M[3][1], M[3][3]) / det;
      r.M[3][2] = - Determ3x3(M[0][0], M[0][1], M[0][2],
                              M[1][0], M[1][1], M[1][2],
                              M[3][0], M[3][1], M[3][2]) / det;

      r.M[0][3] = - Determ3x3(M[0][1], M[0][2], M[0][3],
                              M[1][1], M[1][2], M[1][3],
                              M[2][1], M[2][2], M[2][3]) / det;
      r.M[1][3] = + Determ3x3(M[0][0], M[0][2], M[0][3],
                              M[1][0], M[1][2], M[1][3],
                              M[2][0], M[2][2], M[2][3]) / det;
      r.M[2][3] = - Determ3x3(M[0][0], M[0][1], M[0][3],
                              M[1][0], M[1][1], M[1][3],
                              M[2][0], M[2][1], M[2][3]) / det;
      r.M[3][3] = + Determ3x3(M[0][0], M[0][1], M[0][2],
                              M[1][0], M[1][1], M[1][2],
                              M[2][0], M[2][1], M[2][2]) / det;
      std::memcpy(InvM, r.M[0], 16 * sizeof(Type));
    } /* End of 'EvaluareInverseMatrix' function */


    /* Get/calculate transposition matrix functoinon.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EvaluareTranspositionMatrix( VOID )
    {
      if (IsTranspositionEvaluated)
        return;
      IsTranspositionEvaluated = true;

      std::memcpy(TransM, matr(M[0][0], M[1][0], M[2][0], M[3][0], 
                           M[0][1], M[1][1], M[2][1], M[3][1], 
                           M[0][2], M[1][2], M[2][2], M[3][2],
                           M[0][3], M[1][3], M[2][3], M[3][3]).M[0], 16 * sizeof(Type));
    } /* End of 'EvaluareTranspositionMatrix' function */

    /* Counting matrix  determination function
     * ARGUMENTS: None. 
     * RETURNS:
     *   (Type) determination of matrix.
     */
    Type Determ( VOID ) const
    {
      return
      +M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                           M[2][1], M[2][2], M[2][3],
                           M[3][1], M[3][2], M[3][3]) + 
      -M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                           M[2][0], M[2][2], M[2][3],
                           M[3][0], M[3][2], M[3][3]) + 
      +M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                           M[2][0], M[2][1], M[2][3],
                           M[3][0], M[3][1], M[3][3]) + 
      -M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                           M[2][0], M[2][1], M[2][2],
                           M[3][0], M[3][1], M[3][2]);
    } /* End of 'Determ' function */

    public:
    /* Obtain counting matrix determination function
     * ARGUMENTS: None. 
     * RETURNS:
     *   (Type) determination of matrix.
     */
    Type operator!( VOID ) const
    {
      return
      +M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                           M[2][1], M[2][2], M[2][3],
                           M[3][1], M[3][2], M[3][3]) + 
      -M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                           M[2][0], M[2][2], M[2][3],
                           M[3][0], M[3][2], M[3][3]) + 
      +M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                           M[2][0], M[2][1], M[2][3],
                           M[3][0], M[3][1], M[3][3]) + 
      -M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                           M[2][0], M[2][1], M[2][2],
                           M[3][0], M[3][1], M[3][2]);
    } /* End of 'Determ' function */
    
    /* Obtain multiplying two matrix
     * ARGIMENTS:
     *   - matrix to be multiply:
     *       matr A;
     * RETIURNS:
     *   (matr) result matr.
     */
    matr<Type> operator*( matr<Type> M ) const
    {
      matr<Type> r = {};

      r.M[0][0] = M[0][0] * M.M[0][0] + M[0][1] * M.M[1][0] + M[0][2] * M.M[2][0] + M[0][3] * M.M[3][0];
      r.M[0][1] = M[0][0] * M.M[0][1] + M[0][1] * M.M[1][1] + M[0][2] * M.M[2][1] + M[0][3] * M.M[3][1];
      r.M[0][2] = M[0][0] * M.M[0][2] + M[0][1] * M.M[1][2] + M[0][2] * M.M[2][2] + M[0][3] * M.M[3][2];
      r.M[0][3] = M[0][0] * M.M[0][3] + M[0][1] * M.M[1][3] + M[0][2] * M.M[2][3] + M[0][3] * M.M[3][3];

      r.M[1][0] = M[1][0] * M.M[0][0] + M[1][1] * M.M[1][0] + M[1][2] * M.M[2][0] + M[1][3] * M.M[3][0];
      r.M[1][1] = M[1][0] * M.M[0][1] + M[1][1] * M.M[1][1] + M[1][2] * M.M[2][1] + M[1][3] * M.M[3][1];
      r.M[1][2] = M[1][0] * M.M[0][2] + M[1][1] * M.M[1][2] + M[1][2] * M.M[2][2] + M[1][3] * M.M[3][2];
      r.M[1][3] = M[1][0] * M.M[0][3] + M[1][1] * M.M[1][3] + M[1][2] * M.M[2][3] + M[1][3] * M.M[3][3];

      r.M[2][0] = M[2][0] * M.M[0][0] + M[2][1] * M.M[1][0] + M[2][2] * M.M[2][0] + M[2][3] * M.M[3][0];
      r.M[2][1] = M[2][0] * M.M[0][1] + M[2][1] * M.M[1][1] + M[2][2] * M.M[2][1] + M[2][3] * M.M[3][1];
      r.M[2][2] = M[2][0] * M.M[0][2] + M[2][1] * M.M[1][2] + M[2][2] * M.M[2][2] + M[2][3] * M.M[3][2];
      r.M[2][3] = M[2][0] * M.M[0][3] + M[2][1] * M.M[1][3] + M[2][2] * M.M[2][3] + M[2][3] * M.M[3][3];

      r.M[3][0] = M[3][0] * M.M[0][0] + M[3][1] * M.M[1][0] + M[3][2] * M.M[2][0] + M[3][3] * M.M[3][0];
      r.M[3][1] = M[3][0] * M.M[0][1] + M[3][1] * M.M[1][1] + M[3][2] * M.M[2][1] + M[3][3] * M.M[3][1];
      r.M[3][2] = M[3][0] * M.M[0][2] + M[3][1] * M.M[1][2] + M[3][2] * M.M[2][2] + M[3][3] * M.M[3][2];
      r.M[3][3] = M[3][0] * M.M[0][3] + M[3][1] * M.M[1][3] + M[3][2] * M.M[2][3] + M[3][3] * M.M[3][3];

      return r;
    } /* End of 'operator*' dunction */

    /* Creating inversion matrix function
     * ARGUMENTS: None.
     * RESULTS:
     *   (matr) inversion matrix.
     */
    matr<Type> Inverse( VOID )
    {
      EvaluareInverseMatrix();
      return matr(InvM);
    } /* End of 'Inverse' function */

    /***
    * Static methods
    ***/

    /* Get identity matrix function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    static matr<Type> Identity( VOID )
    {
      return matr<Type>(
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          0, 0, 0, 1);
    } /* End of 'Identity' function */

    /* Making rotation matrix by arbitary vector function
     * ARGUMENTS: 
     *   - angle value in degree:
     *       DBL Deg;
     *   - arbitrary vector of rotation:
     *       vec3 &A;
     * RETURNS:
     *   (matr) rotate matrix.
     */
    template<typename Type1>
    static matr<Type> Rotate( DBL Deg, const vec3<Type1> &V )
    {
      DBL Angl = D2R(Deg);
      DBL si = sin(Angl), co = cos(Angl);
      return matr<Type>(
            co + V.X * V.X * (1 - co), V.Y * V.X * (1 - co) - V.Z * si, V.Z * V.X * (1 - co) + V.Y * si, 0,
            V.X * V.Y * (1 - co) + V.Z * si, co + V.Y * V.Y * (1 - co), V.Z * V.Z * (1 - co) - V.X * si, 0,
            V.X * V.Z * (1 - co) - V.Y * si, V.Y * V.Z * (1 - co) + V.X * si, co + V.Z * V.Z * (1 - co), 0,
            0, 0, 0, 1);
    } /* End of 'Rotate' function */

    /* Making rotation matrix by X function
     * ARGUMENTS: 
     *   - angle value in degree:
     *       DBL Deg;
     * RETURNS:
     *   (matr) rotate matrix.
     */
    static matr<Type> RotateX( DBL Deg )
    {
      DBL Angl = D2R(Deg);
      DBL si = sin(Angl), co = cos(Angl);
      return matr(1, 0, 0, 0,
                  0, co, si, 0,
                  0, -si, co, 0,
                  0, 0, 0, 1);
    } /* End of 'RotateX' function */

    /* Making rotation matrix by Y function
     * ARGUMENTS: 
     *   - angle value in degree:
     *       DBL Deg;
     * RETURNS:
     *   (matr) rotate matrix.
     */
    static matr<Type> RotateY( DBL Deg )
    {
      DBL Angl = D2R(Deg);
      DBL si = sin(Angl), co = cos(Angl);
      return matr(
            co, 0, -si, 0,
            0, 1, 0, 0,
            si, 0, co, 0,
            0, 0, 0, 1);
    } /* End of 'RotateY' function */

    /* Making rotation matrix by Z function
     * ARGUMENTS: 
     *   - angle value in degree:
     *       DBL Deg;
     * RETURNS:
     *   (matr) rotate matrix.
     */
    static matr<Type> RotateZ( DBL Deg )
    {
      DBL Angl = D2R(Deg);
      DBL si = sin(Angl), co = cos(Angl);
      return matr(
            co, si, 0, 0,
            -si, co, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1);
    } /* End of 'RotateZ' function */

    /* Making scale matrix
     * ARGUMENTS:
     *   - scaling vector:
     *       const vec3 A;
     * RETURNS:
     *   (matr) scale matrix.
    */
    template<typename Type1>
    static matr<Type> Scale( const vec3<Type1> &A )
    {
      return matr(
          A.X, 0, 0, 0,
          0, A.Y, 0, 0,
          0, 0, A.Z, 0,
          0, 0, 0, 1);
    } /* End of 'Scale' function */

    /* Making scale matrix
     * ARGUMENTS:
     *   - scaling vector:
     *       const vec3 A;
     * RETURNS:
     *   (matr) scale matrix.
    */
    template<typename Type1>
    static matr<Type> Translate( const vec3<Type1> &A )
    {
      return matr(
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          A.X, A.Y, A.Z, 1);
    } /* End of 'Translate' function */

    /***
    * Camera matrix
    ***/

    /* Matrix look-at viewer setup function.
     * ARGUMENTS:
     *   - viewer position, look-at point, approximat up direction:
     *       vec3 Loc, At, Up1;
     * RETURNS:
     *   (matr) result matrix.
     */
    template<typename Type1>
    static matr<Type> View( const vec3<Type1> &Loc, const vec3<Type1> &At, const vec3<Type1> &Up1 )
    {
      vec3<Type1> Dir = (At - Loc), Right = (Dir % Up1), Up = (Right % Dir);
      Dir.Normalize(), Right.Normalize(), Up.Normalize();
      return matr<Type>( Right.X, Up.X, -Dir.X, 0,
          Right.Y, Up.Y, -Dir.Y, 0,
          Right.Z, Up.Z, -Dir.Z, 0,
          -(Loc & Right), -(Loc & Up), (Loc & Dir), 1);
    } /* End of 'View' function */

    /* Matrix frustum setup function
     *  ARGUMENTS:
     *   - size of projection space:
     *       <Type> L, R, B, T, N, F;
     * RETURNS:
     *   (matr) result frustum matrix.
     */
    static matr<Type> Frustum( Type L, Type R, Type B, Type T, Type N, Type F)
    {
      return matr((2 * N) / (R - L), 0, 0, 0,
                  0, (2 * N) / (T - B), 0, 0,
                  (R + L) / (R - L), (T + B) / (T - B), (-((F + N) / (F - N))), (-1),
                  0, 0, (-((2 * N * F) / (F - N))), 0);
    } /* End of 'Frustum' functino */

    /* Making transposition of matrix function.
     *  ARGUMENTS: None
     * RETURNS:
     *   (matr) transposition of matrix.
     */
    matr<Type> Transpose( VOID )
    {
      EvaluareTranspositionMatrix();
      return matr(TransM);
    } /* End of 'Transpose' function */

    /* Matrix ortho setup fuction.
     * ARGUMENTS:
     *   - size of projection space:
     *       <Type> L, R, B, T, N, F;
     * RETURNS:
     *   (matr) result matrix.
     */
    static matr<Type> Ortho( Type L, Type R, Type B, Type T, Type N, Type F )
    {
      return matr(
          2 / (R - L), 0, 0, 0,
          0, 2 / (T - B), 0, 0,
          0, 0, -2 / (F - N), 0,
          -(R + L) / (R - L), -(T + B) / (T - B), -(F + N) / (F - N), 1);
    } /* End of 'Ortho' function */
  } /* End of 'matr' class */;
} /* End of 'mth' namespace */

/* Obtional output vector to osstream function
 * ARGUMENTS: 
 *   - 
 */
template<typename Type>
std::ostream & operator<<( std::ostream &C, const mth::matr<Type> &A )
{
  C << "<" << A.M[0][0] << ", " << A.M[0][1] << ", " << A.M[0][2] << ", " << A.M[0][3] << ">" << "\n";
  C << "<" << A.M[1][0] << ", " << A.M[1][1] << ", " << A.M[1][2] << ", " << A.M[1][3] << ">" << "\n";
  C << "<" << A.M[2][0] << ", " << A.M[2][1] << ", " << A.M[2][2] << ", " << A.M[2][3] << ">" << "\n";
  C << "<" << A.M[3][0] << ", " << A.M[3][1] << ", " << A.M[3][2] << ", " << A.M[3][3] << ">" << "\n" << std::endl;
  return C;
} /* End of 'operator<<' function */
#endif // __mth_matr_h



