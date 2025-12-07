
/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : Animation project.
 *               Main application module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 04.08.2024.
 * NOTE        : None.
 */
#include "gogl.h"


/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT CmdShow )
{
  /* Create console */
  AllocConsole();
  SetConsoleTitle("gort console");
  HWND hCnsWnd = GetConsoleWindow();
  RECT rc;
  GetWindowRect(hCnsWnd, &rc);
  MoveWindow(hCnsWnd, 1500, 300, 600, 300, TRUE);
  std::freopen("CONOUT$", "w", stdout);
  system("@chcp 1251 > nul");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);

  gogl::anim *Anim = gogl::anim::Get();

  *Anim << "Unit Control" << "Unit Triangle" << "Unit Sky" << "Unit Grid";

  Anim->Run();

  return 30;
} /* End of 'WinMain' function */

/* End of 'main.cpp' file */