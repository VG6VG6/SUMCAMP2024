/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_vec3.h
 * PURPOSE     : Animation project.
 *               Math 3d vectors handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_
#include "mth_def.h"

namespace mth // Space math namespace
{
  /* 3D vector representation type */
  template<typename Type>
    class vec3
    {
    public:
      Type X, Y, Z;
      template<typename Type1> friend class matr;

      /* Get zero vector function
       * ARGUMENTS: None.
       * RETURNS: 
       *   (vec3) zero vector;
       */
      vec3<Type> Zero( VOID )
      {
        X = {};
        Y = {};
        Z = {};
        return *this;
      } /* End of 'Zero' function */

      /* default constructor */
      vec3( VOID )
      {
      }

      /* vector constructors */
      vec3( Type X1, Type Y1, Type Z1 ) : X(X1), Y(Y1), Z(Z1)
      {
      }
      explicit vec3( Type A ) : X(A), Y(A), Z(A)
      {
      }

      /* Obtain sum of two vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec3 &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator+( const vec3<Type> &A ) const
      {
        return vec3(X + A.X, Y + A.Y, Z + A.Z);
      } /* End of 'operator+' function */

      /* Obtain add vector to this vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec3 &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator+=( const vec3<Type> &A )
      {
        X += A.X, Y += A.Y, Z += A.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Obtain sum of vector and Type function.
       * ARGUMENTS:
       *   - type to be add:
       *       const Type &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator+( const Type &A ) const
      {
        return vec3(X + A, Y + A, Z + A);
      } /* End of 'operator+' function */

      /* Obtain add real Type to this vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const Type &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator+=( const Type &A )
      {
        X += A, Y += A, Z += A;
        return *this;
      } /* End of 'operator+=' function */

      /* Obtain multiplication of two vectors function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec3 &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator*( const vec3<Type> &A ) const
      {
        return vec3(X * A.X, Y * A.Y, Z * A.Z);
      } /* End of 'operator*' function */

      /* Multiplication this vector to vector function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec3 &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator*=( const vec3<Type> &A )
      {
        X *= A.X;
        Y *= A.Y;
        Z *= A.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Obtain multiplication vector by real Type function.
       * ARGUMENTS:
       *   - Type to be multiply:
       *       const Type &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator*( const Type &A ) const
      {
        return vec3(X * A, Y * A, Z * A);
      } /* End of 'operator*' function */

      /* Multiplication this vector to real Type function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const Type &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator*=( const Type &A )
      {
        X *= A;
        Y *= A;
        Z *= A;
        return *this;

      } /* End of 'operator*=' function */

      /* Obtain subtraction of two vectors function.
       * ARGUMENTS:
       *   - vector to be subtrac:
       *       const vec3 &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator-( const vec3<Type> &A ) const
      {
        return vec3(X - A.X, Y - A.Y, Z - A.Z);
      } /* End of 'operator-' function */

      /* Subtraction this vetor to vector function.
       * ARGUMENTS:
       *   - vector to be subtrac:
       *       const vec3 &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator-=( const vec3<Type> &A )
      {
        X -= A.X;
        Y -= A.Y;
        Z -= A.Z;
        return *this;
      } /* End of 'operator-=' function */

      /* Obtain subtraction vector by real Type function.
       * ARGUMENTS:
       *   - Type to be subtrac:
       *       const Type &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator-( const Type &A ) const
      {
        return vec3(X - A, Y - A, Z - A);
      } /* End of 'operator-' function */

      /* Subtraction this vetor to real Type function.
       * ARGUMENTS:
       *   - vector to be subtrac:
       *       const Type &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator-=( const Type &A )
      {
        X -= A;
        Y -= A;
        Z -= A;
        return *this;
      } /* End of 'operator-=' function */
      
      /* Obtain division of two vectors function.
       * ARGUMENTS:
       *   - vector to be divide by:
       *       const vec3 &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator/( const vec3<Type> &A ) const
      {
        return vec3(X / A.X, Y / A.Y, Z / A.Z);
      } /* End of 'operator/' function */

      /* Division this ector to vector function.
       * ARGUMENTS:
       *   - vector to be divide by:
       *       const vec3 &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator/=( const vec3<Type> &A )
      {
        X /= A.X;
        Y /= A.Y;
        Z /= A.Z;
        return *this;
      } /* End of 'operator/=' function */

      /* Obtain division vector by real Type function.
       * ARGUMENTS:
       *   - Type to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator/( const Type &A ) const
      {
        return vec3(X / A, Y / A, Z / A);
      } /* End of 'operator/' function */

      /* Division this ector to real Type function.
       * ARGUMENTS:
       *   - vector to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator/=( const Type &A )
      {
        X /= A;
        Y /= A;
        Z /= A;
        return *this;
      } /* End of 'operator/=' function */

      /* Obtain negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3<Type>) result vector.
       */
      vec3<Type> operator-( VOID ) const
      {
        return vec3(-X, -Y, -Z);
      } /* End of 'operator/' function */

      /* Dot multiplication two vectors function.
       * ARGUMENTS:
       *   - Type to be cross by:
       *       const vec3<Type> &A;
       * RETURNS:
       *   (Type) result vector.
       */
      Type Dot( const vec3<Type> &A ) const
      {
        return X * A.X + Y * A.Y + Z * A.Z;
      } /* End of 'Dot' function */

      /* Dot multiplication two vectors function.
       * ARGUMENTS:
       *   - Type to be cross by:
       *       const vec3<Type> &A;
       * RETURNS:
       *   (Type) result vector.
       */
      Type operator&( const vec3<Type> &A ) const
      {
        return X * A.X + Y * A.Y + Z * A.Z;
      } /* End of 'operator&' function */

      /* Get vector length function.
       * ARGUMENTS:
       *   - Type to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (Type) vectors length.
       */
      Type operator!( VOID ) const
      {
        Type len = *this & *this;

        if (len == 0 || len == 1)
          return len;
        return std::sqrt(len);
      } /* End of 'operator!' function */

      /* Get vector length function.
       * ARGUMENTS:
       *   - Type to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (Type) vectors length.
       */
      Type Len( VOID ) const
      {
        Type len = *this & *this;

        if (len != 0 || len != 1)
          if constexpr (std::is_same_v<Type, FLT>)
            return std::sqrtf(len);
          else
            return std::sqrt(len);
        return len;
      } /* End of 'Len' function */

      /* Countong of vector square function.
       * ARGUMENTS:
       *   - Type to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (Type) vectors square length.
       */
      Type Len2( VOID ) const
      {
        return *this & *this;
      } /* End of 'Len' function */

      /* Cross multiplication two vectors function.
       * ARGUMENTS:
       *   - Type to be cross by:
       *       const vec3<Type> &A;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3<Type> Cross( const vec3<Type> &A ) const
      {
        return vec3(Y * A.Z - Z * A.Y,
                    Z * A.X - X * A.Z,
                    X * A.Y - Y * A.X);
      } /* End of 'Cross' function */

      /* Cross multiplication two vectors function.
       * ARGUMENTS:
       *   - Type to be cross by:
       *       const vec3<Type> &A;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3<Type> operator%( const vec3<Type> &A ) const
      {
        return vec3(Y * A.Z - Z * A.Y,
                    Z * A.X - X * A.Z,
                    X * A.Y - Y * A.X);
      } /* End of 'operator%' function */

      /* Normalize this vector function
       * ARGUMENTS: None.
       * RETURNS: 
       *   (vec3 &) link to result vector.
       */
      vec3<Type> & Normalize( VOID )
      {
        *this /= !*this;
        return *this;
      } /* End of 'normalize' function */

      /* Get normalizing vector
       * ARGUMENTS: None.
       * RETURNS: 
       *   (vec3 ) result vector.
       */
      vec3<Type> Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' finction */

      /* Calculate distanse between two vectors
       * ARGUMENTS:
       *   - Second vector to calculate:
       *       const vec3<Type> &A;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3<Type> Distance( const vec3<Type> &A ) const
      {
        vec3 B(*this - A);
        if (B.X < 0)
          B.X = - B.X;
        if (B.Y < 0)
          B.Y = - B.Y;
        if (B.Z < 0 )
          B.Z = - B.Z;
        return B;
      } /* End of 'Distance' finction */

      /* Generate random vector fucntion
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) random vector.
       */
      vec3<Type> Rnd0( VOID )
      {
        return vec3((Type)(rand() % RAND_MAX),
                    (Type)(rand() % RAND_MAX),
                    (Type)(rand() % RAND_MAX));
      } /* End of 'Rnd0' function */

      /* Generate random vector from 0 till 1 fucntion
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) random vector.
       */
      static vec3<Type> Rnd1( VOID )
      {
        return vec3((Type)(rand() % RAND_MAX / (Type)RAND_MAX),
                    (Type)(rand() % RAND_MAX / (Type)RAND_MAX),
                    (Type)(rand() % RAND_MAX / (Type)RAND_MAX)) * 2 - 1;
      } /* End of 'Rnd1' function */

      /* Obtain edit vectors with [] function.
       * ARGUMENTS: 
       *   - component index:
       *       INT Index;
       * RETURNS:
       *   (Type &) link to vector component.
       */
      Type & operator[]( INT Index )
      {
        if (Index == 0)
          return X;
        if (Index == 1)
          return Y;
        return Z;
      } /* End of 'operator[]' function */

      /* Obtain edit vectors with [] function.
       * ARGUMENTS: 
       *   - component index:
       *       INT Index;
       * RETURNS:
       *   (Type &) link to vector component.
       */
      Type operator[]( INT Index ) const
      {
        if (Index == 0)
          return X;
        if (Index == 1)
          return Y;
        return Z;
      } /* End of 'operator[]' function */

      /* Obtain get pointer to vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type ) pointer to vector .
       */
      Type * operator*( VOID )
      {
        return &X;
      } /* End of 'operator*' function */

      /* Obtain multiply vector and matrix function.
       * ARGUMENTS:
       *   - matrix to multiplying:
       *       matr M;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3<Type> operator*( const matr<Type> &M ) const
      {
        FLT w = X * M.M[0][3] + Y * M.M[1][3] + Z * M.M[2][3] + M.M[3][3];
 
        return vec3((X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[2][0] + M.M[3][0]) / w,
                    (X * M.M[0][1] + Y * M.M[1][1] + Z * M.M[2][1] + M.M[3][1]) / w,
                    (X * M.M[0][2] + Y * M.M[1][2] + Z * M.M[2][2] + M.M[3][2]) / w);
      } /* End of 'operator*' function */

      /* Vector by matrix transformation function.
       * ARGUMENTS:
       *   - vector to transform:
       *       VEC3 V;
       *   - matrix to transform:
       *       MATR M;
       * RETURNS:
       *   (VEC3) transformed vector.
       */
      vec3<Type> PointTransform( const matr<Type> &M ) const
      {
        return
          vec3(X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[2][0] + M.M[3][0],
               X * M.M[0][1] + Y * M.M[1][1] + Z * M.M[2][1] + M.M[3][1],
               X * M.M[0][2] + Y * M.M[1][2] + Z * M.M[2][2] + M.M[3][2]);
      } /* End of 'PointTransform' function */

      /* Transforming vector and matrix function.
       * ARGUMENTS:
       *   - matrix to transform:
       *       MATR M;
       * RETURNS:
       *   (VEC3) transformed vector.
       */
      vec3<Type> Transform( const matr<Type> &M ) const
      {
        return
          vec3(X * M.M[0][0] + Y * M.M[1][0] + Z * M.M[2][0],
               X * M.M[0][1] + Y * M.M[1][1] + Z * M.M[2][1],
               X * M.M[0][2] + Y * M.M[1][2] + Z * M.M[2][2]);
      } /* End of 'Transform' function */

    }; /* End of 'vec3' class */
  } /* End of 'mth' namespace */

/* Obtional output vector to osstream function
 * ARGUMENTS: 
 *   - default input/out stream:
 *       std::iostream &C;
 *   - vector to write to console:
 *       mth::vec3<Type> &A;
 * RETURNS:
 *   (std::ostream &) default input/out stream with vector.
 */
template<typename Type>
std::ostream & operator<<( std::ostream &C, const mth::vec3<Type> &A )
{
  C << "<" << A[0] << ", " << A[1] << ", " << A[2] << ">" << std::endl;
  return C;
} /* End of 'operator<<' function */

#endif /* __mth_vec3_h_ */

/* End of 'mth_vec3.h' file */
