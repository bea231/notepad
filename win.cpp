/* Sergeev Artemiy, 33602 (3057/2) */

#include "winmsgx.h"
#include "win.h"

/* Class constructor */
task2::win::win( int CmdShow, char *CmdLine, HINSTANCE hInst, char *WindowName ) : IsInit(FALSE), CmdLine(CmdLine), CmdShow(CmdShow)
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
  wc.hCursor = LoadCursor(NULL, (CHAR *)IDC_ARROW);
  wc.hIcon = LoadIcon(NULL, (CHAR *)IDI_APPLICATION);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = WinFuncCallBack;
  wc.lpszClassName = MainWndClassName;
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR",
      MB_OK | MB_ICONSTOP);
    return;
  }

  /* Window creation */
  hWnd = CreateWindow(MainWndClassName,
    WindowName,
    WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    NULL, NULL, hInstance, (void *)this);
  if (hWnd == NULL)
  {
    MessageBox(NULL, "Error create window", "ERROR",
      MB_OK | MB_ICONSTOP);
    return;
  }
  /* Show and update window */
  ShowWindow(hWnd, CmdShow);
  UpdateWindow(hWnd);

  /* Send initialization timer message */
  PostMessage(hWnd, WM_TIMER, (WPARAM)InitializationTimerId, 0);
} /* End of 'task2::win::win' constructor */

/* Windowed application running function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (int) error level.
 */
int task2::win::Run( void )
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
      if (IsInit)
        Idle();
  }
  return msg.wParam;
} /* End of 'task2::win::Run' function */

/* Class destructor */
task2::win::~win( void )
{
} /* End of 'task2::win::~win' destructor */

/* System exit function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void task2::win::DoExit( void )
{
  PostMessage(hWnd, WM_CLOSE, 0, 0);
} /* End of 'task2::win::DoExit' destructor */

/* The set full screen application mode.
 * ARGUMENTS:
 *   - is full screen flag:
 *       BOOL IsFullScreen;
 * RETURNS: None.
 */
void task2::win::SetFullScreen( BOOL IsFull )
{
  RECT rc;
  DWORD Style;

  if (IsFull == IsFullScreen)
    return;
  if ((IsFullScreen = IsFull) != FALSE)
  {
    GetWindowRect(hWnd, &SaveRC);
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
    SetWindowPos(hWnd, HWND_TOP, SaveRC.left, SaveRC.top, SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER | SWP_NOSENDCHANGING);
  }
} /* End of 'task2::win::SetFullScreen' function */

/* Window message handle function (CALLBACK version) */
LRESULT CALLBACK task2::win::WinFuncCallBack( HWND hWnd, unsigned int Msg, WPARAM wParam, LPARAM lParam )
{
  win *Win;

  switch (Msg)
  {
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLong(hWnd, 0, (LONG)((CREATESTRUCT *)lParam)->lpCreateParams);
  default:
    Win = (win *)GetWindowLong(hWnd, 0);
    if (Win != NULL)
      return Win->WinFunc(Msg, wParam, lParam);
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'task2::win::WinFuncCallBack' function */

/* Window handle message (with crack message calls) */
LRESULT task2::win::WinFunc( unsigned int Msg, WPARAM wParam, LPARAM lParam )
{
  switch (Msg)
  {
  HANDLE_MSG(WM_CREATE, OnCreate);
  HANDLE_MSG(WM_SIZE, OnSize);
  HANDLE_MSG(WM_ACTIVATE, OnActivate);
  HANDLE_MSG(WM_ERASEBKGND, OnEraseBkgnd);
  HANDLE_MSG(WM_PAINT, OnPaint);
  HANDLE_MSG(WM_TIMER, OnTimer);
  HANDLE_MSG(WM_KEYDOWN, OnKey);
  HANDLE_MSG(WM_CLOSE, OnClose);
  HANDLE_MSG(WM_MOUSEMOVE, OnMouseMove);
  //HANDLE_MSG(WM_DESTROY, OnDestroy);
  //HANDLE_MSG(WM_KEYUP, OnKey);
  //HANDLE_MSG(WM_CHAR, OnChar);
  //HANDLE_MSG(WM_LBUTTONDOWN, OnLButtonDown);
  //HANDLE_MSG(WM_LBUTTONDBLCLK, OnLButtonDown);
  //HANDLE_MSG(WM_LBUTTONUP, OnLButtonUp);
  //HANDLE_MSG(WM_RBUTTONDOWN, OnRButtonDown);
  //HANDLE_MSG(WM_RBUTTONDBLCLK, OnRButtonDown);
  //HANDLE_MSG(WM_RBUTTONUP, OnRButtonUp);
  //HANDLE_MSG(WM_MBUTTONDOWN, OnMButtonDown);
  //HANDLE_MSG(WM_MBUTTONDBLCLK, OnMButtonDown);
  //HANDLE_MSG(WM_MBUTTONUP, OnMButtonUp);
  //HANDLE_MSG(WM_MOUSEWHEEL, OnMouseWheel);
  //HANDLE_MSG(WM_SETCURSOR, OnSetCursor);
  //HANDLE_MSG(WM_SYSCOMMAND, OnSysCommand);
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'task2::win::WinFunc' function */

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL task2::win::OnCreate( CREATESTRUCT *CS )
{
  return TRUE;
} /* End of 'task2::win::OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void task2::win::OnClose( void )
{
  /* Call user level deinitialization */
  if (IsInit)
  {
    IsInit = FALSE;
    Close();
  }
  PostQuitMessage(0);
} /* End of 'task2::win::OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       unsigned int State;
 *   - new width and height of client area:
 *       int W, H;
 * RETURNS: None.
 */
void task2::win::OnSize( unsigned int State, int W, int H )
{
  Width = W;
  Height = H;
  /* Call user level change size notifivcation */
  if (IsInit)
    Resize();
  InvalidateRect(hWnd, NULL, FALSE);
} /* End of 'task2::win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL task2::win::OnEraseBkgnd( HDC hDC )
{
  /* Call user level erase background function */
  if (IsInit)
    Erase(hDC);
  return FALSE;
} /* End of 'task2::win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void task2::win::OnPaint( void )
{
  HDC hDC;
  PAINTSTRUCT ps;

  hDC = BeginPaint(hWnd, &ps);
  /* Call user level paint window content function */
  if (IsInit)
    Paint(hDC);
  EndPaint(hWnd, &ps);
} /* End of 'task2::win::OnPaint' function */

/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       unsigned int Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
void task2::win::OnActivate( unsigned int Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
  /* Call user level activate handle function */
  if (IsInit)
    Activate(Reason);
} /* End of 'task2::win::OnActivate' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       int Id;
 * RETURNS: None.
 */
void task2::win::OnTimer( int Id )
{
  if (Id == InitializationTimerId)
  {
    IsInit = TRUE;
    Init();
    Resize();
    InvalidateRect(hWnd, NULL, TRUE);
    if (IsActive)
      Activate(TRUE);
  }
  else
    /* Call user level timer handle function */
    if (IsInit)
      Timer();
} /* End of 'task2::win::OnDestroy' function */

/* WM_KEYDOWN window message handle function.
 * ARGUMENTS:
 *   - virtual key identyfier:
 *       unsigned int vk;
 *   - is button down:
 *       BOOL fDown;
 *   - count of pressing repeat:
 *       int cRepeate;
 *   - flags:
 *       unsigned int flags;
 * RETURNS: None.
 */
void task2::win::OnKey(unsigned int vk, bool fDown, int cRepeat, unsigned int flags)
{
  Key(vk, fDown);
} /* End of 'task2::win::OnCreate' function */

/* WM_MOUSEMOVE window message handle function.
 * ARGUMENTS:
 *   - new mouse coordinate:
 *       int x, y;
 *   - state mouse flags:
 *       unsigned int flags;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
void task2::win::OnMouseMove(int x, int y, unsigned int flags)
{
  Mouse(x, y, flags);
} /* End of 'task2::win::OnCreate' function */
