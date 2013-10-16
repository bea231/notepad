/* Sergeev Artemiy, 2057/2 */

#ifndef _WINMSGX_H_
#define _WINMSGX_H_

/****** Message crackers ****************************************************/

#define HANDLE_MSG(message, fn)    \
    case (message): return HANDLE_##message((wParam), (lParam), (fn))

/* bool Cls_OnCreate(LPCREATESTRUCT lpCreateStruct) */
#define HANDLE_WM_CREATE(wParam, lParam, fn) \
    ((fn)((LPCREATESTRUCT)(lParam)) ? 0L : (LRESULT)-1L)

/* void Cls_OnDestroy(void) */
#define HANDLE_WM_DESTROY(wParam, lParam, fn) \
    ((fn)(), 0L)

/* void Cls_OnSize(unsigned int state, int cx, int cy) */
#define HANDLE_WM_SIZE(wParam, lParam, fn) \
    ((fn)((unsigned int)(wParam), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)

/* void Cls_OnClose(void) */
#define HANDLE_WM_CLOSE(wParam, lParam, fn) \
    ((fn)(), 0L)

/* void Cls_OnPaint(void) */
#define HANDLE_WM_PAINT(wParam, lParam, fn) \
    ((fn)(), 0L)

/* bool Cls_OnEraseBkgnd(HDC hdc) */
#define HANDLE_WM_ERASEBKGND(wParam, lParam, fn) \
    (LRESULT)(DWORD)(bool)(fn)((HDC)(wParam))

/* void Cls_OnActivate(unsigned int state, HWND hwndActDeact, bool fMinimized) */
#define HANDLE_WM_ACTIVATE(wParam, lParam, fn) \
    ((fn)((unsigned int)LOWORD(wParam), (HWND)(lParam), (bool)(HIWORD(wParam) != 0)), 0L)

/* void Cls_OnKey(unsigned int vk, bool fDown, int cRepeat, unsigned int flags) */
#define HANDLE_WM_KEYDOWN(wParam, lParam, fn) \
    ((fn)((unsigned int)(wParam), TRUE, (int)(short)LOWORD(lParam), (unsigned int)(HIWORD(lParam) != 0)), 0L)

/* void Cls_OnKey(unsigned int vk, bool fDown, int cRepeat, unsigned int flags) */
#define HANDLE_WM_KEYUP(wParam, lParam, fn) \
    ((fn)((unsigned int)(wParam), FALSE, (int)(short)LOWORD(lParam), (unsigned int)HIWORD(lParam)), 0L)

/* void Cls_OnChar(TCHAR ch, int cRepeat) */
#define HANDLE_WM_CHAR(wParam, lParam, fn) \
    ((fn)((TCHAR)(wParam), (int)(short)LOWORD(lParam)), 0L)

/* void Cls_OnMouseMove(int x, int y, unsigned int keyFlags) */
#define HANDLE_WM_MOUSEMOVE(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnLButtonDown(bool fDoubleClick, int x, int y, unsigned int keyFlags) */
#define HANDLE_WM_LBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnLButtonDown(bool fDoubleClick, int x, int y, unsigned int keyFlags) */
#define HANDLE_WM_LBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnLButtonUp(int x, int y, unsigned int keyFlags) */
#define HANDLE_WM_LBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnRButtonDown(bool fDoubleClick, int x, int y, unsigned int keyFlags) */
#define HANDLE_WM_RBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnRButtonDown(bool fDoubleClick, int x, int y, unsigned int keyFlags) */
#define HANDLE_WM_RBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnRButtonUp(int x, int y, unsigned int flags) */
#define HANDLE_WM_RBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnMButtonDown(bool fDoubleClick, int x, int y, unsigned int keyFlags) */
#define HANDLE_WM_MBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnMButtonDown(bool fDoubleClick, int x, int y, unsigned int keyFlags) */
#define HANDLE_WM_MBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnMButtonUp(int x, int y, unsigned int flags) */
#define HANDLE_WM_MBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (unsigned int)(wParam)), 0L)

/* void Cls_OnMouseWheel(int xPos, int yPos, int zDelta, unsigned int fwKeys) */
#define HANDLE_WM_MOUSEWHEEL(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (int)(short)HIWORD(wParam), (unsigned int)(short)LOWORD(wParam)), 0L)

/* void Cls_OnTimer(unsigned int id) */
#define HANDLE_WM_TIMER(wParam, lParam, fn) \
    ((fn)((unsigned int)(wParam)), 0L)

/* bool Cls_OnSetCursor(HWND hwndCursor, unsigned int codeHitTest, unsigned int msg) */
#define HANDLE_WM_SETCURSOR(wParam, lParam, fn) \
    (LRESULT)(DWORD)(bool)(fn)((HWND)(wParam), (unsigned int)LOWORD(lParam), (unsigned int)HIWORD(lParam))

/* void Cls_OnSysCommand(unsigned int cmd, int x, int y) */
#define HANDLE_WM_SYSCOMMAND(wParam, lParam, fn) \
    ((fn)((unsigned int)(wParam), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)

/* void Cls_OnGetMinMaxInfo(HWND hwnd, LPMINMAXINFO lpMinMaxInfo) */
#define HANDLE_WM_GETMINMAXINFO(wParam, lParam, fn) \
    ((fn)((LPMINMAXINFO)(lParam)), 0L)

/* void Cls_OnHScroll(HWND hwndCtl, UINT code, int pos) */
#define HANDLE_WM_HSCROLL(wParam, lParam, fn) \
    ((fn)((HWND)(lParam), (UINT)(LOWORD(wParam)), (int)(short)HIWORD(wParam)), 0L)

/* void Cls_OnVScroll(HWND hwndCtl, UINT code, int pos) */
#define HANDLE_WM_VSCROLL(wParam, lParam, fn) \
    ((fn)((HWND)(lParam), (UINT)(LOWORD(wParam)),  (int)(short)HIWORD(wParam)), 0L)

/* void Cls_OnCommand(int id, HWND hwndCtl, UINT codeNotify) */
#define HANDLE_WM_COMMAND(wParam, lParam, fn) \
    ((fn)((int)(LOWORD(wParam)), (HWND)(lParam), (unsigned int)HIWORD(wParam)), 0L)

#endif /* _WINMSGX_H_ */
