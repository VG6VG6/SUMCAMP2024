/* FILE NAME: coml.h
 * PROGRAMMER: VG6
 * LAST UPDATE: 20.07.2024
 * PURPOSE: Complex math headers.
 */
#ifndef _CMPL_H
#define _CMPL_H

#include <cmath>
#include <time.h>

typedef double DBL;

struct Timer
{
  double SyncTime, FPS;
 
  Timer( void ) : FPS(300), SyncTime(0)
  {
  }

  void update( void )
  {
    long t;
    static long StartTime = -1, FPSTime, FrameCount;
 
    t = clock();
    if (StartTime == -1)
      StartTime = FPSTime = t;
    SyncTime = (t - StartTime) / (double)CLOCKS_PER_SEC;
    FrameCount++;
    if (t - FPSTime > 3 * CLOCKS_PER_SEC)
    {
      FPS = FrameCount / ((t - FPSTime) / (double)CLOCKS_PER_SEC);
      FPSTime = t;
      FrameCount = 0;
    }
  }
};

struct cmpl
{
  DBL Re, Im; // Complex unmber value

  /* Complex numbers constructor */
  cmpl( void ) : Re(0), Im(0)
  {
  }
  cmpl( DBL ReN ) : Re(ReN), Im(ReN)
  {
  }
  cmpl( DBL ReN, DBL ImN ) : Re(ReN), Im(ImN)
  {
  }
  cmpl( const cmpl &A ) : Re(A.Re), Im(A.Im)
  {
  }

    /* Obtain sum of two complex number function.
   * ARGUMENTS:
   *   - complex number to be add:
   *       const cmpl &Z;
   * RETURNS:
   *   (cmpl) result value.
   */
  cmpl operator+( const cmpl &Z ) const
  {
    return cmpl(Re + Z.Re, Im + Z.Im);
  } /* End of 'operator+' function */

  /* Obtain sum of complex number and real function.
   * ARGUMENTS:
   *   - number to be add:
   *       DBL X;
   * RETURNS:
   *   (cmpl) result value.
   */
  cmpl operator+( DBL X ) const
  {
    return cmpl(Re + X, Im);
  } /* End of 'operator+' function */

  /* Obtain multiplication of two complex number function.
   * ARGUMENTS:
   *   - complex number to be multiply:
   *       const cmpl &Z;
   * RETURNS:
   *   (cmpl) result value.
   */
  cmpl operator*( const cmpl &Z ) const
  {
    return cmpl(Re * Z.Re - Im * Z.Im, Re * Z.Im + Im * Z.Re);
  } /* End of 'operator*' function */

  /* Obtain multiplication of complex number by real function.
   * ARGUMENTS:
   *   - number to be multiply:
   *       DBL X;
   * RETURNS:
   *   (cmpl) result value.
   */
  cmpl operator*( DBL X ) const
  {
    return cmpl(Re * X, Im * X);
  } /* End of 'operator*' function */

  /* Obtain subtraction of two complex number function.
   * ARGUMENTS:
   *   - complex number to be subtrac:
   *       const cmpl &Z;
   * RETURNS:
   *   (cmpl) result value.
   */
  cmpl operator-( const cmpl &Z ) const
  {
    return cmpl(Re - Z.Re, Im - Z.Im);
  } /* End of 'operator-' function */

  /* Obtain division of two complex number function.
   * ARGUMENTS:
   *   - complex number to be divide by:
   *       const cmpl &Z;
   * RETURNS:
   *   (cmpl) result value.
   */
  cmpl operator/( const cmpl &Z ) const
  {
    DBL norm = !Z;
    return cmpl((Re * Z.Re + Im * Z.Im) / norm, (Im * Z.Re - Re * Z.Im) / norm);
  } /* End of 'operator/' function */

  /* Obtain power complex number function.
   * ARGUMENTS: 
   *   - Power:
   *       (INT) N;
   * RETURNS:
   *   (smpl) result value.
   */
  cmpl operator^( INT N ) const
  {
    cmpl Z(*this);

    for (int i = 1; i < N; i++)
      Z = Z * *this;
    return cmpl(Z);
  }

  /* Obtain squared complex number norma function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (DBL) result value.
   */
  DBL operator!( VOID ) const
  {
    return Re * Re + Im * Im;
  } /* End of 'operator*' function */

  /* Get Julia number by coords
   * ARGUMENTS:
   *   - constatnt link to pixel possition
   *       const cmpl &C;
   * RETURNS:
   *   (int) n
   */
  int Julia( const cmpl &C )
  {
    int n = 0;
    cmpl Z = cmpl(Re, Im);

    while(!Z < 4 && n < 255)
    {
      Z = Z * Z + C;
      n++;
    }
    return n;
  } /* End of 'Julia' function */

  /* Get Mondel number by coords
   * ARGUMENTS: None.
   * RETURNS:
   *   (int) n
   */
  int Mandel( void )
  {
    int n = 0;
    cmpl Z0 = cmpl(Re, Im);
    cmpl Z = cmpl(Re, Im);

    while(!Z < 4 && n < 255)
    {
      Z = Z * Z + Z0;
      n++;
    }
    return n;
  } /* End of 'Mondel' function */

  /* Get Newton number by coords
   * ARGUMENTS:
   *   - stepen:
   *       int N;
   *   - timer
   *       Timer Time;
   * RETURNS:
   *   (int) n
   */
  int NewtonStepen( int N, Timer Time )
  {
    int n = 0;
    cmpl Z = cmpl(Re, Im);

    while(!Z < 4 && n < 255)
    {
      Z = Z - ((Z ^ N) - cmpl(1, 0)) / ((Z ^ (N - 1)) * N) + (0.08 * sin(Time.SyncTime / 10));
      n++;
    }
    return n;
  } /* End of 'NewtonStepen' function */



  /* Get Newton sinus number by coords
   * ARGUMENTS:
   *   - timer
   *       Timer Time;
   * RETURNS:
   *   (int) n
   *
  int NewtonSin( Timer Time )
  {
    int n = 0;
    cmpl Z = cmpl(Re, Im);

    while(!Z < 4 && n < 255)
    {
      Z = Z - (sin(Z) / cos(Z));
      n++;
    }
    return n;
  } /* End of 'NewtonSin' function*/
};

double StartX1 = 2, StartX0 = -2, StartY1 = 2, StartY0 = -2;
double X1 = 2, X0 = -2, Y1 = 2, Y0 = -2;

struct Control
{
  int ZoomLevel = 0;
  Control( void )
  {}

  void Zoom( int Mz )
  {
    if (Mz < 0 && ZoomLevel <= 0)
      return;
    X1 = StartX1 / ZoomLevel;
    X0 = StartX0 / ZoomLevel;
    Y1 = StartY1 / ZoomLevel;
    Y0 = StartY0 / ZoomLevel;
  }
  void Move( int Mx, int My )
  {
    cmpl a(1, 2);
    a.Mandel();
  }
};

struct Julia
{
  double X1 = 1, X0 = -1, Y1 = 1, Y0 = -1;

  int operator()( int X, int Y, int W, int H, const Timer &Time, int foo )
  {
    return cmpl(X * (X1 - X0) / W + X0, Y * (Y1 - Y0) / H + Y0).Julia(cmpl(0.35 + 0.08 * sin(Time.SyncTime), 0.36 + 0.08 * sin(Time.SyncTime)));
  }
};

struct Mandel
{
  double X1 = 1, X0 = -1, Y1 = 1, Y0 = -1;

  int operator()( int X, int Y, int W, int H, const Timer Time, int foo )
  {
    return cmpl(X * (X1 - X0) / W + X0, Y * (Y1 - Y0) / H + Y0).Mandel();
  }
};

struct NewtonStepen
{
  int operator()( int X, int Y, int W, int H, Timer Time, int step )
  {
    return cmpl(X * (X1 - X0) / W + X0, Y * (Y1 - Y0) / H + Y0).NewtonStepen(step, Time);
  }
};

struct NewtonSin
{
  double X1 = 2, X0 = -2, Y1 = 2, Y0 = -2;

  int operator()( int X, int Y, int W, int H, Timer Time, int step )
  {
    return 0;//cmpl(X * (X1 - X0) / W + X0, Y * (Y1 - Y0) / H + Y0).NewtonSin(Time);
  }
};

#endif /* _CMPL_H */
/* End of 'coml.h' file */
