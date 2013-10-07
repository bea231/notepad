/* Sergeev Artemiy, 33601/2 (3057/2) */

#include <string>
#include <stdio.h>
#include "textview.h"

/* Default class constructor */
task2::textview::textview( int CmdShow, char *CmdLine, HINSTANCE hInst, char *WindowName ) : LinesInPage(0)
{
  this->CmdShow = CmdShow;
  this->CmdLine = CmdLine;

  if (strlen(CmdLine) > 0 )
  {
    char TextFileName[MAX_PATH];

    sscanf(CmdLine, "%s", TextFileName);
    Buffer.Init(TextFileName);
  }
  else
    Buffer.Init(NULL);
}

/* Class destructor */
task2::textview::~textview( void )
{
}

/* Initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void task2::textview::Init( void )
{
}

/* Deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void task2::textview::Close( void )
{
}

/* Change window size handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void task2::textview::Resize( void )
{
  TEXTMETRIC text_metric;
  HDC hDC;

  hDC = GetDC(hWnd);
  GetTextMetrics(hDC, &text_metric);
  LinesInPage = Height / text_metric.tmHeight + 1;
  ReleaseDC(hWnd, hDC);
}

/* Erase background handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
void task2::textview::Erase( HDC hDC )
{
  HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
  HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(WHITE_BRUSH));

  /* Default action - draw white rectangle */
  Rectangle(hDC, 0, 0, Width + 1, Height + 1);
  SelectObject(hDC, hOldPen);
  SelectObject(hDC, hOldBrush);
}

/* Paint window content function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS: None.
 */
void task2::textview::Paint( HDC hDC )
{
  TEXTMETRIC text_metric;
  int cur_y = 0;
  char *ptr, *ptr2;

  GetTextMetrics(hDC, &text_metric);

  ptr = Buffer.GetFirstBeginPtr();
  ptr2 = Buffer.GetEndPtr();

  for (cur_y = 0; cur_y < Height + text_metric.tmHeight && Buffer.HaveStrings(); cur_y += text_metric.tmHeight)
  {
    TextOut(hDC, 0, cur_y, ptr, ptr2 - ptr + 1);
    ptr = Buffer.GetBeginPtr();
    ptr2 = Buffer.GetEndPtr();
  }
}

/* Activate handle function.
 * ARGUMENTS:
 *   - activation window flag:
 *       BOOL IsActive;
 * RETURNS: None.
 */
void task2::textview::Activate( BOOL IsActive )
{
}

/* Timer handle function
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void task2::textview::Timer( void )
{
}

/* Free CPU time handling function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void task2::textview::Idle( void )
{
}

/* Keyboard state function.
 * ARGUMENTS:
 *   - virtual key identifier:
 *       unsigned int vk;
 * RETURNS: None.
 */
void task2::textview::Key( unsigned int vk, bool fDown )
{
  if (fDown)
  {
    switch (vk)
    {
    case VK_LEFT:
      Buffer.ShiftX(-1);
      break;
    case VK_RIGHT:
      Buffer.ShiftX(1);
      break;
    case VK_DOWN:
      Buffer.ShiftY(1);
      break;
    case VK_UP:
      Buffer.ShiftY(-1);
      break;
    case VK_NEXT:
      Buffer.ShiftY(LinesInPage - 1);
      break;
    case VK_PRIOR:
      Buffer.ShiftY(-LinesInPage + 1);
      break;
    }
  }
  InvalidateRect(hWnd, NULL, TRUE);
}

/* WM_MOUSEMOVE window message handle function.
 * ARGUMENTS:
 *   - new mouse coordinate:
 *       int x, y;
 *   - state mouse flags:
 *       unsigned int flags;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
 void task2::textview::Mouse(int x, int y, unsigned int flags)
 {
 }