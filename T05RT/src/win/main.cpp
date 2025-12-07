/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : Raytracing project.
 *               Main module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 27.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
#include "gort.h"
#include <iostream>

#include "win/win.h"
#include "ray/rt.h"

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
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  struct mlLib
  {
    CHAR Name[100];
    gort::vec3 Ka, Kd, Ks;
    DBL Ph;
  };

  mlLib MtlLib[] =  {
    {"Black Plastic",   {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},               32},
    {"Brass",           {0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843}, 27.8974},
    {"Bronze",          {0.2125,0.1275,0.054},       {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},  25.6},
    {"Chrome",          {0.25, 0.25, 0.25},          {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597}, 76.8},
    {"Copper",          {0.19125,0.0735,0.0225},     {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},  12.8},
    {"Gold",            {0.24725,0.1995,0.0745},     {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},  51.2},
    {"Peweter",         {0.10588,0.058824,0.113725}, {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},      9.84615},
    {"Silver",          {0.19225,0.19225,0.19225},   {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},  51.2},
    {"Polished Silver", {0.23125,0.23125,0.23125}, {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},  89.6},
    {"Turquoise",       {0.1, 0.18725, 0.1745},      {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678}, 12.8},
    {"Ruby",            {0.1745, 0.01175, 0.01175},  {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959}, 76.8},
    {"Polished Gold",   {0.24725, 0.2245, 0.0645},   {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006}, 83.2},
    {"Polished Bronze", {0.25, 0.148, 0.06475},    {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621}, 76.8},
    {"Polished Copper", {0.2295, 0.08825, 0.0275}, {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2},
    {"Jade",            {0.135, 0.2225, 0.1575},     {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228}, 12.8},
    {"Obsidian",        {0.05375, 0.05, 0.06625},    {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435}, 38.4},
    {"Pearl",           {0.25, 0.20725, 0.20725},    {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648}, 11.264},
    {"Emerald",         {0.0215, 0.1745, 0.0215},    {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},       76.8},
    {"Black Plastic",   {0.0, 0.0, 0.0},             {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                32.0},
    {"Black Rubber",    {0.02, 0.02, 0.02},          {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                10.0},
  };
  INT MtlSize = sizeof(MtlLib) / sizeof(mlLib);
  AllocConsole();
  SetConsoleTitle("gort console");
  HWND hCnsWnd = GetConsoleWindow();
  RECT rc;
  GetWindowRect(hCnsWnd, &rc);
  MoveWindow(hCnsWnd, 1500, 300, 600, 300, TRUE);
  std::freopen("CONOUT$", "w", stdout);
  system("@chcp 1251 > nul");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);

  gort::rt_win Rt;
  gort::surface mtl;

  Rt.Create();
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xFC);
  std::cout << "Window Created!!!" << std::endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
  
  Rt.Scene.AmbientColor = gort::vec3(0.1);

#if 0
  //Rt.Scene << new gort::sphere(gort::vec3(0, 0.5, 0.5), 0.5, mtl);
  //Rt.Scene << new gort::lght::point(gort::vec3(5, 4, 1), 28, gort::vec3(0.9, 0.04, 0));
  Rt.Scene << new gort::lght::point(gort::vec3(0, 17, 27), 50, gort::vec3(0.1, 0.02, 0.7));
  
  //Rt.Scene << new gort::lght::point(gort::vec3::Rnd1() * 15 , rand() % 100, gort::vec3::Rnd1());
  INT RndBoxSIZE = 15;
  for (INT i = 0; i < 10; i++)
  {
    mtl.Ka = MtlLib[(50 + i) % MtlSize].Ka;
    mtl.Kd = MtlLib[(50 + i) % MtlSize].Kd;
    mtl.Ks = MtlLib[(50 + i) % MtlSize].Ks;
    mtl.Ph = MtlLib[(50 + i) % MtlSize].Ph;
    mtl.Kr = (rand() % 100 / 100.0);
    Rt.Scene << new gort::sphere(gort::vec3(i % 2 * 2, 1, i % 4 * 3), rand() % 500 / 100.0, mtl);
    gort::vec3 P = gort::vec3::Rnd1() * RndBoxSIZE + gort::vec3(0, RndBoxSIZE, 0);
    DBL size = rand() % 500 / 100.0;
    Rt.Scene << new gort::box(P - gort::vec3(size), P + gort::vec3(size), mtl);
  }

  
#endif
  
  mtl.Ka = {0.19225,0.19225,0.19225};
  mtl.Kd = {0.50754,0.50754,0.50754};
  mtl.Ks = {0.508273,0.508273,0.508273};
  mtl.Ph = 51.2;
  mtl.Kr = {0.1};
  mtl.Kt = {0};
  
  Rt.Scene << new gort::plane(gort::vec3(-1.5), gort::vec3(0, 1, 0), mtl);

  mtl.Ka = MtlLib[2].Ka;
  mtl.Kd = MtlLib[2].Kd;
  mtl.Ks = MtlLib[2].Ks;
  mtl.Ph = MtlLib[2].Ph;
  mtl.Kr = {0.10};
  mtl.Kt = {0.90};


  Rt.Scene << new gort::plane(gort::vec3(-35.5), gort::vec3(0, 0, -1), mtl);
  Rt.Scene << new gort::plane(gort::vec3(40.5), gort::vec3(0, -1, 0), mtl);
  Rt.Scene << new gort::plane(gort::vec3(35.5), gort::vec3(0, 1, 1), mtl);
  mtl.Ka = {0.24725, 0.2245, 0.0645};
  mtl.Kd = {0.34615, 0.3143, 0.0903};
  mtl.Ks = {0.797357, 0.723991, 0.208006};
  mtl.Ph = 80.2;
  mtl.Kr = {0.8};
  mtl.Kt = {0.2};

  // New scene
  mtl.Kr = {0.8};
  mtl.Kt = {0.018};

  for (INT i = 0; i < 50; i++)
  {
    mtl.Ka = MtlLib[(50 + i) % MtlSize].Ka;
    mtl.Kd = MtlLib[(50 + i) % MtlSize].Kd;
    mtl.Ks = MtlLib[(50 + i) % MtlSize].Ks;
    mtl.Ph = MtlLib[(50 + i) % MtlSize].Ph;
    mtl.Kr = {rand() % 100 / 100.0};
    mtl.Kt = {rand() % 100 / 100.0};
    gort::vec3 P = (gort::vec3::Rnd1() * gort::vec3(20, 15, 20)) + gort::vec3(0, 15, 0);
    gort::shape *B = new gort::sphere(P, rand() % 10 / 5.0, mtl);
    B->Media.Decay = 0;
    B->Media.RefractionCoef = 1 + rand() % 100 / 200.0;
    Rt.Scene << B;
    P = (gort::vec3::Rnd1() * gort::vec3(20, 15, 20)) + gort::vec3(0, 15, 0);
    B = new gort::box(P + rand() % 10 / 5.0, P - rand() % 10 / 5.0, mtl);
    B->Media.Decay = 0;
    B->Media.RefractionCoef = 1 + rand() % 100 / 200.0;
    Rt.Scene << B;
  }
  mtl.Ka = MtlLib[5].Ka;
  mtl.Kd = MtlLib[5].Kd;
  mtl.Ks = MtlLib[5].Ks;
  mtl.Ph = MtlLib[5].Ph;
  mtl.Kt = {0.0};
  mtl.Kr = {0.0};

  
  /*gort::g3dm *Cow = new gort::g3dm("bin/models/cow.g3dm", mtl);

  Rt.Scene << Cow;*/

  Rt.Cam.SetLocAtUp(gort::vec3(4, 15, 26), gort::vec3(0, 5, 0), gort::vec3(0, 1, 0));
  Rt.Cam.SetProj(0.1, 0.1, 500);


  Rt.Scene << new gort::lght::point(gort::vec3(3, 0, 0),   5, gort::vec3(1, 0, 0));
  Rt.Scene << new gort::lght::point(gort::vec3(15, 8, -15),  63, gort::vec3(0, 1, 0));
  Rt.Scene << new gort::lght::point(gort::vec3(-15, 3, 15),  107, gort::vec3(0, 0, 1));
  Rt.Scene << new gort::lght::point(gort::vec3(0, 10, 5),     120, gort::vec3(1, 1, 1));
  Rt.Scene << new gort::lght::direction(gort::vec3(0, -10, -4), gort::vec3(1, 1, 1));

  Rt.Run();
  return 0;
} /* End of 'WinMain' function*/

/* End of 'main.cpp' file */
