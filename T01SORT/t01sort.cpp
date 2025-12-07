/* FILE NAME: t01sort.cpp
 * PROGRAMMER: VG6
 * LAST UPDATE: 18.07.2024
 * PURPOSE: Array sorter.
 */
#include <iostream>
#include <fstream>
#include <string>

/* Calculate array elements count function.
 * ARGUMENTS:
 *   - file name:
 *       std::string s;
 * RETURNS:
 *   (INT) Count of array elements.
 */
int GetArrCount( std::string s )
{
  std::fstream f;
  int ans = 0;

  f.open(s, std::fstream::in);

  while (!f.eof())
  {
    f >> s;
    if (s == " ")
      continue;
    ans++;
  }
  f.close();
  return ans - 1;
} /* End of 'GetArrCount' function */

/* Calculate array elements count function.
 * ARGUMENTS:
 *   - poineter to first array element:
 *       int *arr;
 *   - count of array elements:
 *       int N;
 *   - file name:
 *       std::string s;
 * RETURNS: None.
 */
void AddArr( float *arr, int N, std::string s )
{
  std::fstream f;
  float value;

  f.open(s, std::fstream::in);
  for (int i = 0; i < N; i++)
  {
    f >> value;
    arr[i] = value;
  }
  f.close();
}/* End of 'AddArr' function */

/* Display array function.
 * ARGUMENTS:
 *   - poineter to first array element:
 *       int *arr;
 *   - count of array elements:
 *       int N;
 * RETURNS: None.
 */
void Display( float *arr, int N )
{
  for (int i = 0; i < N; i++)
    std::cout << arr[i] << " ";
  std::cout << std::endl;
} /* End of 'Display' function */

template<typename Type>
/* Swap 2 numbers function.
 * ARGUMENTS:
 *   - links to 2 numbers:
 *       Type &A, &B;
 * RETURNS: none.
 */
void Swap(Type &A, Type &B)
{
  Type tmp = A;
  A = B;
  B = tmp;
} /* End of 'Swap' function */

template<typename Type>
/* Array quick sort function.
 *   - poineter to first array element:
 *       Type arr;
 *   - count of array elements:
 *       int N;
 * RETURNS: None.
 */
void Sort( Type *arr, int N )
{
  Type x = arr[N / 2];
  int b = 0, e = N - 1;

  if (N < 2)
    return;

  while (b <= e)
  {
    while (arr[b] < x)
      b++;
    while (arr[e] > x)
      e--;

    if (b <= e)
    {
      if (b != e)
        Swap(arr[b], arr[e]);
      b++;
      e--;
    }
  }

  Sort(arr, e + 1);
  Sort(arr + b,  N - b);
} /* End of 'Sort' functioun */

/* Main programm function
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) Finish program code.
 */
int main( void )
{
  std::string s;
  int count;
  float *Arr;

  /* Read file name */
  std::cout << "Enter file name: ";
  std::cin >> s;

  if ((count = GetArrCount(s)) == -1)
    return 0;
  
  Arr = new float[count];
  AddArr(Arr, count, s);
  Display(Arr, count);

  Sort(Arr, count);
  Display(Arr, count);

  delete[] Arr;
} /* End of 'main' function */

/* End of 't01sort.cpp' file */