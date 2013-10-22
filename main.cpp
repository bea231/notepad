/* Sergeev Artemiy, 33601/2 (3057/2) */

#include <windows.h>

#include "textview.h"


/* The main program function */
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    char *cmdLine, int cmdShow )
{
  if (hPrevInstance != NULL || cmdLine == NULL)
    return -1;

  notepad::textview mywin(cmdShow, cmdLine, hInstance, "Notepad");

  mywin.Run();
  return 0;
}
