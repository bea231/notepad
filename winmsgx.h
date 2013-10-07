#ifndef _WINMSGX_H_
#define _WINMSGX_H_

#include <windows.h>

/****** Message crackers ****************************************************/

#define HANDLE_MSG(message, fn)    \
    case (message): return HANDLE_##message((wParam), (lParam), (fn))

/* BOOL Cls_OnCreate(LPCREATESTRUCT lpCreateStruct) */
#define HANDLE_WM_CREATE(wParam, lParam, fn) \
    ((fn)((LPCREATESTRUCT)(lParam)) ? 0L : (LRESULT)-1L)

/* void Cls_OnDestroy(void) */
#define HANDLE_WM_DESTROY(wParam, lParam, fn) \
    ((fn)(), 0L)

/* void Cls_OnSize(UINT state, int cx, int cy) */
#define HANDLE_WM_SIZE(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)

/* void Cls_OnClose(void) */
#define HANDLE_WM_CLOSE(wParam, lParam, fn) \
    ((fn)(), 0L)

/* void Cls_OnPaint(void) */
#define HANDLE_WM_PAINT(wParam, lParam, fn) \
    ((fn)(), 0L)

/* BOOL Cls_OnEraseBkgnd(HDC hdc) */
#define HANDLE_WM_ERASEBKGND(wParam, lParam, fn) \
    (LRESULT)(DWORD)(BOOL)(fn)((HDC)(wParam))

/* void Cls_OnActivate(UINT state, HWND hwndActDeact, BOOL fMinimized) */
#define HANDLE_WM_ACTIVATE(wParam, lParam, fn) \
    ((fn)((UINT)LOWORD(wParam), (HWND)(lParam), (BOOL)HIWORD(wParam)), 0L)

/* void Cls_OnKey(UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define HANDLE_WM_KEYDOWN(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), TRUE, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)

/* void Cls_OnKey(UINT vk, BOOL fDown, int cRepeat, UINT flags) */
#define HANDLE_WM_KEYUP(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), FALSE, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)

/* void Cls_OnChar(TCHAR ch, int cRepeat) */
#define HANDLE_WM_CHAR(wParam, lParam, fn) \
    ((fn)((TCHAR)(wParam), (int)(short)LOWORD(lParam)), 0L)

/* void Cls_OnMouseMove(int x, int y, UINT keyFlags) */
#define HANDLE_WM_MOUSEMOVE(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnLButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_LBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnLButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_LBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnLButtonUp(int x, int y, UINT keyFlags) */
#define HANDLE_WM_LBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnRButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_RBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnRButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_RBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnRButtonUp(int x, int y, UINT flags) */
#define HANDLE_WM_RBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnMButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_MBUTTONDOWN(wParam, lParam, fn) \
    ((fn)(FALSE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnMButtonDown(BOOL fDoubleClick, int x, int y, UINT keyFlags) */
#define HANDLE_WM_MBUTTONDBLCLK(wParam, lParam, fn) \
    ((fn)(TRUE, (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnMButtonUp(int x, int y, UINT flags) */
#define HANDLE_WM_MBUTTONUP(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (UINT)(wParam)), 0L)

/* void Cls_OnMouseWheel(int xPos, int yPos, int zDelta, UINT fwKeys) */
#define HANDLE_WM_MOUSEWHEEL(wParam, lParam, fn) \
    ((fn)((int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), (int)(short)HIWORD(wParam), (UINT)(short)LOWORD(wParam)), 0L)

/* void Cls_OnTimer(UINT id) */
#define HANDLE_WM_TIMER(wParam, lParam, fn) \
    ((fn)((UINT)(wParam)), 0L)

/* BOOL Cls_OnSetCursor(HWND hwndCursor, UINT codeHitTest, UINT msg) */
#define HANDLE_WM_SETCURSOR(wParam, lParam, fn) \
    (LRESULT)(DWORD)(BOOL)(fn)((HWND)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam))

/* void Cls_OnSysCommand(UINT cmd, int x, int y) */
#define HANDLE_WM_SYSCOMMAND(wParam, lParam, fn) \
    ((fn)((UINT)(wParam), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam)), 0L)

#endif /* _WINMSGX_H_ */

/* END OF 'WINMSGX.H' FILE */