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

// yatlcclc.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "yatlcclc_win32.h"
#include "applfunc.h"

extern "C"
{
	#include "yatlcclc_main.h" /* Also include CIF_INC.h */
}

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HBITMAP hBitmap;
BITMAP Bitmap;
UINT_PTR mainTimer;

HDC hdc;
HDC memHdc;
HDC stretchedHdc;
HBITMAP bufBMP;

int iSpeed = 0;

LPCSTR lpcsPicturePath;

//char bSimulating = FALSE;
HANDLE applThread = NULL;

struct IS_STRUCT * inputs;

HBRUSH CGBrushes[STATE_MAX];

HWND hWndBitmapper;
HWND hWndToolbar;
HWND hWndStatusbar;

int iBitmapY = 0;
int iBitmapH = 0;
RECT BitmapRect;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_YATLCCLC, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_YATLCCLC));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_YATLCCLC));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_YATLCCLC);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);

   UpdateWindow(hWnd);

   return TRUE;
}

extern int tenth_intern;
VOID CALLBACK TimerProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  UINT_PTR idEvent,
	_In_  DWORD dwTime)
{
	static char strtime[128];
	static int prev = 0;
	InvalidateRect(hWndBitmapper, NULL, FALSE);
	if (CIF_KLOK[CIF_TSEC_TELLER] != prev)
	{
		prev = CIF_KLOK[CIF_TSEC_TELLER];
		switch (CIF_KLOK[CIF_DAGSOORT])
		{
		default:
		case CIF_MAANDAG:
			snprintf(strtime, 128, "Mon %02d-%02d-%04d %02d:%02d:%02d:%02d", CIF_KLOK[CIF_DAG], CIF_KLOK[CIF_MAAND], CIF_KLOK[CIF_JAAR], CIF_KLOK[CIF_UUR], CIF_KLOK[CIF_MINUUT], CIF_KLOK[CIF_SECONDE], tenth_intern);
			break;
		case CIF_DINSDAG:
			snprintf(strtime, 128, "Tue %02d-%02d-%04d %02d:%02d:%02d:%02d", CIF_KLOK[CIF_DAG], CIF_KLOK[CIF_MAAND], CIF_KLOK[CIF_JAAR], CIF_KLOK[CIF_UUR], CIF_KLOK[CIF_MINUUT], CIF_KLOK[CIF_SECONDE], tenth_intern);
			break;
		case CIF_WOENSDAG:
			snprintf(strtime, 128, "Wed %02d-%02d-%04d %02d:%02d:%02d:%02d", CIF_KLOK[CIF_DAG], CIF_KLOK[CIF_MAAND], CIF_KLOK[CIF_JAAR], CIF_KLOK[CIF_UUR], CIF_KLOK[CIF_MINUUT], CIF_KLOK[CIF_SECONDE], tenth_intern);
			break;
		case CIF_DONDERDAG:
			snprintf(strtime, 128, "Thu %02d-%02d-%04d %02d:%02d:%02d:%02d", CIF_KLOK[CIF_DAG], CIF_KLOK[CIF_MAAND], CIF_KLOK[CIF_JAAR], CIF_KLOK[CIF_UUR], CIF_KLOK[CIF_MINUUT], CIF_KLOK[CIF_SECONDE], tenth_intern);
			break;
		case CIF_VRIJDAG:
			snprintf(strtime, 128, "Fri %02d-%02d-%04d %02d:%02d:%02d:%02d", CIF_KLOK[CIF_DAG], CIF_KLOK[CIF_MAAND], CIF_KLOK[CIF_JAAR], CIF_KLOK[CIF_UUR], CIF_KLOK[CIF_MINUUT], CIF_KLOK[CIF_SECONDE], tenth_intern);
			break;
		case CIF_ZATERDAG:
			snprintf(strtime, 128, "Sat %02d-%02d-%04d %02d:%02d:%02d:%02d", CIF_KLOK[CIF_DAG], CIF_KLOK[CIF_MAAND], CIF_KLOK[CIF_JAAR], CIF_KLOK[CIF_UUR], CIF_KLOK[CIF_MINUUT], CIF_KLOK[CIF_SECONDE], tenth_intern);
			break;
		case CIF_ZONDAG:
			snprintf(strtime, 128, "Sun %02d-%02d-%04d %02d:%02d:%02d:%02d", CIF_KLOK[CIF_DAG], CIF_KLOK[CIF_MAAND], CIF_KLOK[CIF_JAAR], CIF_KLOK[CIF_UUR], CIF_KLOK[CIF_MINUUT], CIF_KLOK[CIF_SECONDE], tenth_intern);
			break;
		}
		SendMessage(hWndStatusbar, SB_SETTEXT, MAKEWPARAM(0, SBT_NOBORDERS), (LPARAM)strtime);
	}
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	int tbh, sbh;
	RECT rect;
	INITCOMMONCONTROLSEX InitCtrlEx;
	char strtime[128];

	switch (message)
	{
	case WM_SIZE:
		SendMessage(hWndStatusbar, WM_SIZE, wParam, lParam);
		GetWindowRect(hWndStatusbar, &rect);
		sbh = rect.bottom - rect.top;
		GetWindowRect(hWndToolbar, &rect);
		tbh = rect.bottom - rect.top;
		iBitmapY = tbh;
		iBitmapH = HIWORD(lParam) - sbh - tbh;
		SendMessage(hWndBitmapper, WM_SIZE, wParam, MAKELPARAM(LOWORD(lParam), iBitmapH));
		break;

	case WM_CREATE:


		InitCtrlEx.dwSize = sizeof(INITCOMMONCONTROLSEX);
		InitCtrlEx.dwICC = ICC_BAR_CLASSES;
		InitCommonControlsEx(&InitCtrlEx);
		InitCommonControls();

		hWndToolbar = CreateCoolToolbar(hWnd, hInst);
		CreateAllResources(CGBrushes);

		applicatieprogramma(CIF_INIT);

		CIF_WPS[CIF_PROG_STATUS] = CIF_STAT_REG;
		CIF_KLOK[CIF_DAG] = 1;
		CIF_KLOK[CIF_MAAND] = 1;
		CIF_KLOK[CIF_JAAR] = 2000;

		DisplayParameters();

		BitmapperSetFilename("test.bmp");
		BitmapperControlRegister();


		if (!(hBitmap = (HBITMAP)LoadImage(NULL, "test.bmp"/*(LPCSTR)lpcsPicturePath*/, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)))
		{
			MessageBox(hWnd, TEXT("Bitmap was not found"), TEXT("Bitmap not found"), MB_OK);
			SendMessage(hWnd, WM_CLOSE, NULL, NULL);
		}
		GetObject(hBitmap, sizeof(BITMAP), (LPVOID)&Bitmap);

		hWndStatusbar = CreateStatusBar(hWnd, ID_STATUSBAR, hInst, 4);

		CreateThread(NULL, 0, ApplProc, 0, 0, NULL);

		//		ClientResize(hWnd, Bitmap.bmWidth, Bitmap.bmHeight);

		{
			RECT rcClient, rcWindow;
			POINT ptDiff;
			GetWindowRect(hWndStatusbar, &rect);
			int sbh = rect.bottom - rect.top;
			GetWindowRect(hWndToolbar, &rect);
			int tbh = rect.bottom - rect.top;

			GetWindowRect(hWnd, &rcWindow);
			GetClientRect(hWnd, &rcClient);
			ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
			ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;
			MoveWindow(hWnd, rcWindow.left, rcWindow.top, Bitmap.bmWidth + ptDiff.x, Bitmap.bmHeight + ptDiff.y + tbh + sbh, FALSE);
		}
		hWndBitmapper = CreateWindow(BITMAPPER_WC, NULL, WS_CHILD | WS_VISIBLE,
			0, iBitmapY, Bitmap.bmWidth, Bitmap.bmHeight, hWnd, NULL, hInst, NULL);


		/* Get the sizes of the system font, for formatting */
		hdc = GetDC(hWnd);
		memHdc = CreateCompatibleDC(hdc);
		bufBMP = CreateCompatibleBitmap(hdc, Bitmap.bmWidth, Bitmap.bmHeight);

		mainTimer = SetTimer(hWnd, NULL, 5, &TimerProc);

		snprintf(strtime, 128, "Mon %02d-%02d-%04d %02d:%02d:%02d", CIF_KLOK[CIF_DAG], CIF_KLOK[CIF_MAAND], CIF_KLOK[CIF_JAAR], CIF_KLOK[CIF_UUR], CIF_KLOK[CIF_MINUUT], CIF_KLOK[CIF_SECONDE]);
		SendMessage(hWndStatusbar, SB_SETTEXT, MAKEWPARAM(0, SBT_NOBORDERS), (LPARAM)strtime);

		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_TIME_REALTIME:
		case IDM_TIME_LOWSPEED:
		case IDM_TIME_MIDSPEED:
		case IDM_TIME_HIGHSPEED:
			if (wmId == IDM_TIME_REALTIME) iSpeed = SPEED_RT;
			if (wmId == IDM_TIME_LOWSPEED) iSpeed = SPEED_LO;
			if (wmId == IDM_TIME_MIDSPEED) iSpeed = SPEED_MI;
			if (wmId == IDM_TIME_HIGHSPEED) iSpeed = SPEED_HI;
			SendMessage(hWndToolbar, TB_CHECKBUTTON, (WPARAM)IDM_TIME_REALTIME, MAKELPARAM(iSpeed == SPEED_RT, 0));
			SendMessage(hWndToolbar, TB_CHECKBUTTON, (WPARAM)IDM_TIME_LOWSPEED, MAKELPARAM(iSpeed == SPEED_LO, 0));
			SendMessage(hWndToolbar, TB_CHECKBUTTON, (WPARAM)IDM_TIME_MIDSPEED, MAKELPARAM(iSpeed == SPEED_MI, 0));
			SendMessage(hWndToolbar, TB_CHECKBUTTON, (WPARAM)IDM_TIME_HIGHSPEED, MAKELPARAM(iSpeed == SPEED_HI, 0));
			CheckMenuItem(GetMenu(hWnd), IDM_TIME_REALTIME, iSpeed == SPEED_RT ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), IDM_TIME_LOWSPEED, iSpeed == SPEED_LO ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), IDM_TIME_MIDSPEED, iSpeed == SPEED_MI ? MF_CHECKED : MF_UNCHECKED);
			CheckMenuItem(GetMenu(hWnd), IDM_TIME_HIGHSPEED, iSpeed == SPEED_HI ? MF_CHECKED : MF_UNCHECKED);
			break;
		//case IDM_SIMULATION:
		//	bSimulating = !bSimulating;
		//	SendMessage(hWndToolbar, TB_CHECKBUTTON, (WPARAM)IDM_SIMULATION, MAKELPARAM(bSimulating, 0));
		//	CheckMenuItem(GetMenu(hWnd), IDM_SIMULATION, bSimulating ? MF_CHECKED : MF_UNCHECKED);
		//	break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		// TODO: Add any drawing code here...
//		EndPaint(hWnd, &ps);
//		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
