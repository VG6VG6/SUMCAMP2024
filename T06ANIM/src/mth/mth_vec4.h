/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_vec4.h
 * PURPOSE     : Animation project.
 *               Math 4d vectors handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 */

#ifndef __mth_vec4_h_
#define __mth_vec4_h_
#include "gogl.h"
#include "mth_def.h"

namespace mth // Space math namespace
{
  /* 4D vector representation type */
  template<typename Type>
    class vec4
    {
      template<typename Type1> friend class matr;
    public:
      Type X, Y, Z, W;

      /* Get zero vector function
       * ARGUMENTS: None.
       * RETURNS: 
       *   (vec3) zero vector;
       */
      vec4<Type> Zero( VOID )
      {
        X = {};
        Y = {};
        Z = {};
        W = {};
        return *this;
      } /* End of 'Zero' function */

      /* default constructor */
      vec4()
      {
        *this = Zero();
      }
      /* vector constructors */
      vec4( Type X1, Type Y1, Type Z1, Type W1 ) : X(X1), Y(Y1), Z(Z1), W(W1)
      {
      }
      explicit vec4( vec3<Type> V, Type A ) : X(V[0]), Y(V[1]), Z(V[2]), W(A)
      {
      }
      explicit vec4( Type A ) : X(A), Y(A), Z(A), W(A)
      {
      }

      /* Obtain sum of two vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec4 &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator+( const vec4<Type> &A ) const
      {
        return vec4(X + A.X, Y + A.Y, Z + A.Z, W + A.W);
      } /* End of 'operator+' function */

      /* Obtain add vector to this vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec4 &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator+=( const vec4<Type> &A )
      {
        X += A.X, Y += A.Y, Z += A.Z, W += A.W;
        return *this;
      } /* End of 'operator+=' function */

      /* Obtain sum of vector and Type function.
       * ARGUMENTS:
       *   - type to be add:
       *       const Type &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator+( const Type &A ) const
      {
        return vec4(X + A, Y + A, Z + A, W + A);
      } /* End of 'operator+' function */

      /* Obtain add real Type to this vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const Type &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator+=( const Type &A )
      {
        X += A, Y += A, Z += A, W += A;
        return *this;
      } /* End of 'operator+=' function */

      /* Obtain multiplication of two vectors function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec4 &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator*( const vec4<Type> &A ) const
      {
        return vec4(X * A.X, Y * A.Y, Z * A.Z, W * A.W);
      } /* End of 'operator*' function */

      /* Multiplication this vector to vector function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec4 &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator*=( const vec4<Type> &A )
      {
        X *= A.X;
        Y *= A.Y;
        Z *= A.Z;
        W *= A.W;
        return *this;
      } /* End of 'operator*=' function */

      /* Obtain multiplication vector by real Type function.
       * ARGUMENTS:
       *   - Type to be multiply:
       *       const Type &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator*( const Type &A ) const
      {
        return vec4(X * A, Y * A, Z * A, W + A);
      } /* End of 'operator*' function */

      /* Multiplication this vector to real Type function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const Type &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator*=( const Type &A )
      {
        X *= A;
        Y *= A;
        Z *= A;
        W *= A;
        return *this;

      } /* End of 'operator*=' function */

      /* Obtain subtraction of two vectors function.
       * ARGUMENTS:
       *   - vector to be subtrac:
       *       const vec4 &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator-( const vec4<Type> &A ) const
      {
        return vec4(X - A.X, Y - A.Y, Z - A.Z, W - A.W);
      } /* End of 'operator-' function */

      /* Subtraction this vetor to vector function.
       * ARGUMENTS:
       *   - vector to be subtrac:
       *       const vec4 &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator-=( const vec4<Type> &A )
      {
        X -= A.X;
        Y -= A.Y;
        Z -= A.Z;
        W -= A.W;
        return *this;
      } /* End of 'operator-=' function */

      /* Obtain subtraction vector by real Type function.
       * ARGUMENTS:
       *   - Type to be subtrac:
       *       const Type &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator-( const Type &A ) const
      {
        return vec4(X - A, Y - A, Z - A, W - A);
      } /* End of 'operator-' function */

      /* Subtraction this vetor to real Type function.
       * ARGUMENTS:
       *   - vector to be subtrac:
       *       const Type &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator-=( const Type &A )
      {
        X -= A;
        Y -= A;
        Z -= A;
        W -= A;
        return *this;
      } /* End of 'operator-=' function */
      
      /* Obtain division of two vectors function.
       * ARGUMENTS:
       *   - vector to be divide by:
       *       const vec4 &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator/( const vec4<Type> &A ) const
      {
        return vec4(X / A.X, Y / A.Y, Z / A.Z, W / A.W);
      } /* End of 'operator/' function */

      /* Division this ector to vector function.
       * ARGUMENTS:
       *   - vector to be divide by:
       *       const vec4 &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator/=( const vec4<Type> &A )
      {
        X /= A.X;
        Y /= A.Y;
        Z /= A.Z;
        W /= A.W;
        return *this;
      } /* End of 'operator/=' function */

      /* Obtain division vector by real Type function.
       * ARGUMENTS:
       *   - Type to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator/( const Type &A ) const
      {
        return vec4(X / A, Y / A, Z / A, W / A);
      } /* End of 'operator/' function */

      /* Division this ector to real Type function.
       * ARGUMENTS:
       *   - vector to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator/=( const Type &A )
      {
        X /= A;
        Y /= A;
        Z /= A;
        W /= W;
        return *this;
      } /* End of 'operator/=' function */

      /* Obtain negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4<Type>) result vector.
       */
      vec4<Type> operator-( VOID ) const
      {
        return vec4(-X, -Y, -Z, -W);
      } /* End of 'operator/' function */

      /* Dot multiplication two vectors function.
       * ARGUMENTS:
       *   - Type to be cross by:
       *       const vec4<Type> &A;
       * RETURNS:
       *   (Type) result vector.
       */
      Type Dot( const vec4<Type> &A ) const
      {
        return X * A.X + Y * A.Y + Z * A.Z + W * A.W;
      } /* End of 'Dot' function */

      /* Dot multiplication two vectors function.
       * ARGUMENTS:
       *   - Type to be cross by:
       *       const vec4<Type> &A;
       * RETURNS:
       *   (Type) result vector.
       */
      Type operator&( const vec4<Type> &A ) const
      {
        return X * A.X + Y * A.Y + Z * A.Z + W * A.W;
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
        Type len = &*this;

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
        Type len = !*this;

        if (len == 0 || len == 1)
          return len;
        return std::sqrt(len);
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

      /* Normalize this vector function
       * ARGUMENTS: None.
       * RETURNS: 
       *   (vec4 &) link to result vector.
       */
      vec4<Type> & Normalize( VOID )
      {
        *this /= !*this;
        return *this;
      } /* End of 'normalize' function */

      /* Get normalizing vector
       * ARGUMENTS: None.
       * RETURNS: 
       *   (vec4 ) result vector.
       */
      vec4<Type> Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' finction */

      /* Calculate distanse between two vectors
       * ARGUMENTS:
       *   - Second vector to calculate:
       *       const vec4<Type> &A;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4<Type> Distance( const vec4<Type> &A ) const
      {
        vec4 B(*this - A);

        if (B.X < 0)
          B.X = - B.X;
        if (B.Y < 0)
          B.Y = - B.Y;
        if (B.Z < 0 )
          B.Z = - B.Z;
        return B;
      } /* End of 'Distance' finction */

      /* Generate random vector from 0 till 1fucntion
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) random vector.
       */
      vec4<Type> Rnd0( VOID )
      {
        return vec4((Type)(rand() % RAND_MAX),
                    (Type)(rand() % RAND_MAX),
                    (Type)(rand() % RAND_MAX),
                    (Type)(rand() % RAND_MAX)).Normalize();
      } /* End of 'Rnd0' function */

      /* Generate random vector from -1 till 1 fucntion
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) random vector.
       */
      vec4<Type> Rnd1( VOID )
      {
        return Rnd0() * 2 - 1;
      } /* End of 'Rnd1' function */

      /* Obtain edit vectors with [] function.
       * ARGUMENTS: 
       *   - component index:
       *       INT Index;
       * RETURNS:
       *   (Type &) link to vector component.
       */
      Type & operator[]( INT &Index )
      {
        if (Index == 0)
          return &X;
        if (Index == 1)
          return &Y;
        if (Index == 2)
          return &Z;
        return &W;
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

    }; /* End of 'vec4' class */

  } /* End of 'mth' namespace */

/* Obtional output vector to osstream function
 * ARGUMENTS: 
 *   - default input/out stream:
 *       std::iostream &C;
 *   - vector to write to console:
 *       mth::vec4<Type> &A;
 * RETURNS:
 *   (std::ostream &) default input/out stream with vector.
 */
template<typename Type>
std::ostream & operator<<( std::ostream &C, const mth::vec4<Type> &A )
{
  C << "<" << A[0] << ", " << A[1] << ", " << A[2] << ", " << A[3] << ">" << std::endl;
  return C;
} /* End of 'operator<<' function */

#endif /* __mth_vec4_h_ */

/* End of 'mth_vec4.h' file */
