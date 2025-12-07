/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : mth_vec2.h
 * PURPOSE     : Raytracing project.
 *               Math 2d vectors handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "gort.h"

#ifndef __mth_vec2_h
#define __mth_vec2_h
#include "mth_def.h"

namespace mth // Space math namespace
{
  /* 3D vector representation type */
  template<typename Type>
    class vec2
    {
      friend class matr<Type>;

    private:
      Type X, Y;
    public:

    /* Get zero vector function
      * ARGUMENTS: None.
      * RETURNS: 
      *   (vec3) zero vector;
      */
    vec2<Type> Zero( VOID )
    {
      X = {};
      Y = {};
      return *this;
    } /* End of 'Zero' function */

      /* default constructor */
      vec2()
      {
        *this = Zero;
      }
      /* vector constructors */
      vec2( Type X1, Type Y1) : X(X1), Y(Y1)
      {
      }
      explicit vec2( Type A ) : X(A), Y(A)
      {
      }

      /* Obtain sum of two vectors function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec2 &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator+( const vec2<Type> &A ) const
      {
        return vec2(X + A.X, Y + A.Y);
      } /* End of 'operator+' function */

      /* Obtain add vector to this vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const vec2 &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator+=( const vec2<Type> &A )
      {
        X += A.X, Y += A.Y;
        return *this;
      } /* End of 'operator+=' function */

      /* Obtain sum of vector and Type function.
       * ARGUMENTS:
       *   - type to be add:
       *       const Type &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator+( const Type &A ) const
      {
        return vec2(X + A, Y + A);
      } /* End of 'operator+' function */

      /* Obtain add real Type to this vector function.
       * ARGUMENTS:
       *   - vector to be add:
       *       const Type &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator+=( const Type &A )
      {
        X += A, Y += A;
        return *this;
      } /* End of 'operator+=' function */

      /* Obtain multiplication of two vectors function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec2 &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator*( const vec2<Type> &A ) const
      {
        return vec2(X * A.X, Y * A.Y);
      } /* End of 'operator*' function */

      /* Multiplication this vector to vector function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const vec2 &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator*=( const vec2<Type> &A )
      {
        X *= A.X;
        Y *= A.Y;
        return *this;
      } /* End of 'operator*=' function */

      /* Obtain multiplication vector by real Type function.
       * ARGUMENTS:
       *   - Type to be multiply:
       *       const Type &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator*( const Type &A ) const
      {
        return vec2(X * A, Y * A);
      } /* End of 'operator*' function */

      /* Multiplication this vector to real Type function.
       * ARGUMENTS:
       *   - vector to be multiply:
       *       const Type &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator*=( const Type &A )
      {
        X *= A;
        Y *= A;
        return *this;
      } /* End of 'operator*=' function */

      /* Obtain subtraction of two vectors function.
       * ARGUMENTS:
       *   - vector to be subtrac:
       *       const vec2 &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator-( const vec2<Type> &A ) const
      {
        return vec2(X - A.X, Y - A.Y);
      } /* End of 'operator-' function */

      /* Subtraction this vetor to vector function.
       * ARGUMENTS:
       *   - vector to be subtrac:
       *       const vec2 &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator-=( const vec2<Type> &A )
      {
        X -= A.X;
        Y -= A.Y;
        return *this;
      } /* End of 'operator-=' function */

      /* Obtain subtraction vector by real Type function.
       * ARGUMENTS:
       *   - Type to be subtrac:
       *       const Type &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator-( const Type &A ) const
      {
        return vec2(X - A, Y - A);
      } /* End of 'operator-' function */

      /* Subtraction this vetor to real Type function.
       * ARGUMENTS:
       *   - vector to be subtrac:
       *       const Type &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator-=( const Type &A )
      {
        X -= A;
        Y -= A;
        return *this;
      } /* End of 'operator-=' function */
      
      /* Obtain division of two vectors function.
       * ARGUMENTS:
       *   - vector to be divide by:
       *       const vec2 &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator/( const vec2<Type> &A ) const
      {
        return vec2(X / A.X, Y / A.Y);
      } /* End of 'operator/' function */

      /* Division this ector to vector function.
       * ARGUMENTS:
       *   - vector to be divide by:
       *       const vec2 &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator/=( const vec2<Type> &A ) const
      {
        X /= A.X;
        Y /= A.Y;
        return *this;
      } /* End of 'operator/=' function */

      /* Obtain division vector by real Type function.
       * ARGUMENTS:
       *   - Type to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator/( const Type &A ) const
      {
        return vec2(X / A, Y / A);
      } /* End of 'operator/' function */

      /* Division this ector to real Type function.
       * ARGUMENTS:
       *   - vector to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator/=( const Type &A ) const
      {
        X /= A;
        Y /= A;
        return *this;
      } /* End of 'operator/=' function */

      /* Obtain negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2<Type>) result vector.
       */
      vec2<Type> operator-( void ) const
      {
        return vec2(-X, -Y);
      } /* End of 'operator/' function */

      /* Dot multiplication two vectors function.
       * ARGUMENTS:
       *   - Type to be cross by:
       *       const vec2<Type> &A;
       * RETURNS:
       *   (Type) result vector.
       */
      Type Dot( const vec2<Type> &A ) const
      {
        return X * A.X + Y * A.Y;
      } /* End of 'Dot' function */

      /* Dot multiplication two vectors function.
       * ARGUMENTS:
       *   - Type to be cross by:
       *       const vec2<Type> &A;
       * RETURNS:
       *   (Type) result vector.
       */
      Type operator&( const vec2<Type> &A ) const
      {
        return X * A.X + Y * A.Y;
      } /* End of 'operator&' function */

      /* Get vector length function.
       * ARGUMENTS:
       *   - Type to be divide by:
       *       const Type &A;
       * RETURNS:
       *   (Type) vectors length.
       */
      Type operator!( void ) const
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
      Type Len( void ) const
      {
        Type len = &*this;

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
      Type Len2( void ) const
      {
        return *this & *this;
      } /* End of 'Len' function */

      /* Normalize this vector function
       * ARGUMENTS: None.
       * RETURNS: 
       *   (vec2 &) link to result vector.
       */
      vec2<Type> & Normalize( VOID )
      {
        *this /= !*this;
        return *this;
      } /* End of 'normalize' function */

      /* Get normalizing vector
       * ARGUMENTS: None.
       * RETURNS: 
       *   (vec2 ) result vector.
       */
      vec2<Type> Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' finction */

      /* Calculate distanse between two vectors
       * ARGUMENTS:
       *   - Second vector to calculate:
       *       const vec2<Type> &A;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2<Type> Distance( const vec2<Type> &A ) const
      {
        vec2 B(*this - A);
        if (B.X < 0)
          B.X = - B.X;
        return Y;
      } /* End of 'Distance' finction */

      /* Generate random vector fucntion
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) random vector.
       */
      vec2<Type> Rnd0( VOID )
      {
        return vec2((Type)(rand() % RAND_MAX),
                    (Type)(rand() % RAND_MAX)).Normalize();
      } /* End of 'Rnd0' function */

      /* Generate random vector from 0 till 1 fucntion
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) random vector.
       */
      vec2<Type> Rnd1( VOID )
      {
        return Rnd0().Normalize() * 2 - 1;
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
        return &Y;
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

    }; /* End of 'vec2' class */

  } /* End of 'mth' namespace */

/* Obtional output vector to osstream function
 * ARGUMENTS: 
 *   - 
 */
template<typename Type>
std::ostream & operator<<( std::ostream &C, const mth::vec2<Type> &A )
{
  C << "<" << A[0] << ", " << A[1] << ">" << std::endl;
  return C;
} /* End of 'operator<<' function */

#endif /* __mth_vec2_h */

/* End of 'mth_vec2.h' file */

