/* Sergeev Artemiy, 33602 (3057/2) */

#ifndef _WIN_H_
#define _WIN_H_

#include <windows.h>

/* Project namespace */
namespace task2
{
  /* Window class name */
  const CHAR MainWndClassName[] = "DefaultClassName";

  /* Window class definition */
  class win
  {
  private:
    /*** Initialization paramentres ***/
    static const int InitializationTimerId = 11111; // Initialization timer identifier
    BOOL IsInit;                                    // Initialization flag
  protected:
    /*** Window data ***/

    /* Window parametres */
    HWND hWnd;                                      // Window handle
    int  Width, Height;                             // Width and height of window
    BOOL IsActive;                                  // Activity flag

    char *CmdLine;
    int CmdShow;
  private:
    /* Full screen parametres */
    RECT SaveRC;                                    // Full screen save parametres
  protected:
    BOOL IsFullScreen;                              // Full screen flag

    /* Application parametres */
    HINSTANCE hInstance;                            // Application instance handle
  public:
    /* Default class constructor */
    win( int CmdShow = SW_SHOWNORMAL, char *CmdLine = NULL, HINSTANCE hInst = NULL, char *WindowName = "Task" );

    /* Default class destructor */
    ~win( void );

    /* Window message handle function (CALLBACK version) */
    static LRESULT CALLBACK WinFuncCallBack( HWND hWnd, unsigned int Msg, WPARAM wParam, LPARAM lParam );

    /* Window handle message (with crack message calls) */
    LRESULT WinFunc( unsigned int Msg, WPARAM wParam, LPARAM lParam );

    /* Windowed application running function */
    int Run( void );

    /* System exit function */
    void DoExit( void );

    /* Set full screen application mode */
    void SetFullScreen( BOOL IsFull );

    /***
     * Message cracked handle
     ***/

    /* WM_CREATE window message handle function */
    BOOL OnCreate( CREATESTRUCT *CS );

    /* WM_CLOSE window message handle function */
    void OnClose( void );

    /* WM_SIZE window message handle function */
    void OnSize( unsigned int State, int W, int H );

    /* WM_ERASEBKGND window message handle function */
    BOOL OnEraseBkgnd( HDC hDC );

    /* WM_PAINT window message handle function */
    void OnPaint( void );

    /* WM_ACTIVATE window message handle function */
    void OnActivate( unsigned int Reason, HWND hWndActDeact, BOOL IsMinimized );

    /* WM_TIMER window message handle function */
    void OnTimer( int Id );

    /* WM_KEYDOWN window message handle function */
    void OnKey(unsigned int vk, bool fDown, int cRepeat, unsigned int flags);

    /* WM_MOUSEMOVE window message handle function */
    void OnMouseMove(int x, int y, unsigned int flags);

    /***
     * Virtual functions for window customization
     ***/

    /* Initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual void Init( void )
    {
    } /* End of 'Init' function */

    /* Deinitialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual void Close( void )
    {
    } /* End of 'Close' function */

    /* Change window size handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual void Resize( void )
    {
    } /* End of 'Resize' function */

    /* Erase background handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual void Erase( HDC hDC )
    {
      HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
      HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(WHITE_BRUSH));

      /* Default action - draw white rectangle */
      Rectangle(hDC, 0, 0, Width, Height);
      SelectObject(hDC, hOldPen);
      SelectObject(hDC, hOldBrush);
    } /* End of 'Erase' function */

    /* Paint window content function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS: None.
     */
    virtual void Paint( HDC hDC )
    {
    } /* End of 'Paint' function */

    /* Activate handle function.
     * ARGUMENTS:
     *   - activation window flag:
     *       BOOL IsActive;
     * RETURNS: None.
     */
    virtual void Activate( BOOL IsActive )
    {
    } /* End of 'Activate' function */

    /* Timer handle function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual void Timer( void )
    {
    } /* End of 'Timer' function */

    /* Free CPU time handling function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual void Idle( void )
    {
    } /* End of 'Idle' function */

    /* Keyboard state function.
     * ARGUMENTS:
     *   - virtual key identifier:
     *       unsigned int vk;
     *   - down flag:
     *       bool fDown;
     * RETURNS: None.
     */
    virtual void Key( unsigned int vk, bool fDown )
    {
    } /* End of 'Key' function */

    /* WM_MOUSEMOVE window message handle function.
     * ARGUMENTS:
     *   - new mouse coordinate:
     *       int x, y;
     *   - state mouse flags:
     *       unsigned int flags;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
     virtual void Mouse(int x, int y, unsigned int flags)
     {
     } /* End of 'Mouse' function */
  }; /* End of 'win' class */
}

#endif /* _WIN_H_ */
