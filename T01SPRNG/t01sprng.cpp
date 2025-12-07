/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : t01sprng.cpp
 * PURPOSE     : Spring project.
 *               Main startup module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov.
 * LAST UPDATE : 21.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <commondf.h>
#include <iostream>

/* Main sturtup function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT main( VOID )
{
  int N, Counter = 1, Y = 0, X = 0;
  int t = 0, b = 0, l = 0, r = 0;

  std::cout << "Enter size: ";
  std::cin >> N;

  int **Arr = new int*[N];
  *Arr = new int[N];

  while (N > Counter)
  {
    int i;

    /* Top */
    for (i = X; i < N - (r + l); i++)
      Arr[Y][i] = Counter++;
    Y = i;
    t++;
    /* Right */
    for (i = Y; i < N - (t + b); i++)
      Arr[i][X] = Counter++;
    X = i;
    r++;
    /* Bottom */
    for (i = X; i < N - (r + l); i++)
      Arr[Y][i] = Counter++;
    Y = i;
    b++;
    /* Left */
    for (i = Y; i < N - (t + b); i++)
      Arr[i][X] = Counter++;
    l++;
    X = i;
  }
  for (int y = 0; y < N; y++)
  {
    for (int x = 0; x < N; x++)
      std::cout << Arr[y][x] << " ";
    std::cout << std::endl;
  }

  return 0;
} /* End of 'main' function */

/* END OF 't01sprng.cpp' FILE */