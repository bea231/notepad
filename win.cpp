/* Sergeev Artemiy, 33601/2 (3057/2) */

#include "win.h"
#include "winmsgx.h"

/* Class constructor */
notepad::win::win( HINSTANCE hInst, int cmdShow ) : isInit(FALSE)
{
  WNDCLASS wc;

  /* Store application instance handle */
  if (hInst == NULL)
    hInst = GetModuleHandle(NULL);
  hInstance = hInst;

  /* Fill and register window class */
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = sizeof(void *);
  wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wc.hCursor = LoadCursor(NULL, (char *)IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, (char *)IDI_APPLICATION);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = WinFuncCallBack;
  wc.lpszClassName = c_MainWndClassName;
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR",
      MB_OK | MB_ICONSTOP);
    return;
  }

  /* Window creation */
  hWnd = CreateWindow(c_MainWndClassName,
    "Notepad",
    WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, (void *)this);
  if (hWnd == NULL)
  {
    MessageBox(NULL, "Error create window", "ERROR",
      MB_OK | MB_ICONSTOP);
    exit(0);
  }
  /* Show and update window */
  ShowWindow(hWnd, cmdShow);
  UpdateWindow(hWnd);

  /* Send initialization timer message */
  PostMessage(hWnd, WM_TIMER, (WPARAM)c_initializationTimer, 0);
}

/* Windowed application running function */
int notepad::win::Run( void )
{
  MSG msg;

  /* Message loop */
  while (TRUE)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
        break;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
      if (isInit)
        Idle();
  }
  return msg.wParam;
}

/* Class destructor */
notepad::win::~win( void )
{
}

/* System exit function */
void notepad::win::DoExit( void )
{
  PostMessage(hWnd, WM_CLOSE, 0, 0);
}

/* The set full screen application mode */
void notepad::win::SetFullScreen( bool IsFull )
{
  RECT rc;
  DWORD Style;

  if (IsFull == isFullScreen)
    return;
  if ((isFullScreen = IsFull) != FALSE)
  {
    GetWindowRect(hWnd, &saveRC);
    rc.left = 0;
    rc.top = 0;
    rc.right = GetSystemMetrics(SM_CXSCREEN);
    rc.bottom = GetSystemMetrics(SM_CYSCREEN);
    Style = GetWindowLong(hWnd, GWL_STYLE);
    AdjustWindowRect(&rc, Style, FALSE);
    SetWindowPos(hWnd, HWND_TOP, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER | SWP_NOREDRAW | SWP_NOSENDCHANGING);
  }
  else
  {
    SetWindowPos(hWnd, HWND_TOP, saveRC.left, saveRC.top, saveRC.right - saveRC.left, saveRC.bottom - saveRC.top,
      SWP_NOOWNERZORDER | SWP_NOSENDCHANGING);
  }
}

/* Window message handle function (CALLBACK version) */
LRESULT CALLBACK notepad::win::WinFuncCallBack( HWND hWnd, unsigned int msg, WPARAM wParam, LPARAM lParam )
{
  win *Win;

  switch (msg)
  {
  case WM_CREATE:
    {
      /* Attach 'this' pointer to window class to window */
      notepad::win *myThis = (notepad::win *)((CREATESTRUCT *)lParam)->lpCreateParams;

      SetWindowLong(hWnd, 0, (LONG)myThis);
      myThis->OnCreate(hWnd, (CREATESTRUCT *)lParam);
    }
  default:
    Win = (win *)GetWindowLong(hWnd, 0);
    if (Win != NULL)
      return Win->WinFunc(msg, wParam, lParam);
  }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}

/* Window handle message (with crack message calls) */
LRESULT notepad::win::WinFunc( unsigned int msg, WPARAM wParam, LPARAM lParam )
{
  switch (msg)
  {
  /* Run specialized macros to convert 'wParam' and 'lParam' for user message process functions */
  HANDLE_MSG(WM_SIZE, OnSize);
  HANDLE_MSG(WM_ACTIVATE, OnActivate);
  HANDLE_MSG(WM_ERASEBKGND, OnEraseBkgnd);
  HANDLE_MSG(WM_PAINT, OnPaint);
  HANDLE_MSG(WM_TIMER, OnTimer);
  HANDLE_MSG(WM_DESTROY, OnClose);
  HANDLE_MSG(WM_CLOSE, OnClose);
  HANDLE_MSG(WM_KEYDOWN, Key);
  HANDLE_MSG(WM_KEYUP, Key);
  HANDLE_MSG(WM_MOUSEMOVE, MouseMove);
  HANDLE_MSG(WM_MOUSEWHEEL, MouseWheel);
  HANDLE_MSG(WM_COMMAND, Command);
  HANDLE_MSG(WM_VSCROLL, VScroll);
  HANDLE_MSG(WM_HSCROLL, HScroll);
  }
  return DefWindowProc(hWnd, msg, wParam, lParam);
}

/* WM_CREATE window message handle function */
bool notepad::win::OnCreate( HWND hWnd, CREATESTRUCT *createStruct )
{
  HDC hDC;

  /* Create second frame buffer */
  hDC = ::GetDC(hWnd);
  this->hDC = CreateCompatibleDC(hDC);
  hBm = CreateCompatibleBitmap(hDC, 10, 10);
  SelectObject(this->hDC, hBm);
  ReleaseDC(hWnd, hDC);

  SetTimer(hWnd, 1110111, 5, NULL);

  isFullScreen = FALSE;
  return TRUE;
}

/* WM_DESTROY window message handle function */
void notepad::win::OnClose( void )
{
  KillTimer(hWnd, 1110111);
  ReleaseDC(hWnd, hDC);
  DeleteObject(hBm);
  /* Call user level deinitialization */
  if (isInit)
  {
    isInit = FALSE;
    Close();
  }
  PostQuitMessage(0);
}

/* WM_SIZE window message handle function */
void notepad::win::OnSize( unsigned int state, int newWidth, int newHeight )
{
  width = newWidth;
  height = newHeight;

  HDC hDC;
  /* Delete old second frame buffer */
  DeleteObject(hBm);
  /* Create new frame buffer */
  hDC = ::GetDC(hWnd);
  hBm = CreateCompatibleBitmap(hDC, width, height);
  ReleaseDC(hWnd, hDC);
  SelectObject(this->hDC, hBm);

  /* Call user level change size notifivcation */
  if (isInit)
    Resize();
  InvalidateRect(hWnd, NULL, FALSE);
}

/* WM_ERASEBKGND window message handle function */
bool notepad::win::OnEraseBkgnd( HDC hDC )
{
  /* Call user level erase background function */
  if (isInit)
    Erase();
  return FALSE;
}

/* WM_PAINT window message handle function */
void notepad::win::OnPaint( void )
{
  HDC hDC;
  PAINTSTRUCT ps;
  HPEN hOldPen = (HPEN)SelectObject(this->hDC, GetStockObject(NULL_PEN));
  HBRUSH hOldBrush = (HBRUSH)SelectObject(this->hDC, GetStockObject(WHITE_BRUSH));

  hDC = BeginPaint(hWnd, &ps);

  /* Call user level paint window content function */
  if (isInit)
  {
    /* Default action - draw white rectangle */
    Rectangle(this->hDC, 0, 0, width + 1, height + 1);
    SelectObject(this->hDC, hOldPen);
    SelectObject(this->hDC, hOldBrush);
    Paint();
  }
  BitBlt(hDC, 0, 0, width, height, this->hDC, 0, 0, SRCCOPY);
  EndPaint(hWnd, &ps);
}

/* WM_ACTIVATE window message handle function */
void notepad::win::OnActivate( unsigned int reason, HWND hWndActDeact, bool isMinimized )
{
  isActive = reason == WA_CLICKACTIVE || reason == WA_ACTIVE;
  /* Call user level activate handle function */
  if (isInit)
    Activate(reason != 0);
}

/* WM_TIMER window message handle function */
void notepad::win::OnTimer( int id )
{
  if (id == c_initializationTimer)
  {
    isInit = TRUE;
    Init();
    Resize();
    InvalidateRect(hWnd, NULL, TRUE);
    if (isActive)
      Activate(TRUE);
  }
  else
    /* Call user level timer handle function */
    if (isInit)
    {
      Timer(id);
      InvalidateRect(hWnd, NULL, FALSE);
    }
}
