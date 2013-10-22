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

    /* Get first file to outout name from first program parameter */
    sscanf(cmdLine, "%s", textFileName);
    buffer.Open((unsigned char *)textFileName);
  }
  buffer.Open(NULL);
}

/* Class destructor */
notepad::textview::~textview( void )
{
}

/* Initialization function */
void notepad::textview::Init( void )
{
  TEXTMETRIC textMetric;

  /* Calculate text characters width and height (in pixels) */
  GetTextMetrics(hDC, &textMetric);
  textHeight = textMetric.tmHeight + textMetric.tmExternalLeading;
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
  /* Calculate new count of strings and characers which can be displayed in work-area */
  stringsInPage = height / textHeight;
  charsInPage = width / textWidth;

  /* Set new scroll bar width and height */
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

/* WM_MOUSEWHEEL window message handle function */
void notepad::textview::MouseWheel(int xPos, int yPos, int zDelta, unsigned int fwKeys)
{
  /* Calculate count of wheel rotate (in WHEEL_DELTA) */
  zDelta = zDelta / WHEEL_DELTA;
  if (fwKeys == MK_SHIFT)
  {
    buffer.ShiftX(-zDelta);
  }
  else
    buffer.ShiftY(-zDelta);
  /* Calculate new scroll bar position */
  UpdateScrollBar();
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
  /* Calculate new scroll bar position */
  UpdateScrollBar();
  InvalidateRect(hWnd, NULL, FALSE);
}

/* WM_COMMAND window message handle function */
void notepad::textview::Command(int id, HWND hwndCtl, UINT codeNotify)
 {
   OPENFILENAME openFileStruct = {0};
   unsigned char fileName[MAX_PATH] = {0};

   switch(id)
   {
   case ID_FILE_EXIT:
     SendMessage(hWnd, WM_DESTROY, 0, 0);
     break;
   case ID_MYFILE_OPEN:
     /* Fill structure to open file */
     openFileStruct.lStructSize = sizeof(OPENFILENAME);
     openFileStruct.hwndOwner = hWnd;
     openFileStruct.lpstrFile = (char *)fileName;
     openFileStruct.nMaxFile = MAX_PATH;
     openFileStruct.lpstrFilter = "All\0*.*\0Text files\0*.txt\0";
     openFileStruct.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

     if (GetOpenFileName(&openFileStruct) != FALSE)
     {
       /* Read new text to buffer from new file */
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
    buffer.ShiftX(-(long)charsInPage);    // shift text by one-page to left
    break;
  case SB_PAGERIGHT:
    buffer.ShiftX(charsInPage);           // shift text by one-page to right
    break;
  case SB_THUMBTRACK:
    scrollInfo.fMask = SIF_POS;
    GetScrollInfo(hWnd, SB_HORZ, &scrollInfo);
    buffer.ShiftX(pos - scrollInfo.nPos); // shift text by track value
    break;
  case SB_LINERIGHT:
    buffer.ShiftX(1);                     // shift right
    break;
  case SB_LINELEFT:
    buffer.ShiftX(-1);                    // shift left
    break;
  }
  UpdateScrollBar();
  InvalidateRect(hWnd, NULL, FALSE);
}

/* WM_VSCROLL window message handle function */
void notepad::textview::VScroll(HWND hwndCtl, UINT code, int pos)
{
  SCROLLINFO scrollInfo;

  scrollInfo.cbSize = sizeof(SCROLLINFO);
  switch (code)
  {
  case SB_PAGEUP:
    buffer.ShiftY(-(long)stringsInPage);        // shift text by one-page up
    break;
  case SB_PAGEDOWN:
    buffer.ShiftY(stringsInPage);               // shift text by one-page down
    break;
  case SB_THUMBTRACK:
    scrollInfo.fMask = SIF_POS;
    GetScrollInfo(hWnd, SB_VERT, &scrollInfo);
    buffer.ShiftY(pos - scrollInfo.nPos);       // shift text by track value
    break;
  case SB_LINEDOWN:
    buffer.ShiftY(1);                           // shift text by one-line down
    break;
  case SB_LINEUP:
    buffer.ShiftY(-1);                          // shift text by one-line up
    break;
  }
  UpdateScrollBar();
  InvalidateRect(hWnd, NULL, FALSE);
}
/* Hide or show scrollbar and set new scrollbar position function */
void notepad::textview::UpdateScrollBar( void )
{
  SCROLLINFO scrollInfo;

  if (stringsInPage < buffer.GetStringsCount())
  {
    /* Show vertical scroll bar */
    ShowScrollBar(hWnd, SB_VERT, TRUE);

    /* Set new width and minimum-maximum position of scrollbar */
    scrollInfo.cbSize = sizeof(SCROLLINFO);
    scrollInfo.fMask = SIF_PAGE | SIF_RANGE;
    scrollInfo.nMin = 0;
    scrollInfo.nMax = buffer.GetStringsCount() + stringsInPage - buffer.breakScrollY - 1;
    scrollInfo.nPage = stringsInPage;
    SetScrollInfo(hWnd, SB_VERT, &scrollInfo, TRUE);

    /* Set current scrollbar position */
    SetScrollPos(hWnd, SB_VERT, buffer.GetCurrentString(), TRUE);
  }
  else
    ShowScrollBar(hWnd, SB_VERT, FALSE);  // Hide vertical scroll bar

  if (charsInPage < buffer.GetMaxStringLength())
  {
    /* Show horizontal scroll bar */
    ShowScrollBar(hWnd, SB_HORZ, TRUE);

    /* Set new width and minimum-maximum position of scrollbar */
    scrollInfo.nMin = 0;
    scrollInfo.nMax = buffer.GetMaxStringLength() + charsInPage - buffer.breakScrollX - 1;
    scrollInfo.nPage = charsInPage;
    SetScrollInfo(hWnd, SB_HORZ, &scrollInfo, TRUE);

    /* Set current scrollbar position */
    SetScrollPos(hWnd, SB_HORZ, buffer.GetCurrentCharacter(), TRUE);
  }
  else
    ShowScrollBar(hWnd, SB_HORZ, FALSE);  // Hide horizontal scroll bar
}
