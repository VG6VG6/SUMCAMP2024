/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : anim.h
 * PURPOSE     : Animation project.
 *               Animation handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Vladislav A. Golubov (VG6).
 * LAST UPDATE : 1.08.2024.
 * NOTE        : None.
 *
 

 */

#ifndef __anim_h_
#define __anim_h_
#include "win/win.h"
#include "input/input.h"
#include "rnd/render.h"

/* Main application namespace */
namespace gogl
{
  class anim;

  /* Unit class */
  class unit
  {
  public:
    virtual ~unit( VOID )
    {
    }
    virtual VOID Render( anim *Ani ) = 0;
    virtual VOID Response( anim *Ani ) = 0;
  }; /* End of 'unit' class */

  /* Animation class */
  class anim : public win, public input, public render
  {
    private:
    /* Animation units stock */
    stock<unit *> Units;

    class scene : public unit
    {
      stock<unit *> Units;
    public:
      scene & operator<<( unit *Uni )
      {
        Units << Uni;
        return *this;
      }
    };

    scene *Scene;
    anim & operator<<( unit *Uni )
    {
      /*
      scene *s = dynamic_cast<scene *>(Scene);
      if (s != nullptr)
        *s << Uni;
      */
      Units << Uni;
      return *this;
    }


    /* Class constructor */
    anim( HINSTANCE hInst = GetModuleHandle(nullptr) ) : win(hInst), input(win::hWnd), render(win::hWnd)
    {
      GetCurrentDirectory(sizeof(Path), Path);
    } /* End of 'anim' function */

    /* Class destructor */
    ~anim( VOID )
    {
      /* Delete all system units */
      Units.Walk([]( unit *Uni )
      {
        delete Uni;
      });
    } /* End of '~anim' function */

  public:
    CHAR Path[_MAX_PATH];
    /* Add new unit function.
     * ARGUMENTS:
     *   - unit to add:
     *       unit &NewUnit;
     * RETURN:
     *   (anim &) reference to 
    */
    anim & operator<<( unit &NewUnit )
    {
      Units << &NewUnit;
    } /* End of 'operator<<' function */

    /* Obtain animation system instance reference function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (anim &) pointer to instance.
     */
    static anim & GetRef( VOID )
    {
      static anim Instance;

      return Instance;
    } /* End of 'GetRef' function */

    /* Obtain animation system instance pointer function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (anim *) pointer to instance.
     */
    static anim * Get( VOID )
    {
      return &GetRef();
    } /* End of 'Get' function */

    std::map<std::string, unit * (*)( VOID )> UnitNames;
    template<typename unit_type>
      class unit_register
      {
      private:
        static unit * Create( VOID )
        {
          return new unit_type();
        }
      public:
        unit_register( const std::string &UnitName )
        {
          GetRef().UnitNames[UnitName] = Create;
        }
      }; /* End of 'unit_register' class */

    anim & operator<<( const std::string &UnitName )
    {
      if (UnitNames.find(UnitName) != UnitNames.end())
        *this << UnitNames[UnitName]();
      return *this;
    }

    VOID Run( VOID ) override;

    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS );

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID );

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H );

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    VOID OnPaint( HDC hDC, PAINTSTRUCT *PS );

    /* WM_ACTIVATE window message handle function.
     * ARGUMENTS:
     *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
     *       UINT Reason;
     *   - handle of active window:
     *       HWND hWndActDeact;
     *   - minimized flag:
     *       BOOL IsMinimized;
     * RETURNS: None.
     */
    VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id );

    /* WM_MOUSEWHEEL window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse wheel relative delta value:
     *       INT Z;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );

    /* WM_RBUTTONDOWN and WM_LBUTTONDOWN window message handle function.
    * ARGUMENTS:
    *   - is click was double
    *       BOOL IsDoubleClick;
    *   - mouse position:
    *       INT X, Y;
    *   - mouse keys:
    *       UINT Keys;
    * REURNS: None.
    */
    VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );

    /* WM_RBUTTONUP and WM_LBUTTONUP window message handle function.
    * ARGUMENTS:
    *   - mouse position:
    *       INT X, Y;
    *   - mouse keys:
    *       UINT Keys;
    * REURNS: None.
    */
    VOID OnButtonUp( INT X, INT Y, UINT Keys );

    /* WM_MOUSEMOVE window message handle function.
    * ARGUMENTS: 
    *   - mouse position:
    *       INT X, Y;
    *   - mouse keys:
    *       UINT Keys;
    * RETURNS: None.
    */
    VOID OnMouseMove( INT X, INT Y, UINT Keys );

    /* Render scene function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render( VOID );

    /* WM_EXITSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnExitSizeMove( VOID );

    /* WM_ENTERSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnEnterSizeMove( VOID );

    /* Copy frame to screen.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CopyFrame( VOID );
  }; /* End of 'anim' class */

} /* End of 'gogl' namespace */

#endif // __anim_h_

/* End of 'anim.h' file */
