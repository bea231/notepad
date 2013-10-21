/* Sergeev Artemiy, 33601/2 (3057/2) */

#ifndef _TEXTVIEW_H_
#define _TEXTVIEW_H_

#include "viewbuf.h"
#include "win.h"

/* Project namespace */
namespace notepad
{
  class textview : public win
  {
  private:
    viewbuf buffer;
    unsigned int textHeight, textWidth,
                 stringsInPage, charsInPage,
                 scrollX, scrollY;
  public:
    /* Default class constructor */
    textview( int cmdShow = SW_SHOWNORMAL, char *cmdLine = NULL, HINSTANCE hInst = NULL, char *windowName = "Task" );

    /* Class destructor */
    ~textview( void );

    /* Shift window by X-axis */
    void ShiftX( int shift );

    /* Shift window by Y-axis */
    void ShiftY( int shift );

    /* Set new position, hide or show scrollbar function */
    void UpdateScrollBar( void );

    /***
     * Virtual functions for window customization
     ***/

    /* Initialization function */
    virtual void Init( void );

    /* Deinitialization function */
    virtual void Close( void );

    /* Change window size handle function */
    virtual void Resize( void );

    /* Paint window content function */
    virtual void Paint( void );

    /* Erase background handle function */
    virtual void Erase( void );

    /* Keyboard state handle function */
    virtual void Key(unsigned int vk, bool fDown, int cRepeat, unsigned int flags);

    /* WM_MOUSEWHEEL window message handle function */
    virtual void MouseWheel(int xPos, int yPos, int zDelta, unsigned int fwKeys);

    /* WM_COMMAND window message handle function */
    virtual void Command(int id, HWND hwndCtl, unsigned int codeNotify);

    /* WM_HSCROLL window message handle function */
    virtual void HScroll(HWND hwndCtl, unsigned int code, int pos);

    /* WM_VSCROLL window message handle function */
    virtual void VScroll(HWND hwndCtl, unsigned int code, int pos);
  };
}

#endif /* _TEXTVIEW_H_ */