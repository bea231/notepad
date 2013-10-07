/* Sergeev Artemiy, 33602 (3057/2) */

#ifndef _TEXTVIEW_H_
#define _TEXTVIEW_H_

#include <stdio.h>
#include "win.h"
#include "viewbuf.h"

/* Project namespace */
namespace task2
{
  /* Window class definition */
  class textview : public win
  {
  private:
    viewbuf Buffer;
    int LinesInPage;
  public:
    /* Default class constructor */
    textview( int CmdShow = SW_SHOWNORMAL, char *CmdLine = NULL, HINSTANCE hInst = NULL, char *WindowName = "Task" );
    /* Class destructor */

    ~textview( void );

    /***
     * Virtual functions for window customization
     ***/

    /* Initialization function */
    virtual void Init( void );

    /* Deinitialization function */
    virtual void Close( void );

    /* Change window size handle function */
    virtual void Resize( void );

    /* Erase background handle function */
    virtual void Erase( HDC hDC );

    /* Paint window content function */
    virtual void Paint( HDC hDC );

    /* Activate handle function */
    virtual void Activate( BOOL IsActive );

    /* Timer handle function */
    virtual void Timer( void );

    /* Free CPU time handling function */
    virtual void Idle( void );

    /* Keyboard state function */
    virtual void Key( unsigned int vk, bool fDown );

    /* WM_MOUSEMOVE window message handle function */
     virtual void Mouse(int x, int y, unsigned int flags);
  }; /* End of 'win' class */
}

#endif /* _TEXTVIEW_H_ */
