/*
Copyright (C) 2016 CodingConnected e. U., Menno van der Woude

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

#include <Windows.h>
#include <CommCtrl.h>

//extern "C"
//{
	#include "tlccc_main.h" /* Also include CIF_INC.h */
//}

#include "tlccc_win32.h"

extern HWND hWndBitmapper;
extern HWND hWndStatusbar;

extern BITMAP Bitmap;
extern int iSpeed;

extern int iBitmapY;
extern int iBitmapH;
extern RECT BitmapRect;

DWORD WINAPI ApplProc(_In_ LPVOID lpParameter);
void UpdateClock();
VOID CALLBACK TimerProc(_In_  HWND hwnd, _In_  UINT uMsg, _In_  UINT_PTR idEvent, _In_  DWORD dwTime);
void ClientResize(HWND hWnd, int nWidth, int nHeight, HWND hWndStatusBar, HWND hWndToolbar);
void CreateAllResources(HBRUSH CGBrushes[]);
HWND CreateStatusBar(HWND hwndParent, int idStatus, HINSTANCE hinst, int cParts);
HWND CreateCoolToolbar(HWND hWndParent, HINSTANCE hInst);
HRGN BitmapToRegion(HDC hdc, COLORREF cRef, int _x, int _y);

#define SPEED_RT 0
#define SPEED_LO 1
#define SPEED_MI 2
#define SPEED_HI 3
