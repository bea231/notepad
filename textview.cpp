/* Sergeev Artemiy, 33601/2 (3057/2) */

#include <string>
#include <stdio.h>
#include "textview.h"
#include "resource.h"

/* Default class constructor */
notepad::textview::textview( int cmdShow, char *cmdLine, HINSTANCE hInst, char *windowName ) : scrollX(0), scrollY(0)
{
  if (strlen(cmdLine) > 0 )
  {
    char textFileName[MAX_PATH];

    sscanf(cmdLine, "%s", textFileName);
    buffer.Open((unsigned char *)textFileName);
  }
}

/* Class destructor */
notepad::textview::~textview( void )
{
}

/* Initialization function */
void notepad::textview::Init( void )
{
  TEXTMETRIC textMetric;

  GetTextMetrics(hDC, &textMetric);
  textHeight = textMetric.tmHeight;
  textWidth = textMetric.tmMaxCharWidth;
  SetMenu(hWnd, LoadMenu(hInstance, (char *)TEXT(IDR_MENU)));
}

/* Deinitialization function */
void notepad::textview::Close( void )
{
}

/* Change window size handle function */
void notepad::textview::Resize( void )
{
  stringsInPage = height / textHeight;
  charsInPage = width / textWidth;

  UpdateScrollBar();
}

/* Erase background handle function */
void notepad::textview::Erase( void )
{
}

/* Paint window content function */
void notepad::textview::Paint( void )
{
  unsigned char *ptr1, *ptr2;
  unsigned int currentY;

  ptr1 = buffer.Begin();
  ptr2 = buffer.End();
  for (currentY = 0; (currentY < height + textHeight) && buffer.HaveStrings(); currentY += textHeight)
  {
    TextOut(hDC, 0, currentY, (char *)ptr1, ptr2 - ptr1);
    ptr1 = buffer.Next();
    ptr2 = buffer.End();
  }

}

/* Keyboard state handle function */
void notepad::textview::Key(unsigned int vk, bool fDown, int cRepeat, unsigned int flags)
{
  if (fDown)
  {
    switch (vk)
    {
    case VK_LEFT:
      buffer.ShiftX(-1);    // shift left 
      break;
    case VK_RIGHT:
      buffer.ShiftX(1);     // shift right
      break;
    case VK_DOWN:
      buffer.ShiftY(1);     // shift down
      break;
    case VK_UP:
      buffer.ShiftY(-1);    // shift up
      break;
    case VK_NEXT:
      buffer.ShiftY(stringsInPage);  // shift page down
      break;
    case VK_PRIOR:
      buffer.ShiftY(-(long)stringsInPage); // shift page up
      break;
    }
  }
  UpdateScrollBar();
  InvalidateRect(hWnd, NULL, FALSE);
}

/* WM_COMMAND window message handle function */
void notepad::textview::Command(int id, HWND hwndCtl, UINT codeNotify)
 {
   OPENFILENAME ofn = {0};
   unsigned char fileName[MAX_PATH] = {0};

   switch(id)
   {
   case ID_FILE_EXIT:
     SendMessage(hWnd, WM_DESTROY, 0, 0);
     break;
   case ID_MYFILE_OPEN:
     ofn.lStructSize = sizeof(OPENFILENAME);
     ofn.hwndOwner = hWnd;
     ofn.lpstrFile = (char *)fileName;
     ofn.nMaxFile = MAX_PATH;
     ofn.lpstrFilter = "All\0*.*\0Text files\0*.txt\0";
     ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

     if (GetOpenFileName(&ofn) == TRUE)
     {
       buffer.Close();
       buffer.Open(fileName);
     }
     UpdateScrollBar();
     break;
   case ID_FILE_ABOUT:
     MessageBox(hWnd, "Sergeev Artemiy\n"
                      "       33601/2", "About", MB_OK | MB_ICONINFORMATION);
     break;
   }
   InvalidateRect(hWnd, NULL, FALSE);
 }

/* WM_HSCROLL window message handle function */
void notepad::textview::HScroll(HWND hwndCtl, UINT code, int pos)
{
  SCROLLINFO scrollInfo;

  scrollInfo.cbSize = sizeof(SCROLLINFO);
  switch (code)
  {
  case SB_PAGELEFT:
    buffer.ShiftX(-(long)charsInPage);
    break;
  case SB_PAGERIGHT:
    buffer.ShiftX(charsInPage);
    break;
  case SB_THUMBTRACK:
    scrollInfo.fMask = SIF_POS;
    GetScrollInfo(hWnd, SB_HORZ, &scrollInfo);
    buffer.ShiftX(pos - scrollInfo.nPos);
    break;
  case SB_LINERIGHT:
    buffer.ShiftX(1);
    break;
  case SB_LINELEFT:
    buffer.ShiftX(-1);
    break;
  }
  InvalidateRect(hWnd, NULL, FALSE);
  UpdateScrollBar();
}

/* WM_VSCROLL window message handle function */
void notepad::textview::VScroll(HWND hwndCtl, UINT code, int pos)
{
  SCROLLINFO scrollInfo;

  scrollInfo.cbSize = sizeof(SCROLLINFO);
  switch (code)
  {
  case SB_PAGEUP:
    buffer.ShiftY(-(long)stringsInPage);
    break;
  case SB_PAGEDOWN:
    buffer.ShiftY(stringsInPage);
    break;
  case SB_THUMBTRACK:
    scrollInfo.fMask = SIF_POS;
    GetScrollInfo(hWnd, SB_VERT, &scrollInfo);
    buffer.ShiftY(pos - scrollInfo.nPos);
    break;
  case SB_LINEDOWN:
    buffer.ShiftY(1);
    break;
  case SB_LINEUP:
    buffer.ShiftY(-1);
    break;
  }
  InvalidateRect(hWnd, NULL, FALSE);
  UpdateScrollBar();
}
/* Set new position, hide or show scrollbar function */
void notepad::textview::UpdateScrollBar( void )
{
  SCROLLINFO scrollInfo;

  if (stringsInPage < buffer.GetStringsCount())
  {
    ShowScrollBar(hWnd, SB_VERT, TRUE);

    scrollInfo.cbSize = sizeof(SCROLLINFO);
    scrollInfo.fMask = SIF_PAGE | SIF_RANGE;
    scrollInfo.nMin = 0;
    scrollInfo.nMax = buffer.GetStringsCount() + stringsInPage - 3;
    scrollInfo.nPage = stringsInPage;
    SetScrollInfo(hWnd, SB_VERT, &scrollInfo, TRUE);

    SetScrollPos(hWnd, SB_VERT, buffer.GetCurrentString(), TRUE);
  }
  else
    ShowScrollBar(hWnd, SB_VERT, FALSE);

  if (charsInPage < buffer.GetMaxStringLength())
  {
    ShowScrollBar(hWnd, SB_HORZ, TRUE);

    scrollInfo.nMin = 0;
    scrollInfo.nMax = buffer.GetMaxStringLength() + charsInPage - 3;
    scrollInfo.nPage = charsInPage;
    SetScrollInfo(hWnd, SB_HORZ, &scrollInfo, TRUE);

    SetScrollPos(hWnd, SB_HORZ, buffer.GetCurrentCharacter(), TRUE);
  }
  else
    ShowScrollBar(hWnd, SB_HORZ, FALSE);
}