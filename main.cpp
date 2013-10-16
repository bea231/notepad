/* Sergeev Artemiy, 33601/2 (3057/2) */

#include <windows.h>

#include "textview.h"


/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       char *CmdLine;
 *   - show window command parameter:
 *       int cmdShow;
 * RETURNS:
 *   (int) Error level for operation system (0 for success).
 */
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    char *cmdLine, int cmdShow )
{
  if (hPrevInstance != NULL || cmdLine == NULL)
    return -1;

  notepad::textview mywin(cmdShow, cmdLine, hInstance, "Notepad");
  
  mywin.Run();
  return 0;
} /* End of 'WinMain' function */

/* END OF 'WINAPI.CPP' FILE */