/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : unit_control.cpp
 * PURPOSE     : Animation project.
 *               Animation module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 4.08.2024.
 * NOTE        : None.
 *
 

 */
#include "gogl.h"

class unit_control : public gogl::unit
{
  FLT Speed, AngleSpeed;
public:
  /* Unit constructor */
    unit_control( VOID )
    {
      Speed = 10;
      AngleSpeed = 1;
    } /* End of unit constructor */
    /* Unit destructor */
    ~unit_control( VOID )
    {
    } /* End of unit destructor */
    VOID Render( gogl::anim *Ani ) override
    {
    } /* End of 'Render' function */
    VOID Response( gogl::anim *Ani ) override
    {
      FLT Dist, sinT, cosT, sinP, cosP, plen, Azimuth, Elevator;
  
      Dist = !(Ani->Cam.At - Ani->Cam.Loc);

      cosT = (Ani->Cam.Loc.Y - Ani->Cam.At.Y) / Dist;
      sinT = sqrt(1 - cosT * cosT);

      plen = Dist * sinT;
      cosP = (Ani->Cam.Loc.Z - Ani->Cam.At.Z) / plen;
      sinP = (Ani->Cam.Loc.X - Ani->Cam.At.X) / plen;

      Azimuth = R2D(atan2(sinP, cosP));
      Elevator = R2D(atan2(sinT, cosT));

      Azimuth += 
        (-0.5 * Ani->Keys[VK_LBUTTON] * Ani->Mdx +
          47 * Ani->GlobalDeltaTime *(Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT])) * (1 + Ani->Keys[VK_LSHIFT] * 2);

      Elevator -= 
        (0.5 * Ani->Keys[VK_LBUTTON] * Ani->Mdy +
          47 * Ani->GlobalDeltaTime * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]))  * (1 + Ani->Keys[VK_LSHIFT] * 2);
  
      Dist += Ani->GlobalDeltaTime *
        (1 * Ani->Mdz + 8 * (1 + Ani->Keys[VK_SHIFT] * 29) *
            (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]))  * (1 + Ani->Keys[VK_LSHIFT] * 2);

      if (Elevator > 178.0)
        Elevator = 178.0;
      if (Elevator < 0.08)
        Elevator = 0.08;

      if (Dist < 0.001)
        Dist = 0.001;

      if (Ani->Keys[VK_RBUTTON])
      {
        FLT Wp, Hp, sx, sy;
        gogl::vec3 dv;

        Wp = Ani->Cam.Wp;
        Hp = Ani->Cam.Hp;

        sx = Ani->Keys[VK_RBUTTON] * -Ani->Mdx * Wp / Ani->W * Dist / Ani->Cam.ProjDist;
        sy = Ani->Keys[VK_RBUTTON] * Ani->Mdy * Hp / Ani->H * Dist / Ani->Cam.ProjDist;

        dv = Ani->Cam.Right * sx + Ani->Cam.Up * sy;
        Ani->Cam.At += dv;
        Ani->Cam.Loc += dv;
      }
  
      Ani->Cam.SetLocAtUp((gogl::matr::RotateX(Elevator) * gogl::matr::RotateY(Azimuth) * gogl::matr::Translate(Ani->Cam.At)).PointTransform(gogl::vec3(0, Dist, 0)),
                          Ani->Cam.At,
                          gogl::vec3(0, 1, 0));
      
      if (Ani->KeysClick['P'])
        Ani->IsPause = !Ani->IsPause;
      if (Ani->KeysClick[VK_F11])
        Ani->FlipFullScreen();
      if (Ani->KeysClick['F'])
        Ani->Cam.SetLocAtUp(gogl::vec3(0, 14, 70), gogl::vec3(0, 0, 0), gogl::vec3(0, 1, 0));
      if (Ani->KeysClick['W'])
      {
        INT modes[2];

        glGetIntegerv(GL_POLYGON_MODE, modes);
        if (modes[0] == GL_LINE)
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        else
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      }
    } /* End of 'Response' function */
};

static gogl::anim::unit_register<unit_control> _("Unit Control");

/* End of 'unit_control.cpp' */