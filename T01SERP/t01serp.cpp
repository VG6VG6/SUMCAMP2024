/* FILE NAME: t01serp.cpp
 * PROGRAMMER: VG6
 * LAST UPDATE: 18.07.2024
 * PURPOSE: Add numbers in square serpantine.
 */

#include <iostream>
#include <fstream>

/* Main programm function
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) Finish program code.
 */
int main( void )
{
  int N;

  /* Read file name */
  std::cout << "N: ";
  std::cin >> N;

  int maxSpace = (int)std::log10(N * N);

  for (int y = 0; y < N; y++)
  {
    for (int x = 0; x < N; x++)
    {
      int num;

      if (y % 2 == 0)
        num = y * N + x;
      else
        num = (y + 1) * N - x - 1;
      if (num != 0)
      {
        for (int i = 0; i < maxSpace - std::log10(num); i++)
          std::cout << " ";
        std::cout << num << " ";
      }
      else
      {
        for (int i = 0; i < maxSpace; i++)
          std::cout << " ";
        std::cout << num << " ";
      }
    }
    std::cout << std::endl;
  }
} /* End of 'main' function */

/* End of 't01serp.cpp' file */
