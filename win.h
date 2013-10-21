/* Sergeev Artemiy, 33601/2 (3057/2) */

#ifndef _WIN_H_
#define _WIN_H_

#define _WIN32_WINNT_ 0x0500
#include <windows.h>

/* Project namespace */
namespace notepad
{
  /* Window class name */
  const char c_MainWndClassName[] = "DefaultClassName";

  /* Main window class */
  class win
  {
  private:
    /* Initialization timer identifier */
    static const int c_initializationTimer = 11011;

    /* Initialization flag */
    bool isInit;

    RECT saveRC;

  protected:
    /* Window data */
    HWND hWnd;           // Window handle
    HINSTANCE hInstance; // Application instance handle
    int width, height;   // Window size
    bool isActive;       // Active flag
    bool isFullScreen;   // Full screen flag

    HDC hDC;
    HBITMAP hBm;
  public:
    /* Class constructor */
    win( HINSTANCE hInst = NULL, int cmdShow = SW_SHOWNORMAL );

    /* Class destructor */
    ~win( void );

    /* Window message handle function (CALLBACK version) */
    static LRESULT CALLBACK WinFuncCallBack( HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam );

    /* Window handle message (with crack message calls) */
    LRESULT WinFunc( unsigned int msg, WPARAM wParam, LPARAM lParam );

    /* Windowed application running function */
    int Run( void );

    /* System exit function */
    void DoExit( void );

    /* Set full screen application mode */
    void SetFullScreen( bool isFull );

    int GetWidth( void ) const {return width;}

    int GetHeight( void ) const {return height;}

    /***
     * Message cracked handle
     ***/

    /* WM_CREATE window message handle function */
    bool OnCreate( HWND hWnd, CREATESTRUCT *createStruct );

    /* WM_CLOSE window message handle function */
    void OnClose( void );

    /* WM_SIZE window message handle function */
    void OnSize( unsigned int state, int newWidth, int newHeight );

    /* WM_ERASEBKGND window message handle function */
    bool OnEraseBkgnd( HDC hDC );

    /* WM_PAINT window message handle function */
    void OnPaint( void );

    /* WM_ACTIVATE window message handle function */
    void OnActivate( unsigned int reason, HWND hWndActDeact, bool isMinimized );

    /* WM_TIMER window message handle function */
    void OnTimer( int id );

    /* WM_GETMINMAXINFO window message handle function */
    void OnGetMinMax( MINMAXINFO *MinMaxInfo );

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
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual void Erase( void )
    {
    } /* End of 'Erase' function */

    /* Paint window content function */
    virtual void Paint( void )
    {
    }

    /* Activate handle function. */
    virtual void Activate( bool isActive )
    {
    }
    
    /* Timer handle function */
    virtual void Timer( int Id )
    {
    }

    /* Free CPU time handling function. */
    virtual void Idle( void )
    {
    }

    /* Keyboard state function */
    virtual void Key(unsigned int vk, bool fDown, int cRepeat, unsigned int flags)
    {
    }

    /* WM_MOUSEMOVE window message handle function */
    virtual void MouseMove(int x, int y, unsigned int flags)
    {
    }

    /* WM_MOUSEWHEEL window message handle function */
    virtual void MouseWheel(int xPos, int yPos, int zDelta, unsigned int fwKeys)
    {
    }

    /* WM_HSCROLL window message handle function */
    virtual void HScroll(HWND hwndCtl, unsigned int code, int pos)
    {
    }

    /* WM_VSCROLL window message handle function */
    virtual void VScroll(HWND hwndCtl, unsigned int code, int pos)
    {
    }

    /* WM_COMMAND window message handle function */
    virtual void Command(int id, HWND hwndCtl, unsigned int codeNotify)
    {
    }
  }; /* End of 'win' class */
} /* End of 'notepad' namespace */

#endif /* _WIN_H_ */
