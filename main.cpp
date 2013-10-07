/* Sergeev Artemiy, 33602 (3057/2) */

#include "textview.h"

/* The main program function */
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    char *CmdLine, int CmdShow )
{
  if (hPrevInstance != NULL || CmdLine == NULL)
    return -1;

  task2::textview mywin(CmdShow, CmdLine);

  mywin.Run();
  return 0;
} /* End of 'WinMain' function */
