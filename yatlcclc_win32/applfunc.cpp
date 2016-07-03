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

#include "applfunc.h"

DWORD WINAPI ApplProc(
	_In_ LPVOID lpParameter
	)
{
	extern char bSimulating;
	static char _bSimulating = false;

	while (1)
	{
		
		UpdateClock();
		applicatieprogramma(0);
		switch (iSpeed)
		{
		case SPEED_RT:
			Sleep(100);
			break;
		case SPEED_LO:
			Sleep(100);
			break;
		case SPEED_MI:
			Sleep(10);
			break;
		default:
		case SPEED_HI:
			break;
		}
	}
	return 0;
}

int tenth_intern = 0;
void UpdateClock()
{
	static int iSimTimeHour = 12, iSimTimeMinute = 0, iSimTimeSecond = 0;

	// update clock
	if (iSpeed == SPEED_RT || iSpeed == SPEED_MI)
	{
		int i = ++CIF_KLOK[CIF_TSEC_TELLER];
		tenth_intern++;
	}
	else
	{
		CIF_KLOK[CIF_TSEC_TELLER] += 5;
		tenth_intern += 5;
	}
	if (CIF_KLOK[CIF_TSEC_TELLER] < 0) 
		CIF_KLOK[CIF_TSEC_TELLER] = 0;

	if (tenth_intern >= 10) tenth_intern = 0, iSimTimeSecond++, CIF_KLOK[CIF_SEC_TELLER]++;
	if (CIF_KLOK[CIF_SEC_TELLER] < 0) 
		CIF_KLOK[CIF_SEC_TELLER] = 0;

	if (iSimTimeSecond >= 60) iSimTimeSecond = 0, iSimTimeMinute++;
	if (iSimTimeMinute >= 60) iSimTimeMinute = 0, iSimTimeHour++;
	if (iSimTimeHour >= 24) iSimTimeHour = 0;

	CIF_KLOK[CIF_UUR] = iSimTimeHour;
	CIF_KLOK[CIF_MINUUT] = iSimTimeMinute;
	CIF_KLOK[CIF_SECONDE] = iSimTimeSecond;

	// day switch
	if (CIF_KLOK[CIF_UUR] == 0 && CIF_KLOK[CIF_MINUUT] == 0 && CIF_KLOK[CIF_SECONDE] == 0 && tenth_intern == 0)
	{
		// sort of day
		CIF_KLOK[CIF_DAGSOORT]++;
		if (CIF_KLOK[CIF_DAGSOORT] > 6) CIF_KLOK[CIF_DAGSOORT] = 0;

		// date
		CIF_KLOK[CIF_DAG]++;
		switch (CIF_KLOK[CIF_MAAND])
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
			if (CIF_KLOK[CIF_DAG] > 31)
			{
				CIF_KLOK[CIF_MAAND]++;
				CIF_KLOK[CIF_DAG] = 1;
			}
			break;
		case 12:
			if (CIF_KLOK[CIF_DAG] > 31)
			{
				CIF_KLOK[CIF_JAAR]++;
				CIF_KLOK[CIF_MAAND] = 1;
				CIF_KLOK[CIF_DAG] = 1;
			}
			break;
		case 2:
			if (CIF_KLOK[CIF_DAG] > 28)
			{
				CIF_KLOK[CIF_MAAND]++;
				CIF_KLOK[CIF_DAG] = 1;
			}
			break;
		default:
			if (CIF_KLOK[CIF_DAG] > 30)
			{
				CIF_KLOK[CIF_MAAND]++;
				CIF_KLOK[CIF_DAG] = 1;
			}
			break;
		}
	}
}

void ClientResize(HWND hWnd, int nWidth, int nHeight, HWND hWndStatusBar, HWND hWndToolbar)
{
	RECT rcClient, rcWindow;
	POINT ptDiff;

	GetWindowRect(hWndStatusbar, &rcClient);
	int sbh = rcClient.bottom - rcClient.top;
	GetWindowRect(hWndToolbar, &rcClient);
	int tbh = rcClient.bottom - rcClient.top;
	iBitmapY = tbh;
	iBitmapH = nHeight - sbh - tbh;

	GetClientRect(hWnd, &rcClient);
	GetWindowRect(hWnd, &rcWindow);
	ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
	ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;

	///MoveWindow(hWnd, rcWindow.left, rcWindow.top, nWidth + ptDiff.x, nHeight + ptDiff.y + tbh + sbh, FALSE);

	BitmapRect.top = tbh;
	BitmapRect.bottom = nHeight - sbh;
	BitmapRect.left = 0;
	BitmapRect.right = nWidth;
	InvalidateRect(hWnd, &BitmapRect, FALSE);
}

// Function below found here:
// http://www.codeguru.com/cpp/g-m/bitmap/usingregions/article.php/c1751/Converting-a-bitmap-to-a-region.htm
// No license is given.
//
//	BitmapToRegion :	Create a region from the "non-transparent" pixels of a bitmap
//	Author :			Jean-Edouard Lachand-Robert (http://www.geocities.com/Paris/LeftBank/1160/resume.htm), June 1998.
//
//	hBmp :				Source bitmap
//	cTransparentColor :	Color base for the "transparent" pixels (default is black)
//	cTolerance :		Color tolerance for the "transparent" pixels.
//
//	A pixel is assumed to be transparent if the value of each of its 3 components (blue, green and red) is 
//	greater or equal to the corresponding value in cTransparentColor and is lower or equal to the 
//	corresponding value in cTransparentColor + cTolerance.
//
// https://github.com/cswuyg/simple_win/blob/master/use_rgn_api_to_transparent/SetWindowRgn/transparent/transparent.cpp
HRGN BitmapToRegion(HDC hdc, COLORREF cRef, int _x, int _y)
{
	HRGN hRgn = NULL;

	if (hdc)
	{
		// For better performances, we will use the ExtCreateRegion() function to create the
		// region. This function take a RGNDATA structure on entry. We will add rectangles by
		// amount of ALLOC_UNIT number in this structure.
#define ALLOC_UNIT	100
		DWORD maxRects = ALLOC_UNIT;
		HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects));
		RGNDATA *pData = (RGNDATA *)GlobalLock(hData);
		pData->rdh.dwSize = sizeof(RGNDATAHEADER);
		pData->rdh.iType = RDH_RECTANGLES;
		pData->rdh.nCount = pData->rdh.nRgnSize = 0;
		SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);

		int maxx = -1;
		for (int y = _y; y < Bitmap.bmHeight; ++y)
		{
			char finished = 1;
			int xs = -1, xe = -1;
			for (int x = _x; x < Bitmap.bmWidth; ++x)
			{
				// Search for a continuous range
				COLORREF cr1 = GetPixel(hdc, x, y);
				if (cr1 != cRef)
				{
					xe++;
					if (xs != -1 || x >= maxx)
						break;
					continue;
				}
				else
				{
					if (xs == -1) xs = x;
					xe = x;
					if (x > maxx) maxx = x;
					finished = 0;
				}
			}
			if (!finished)
			{
				// Add the pixels (x0, y) to (x, y+1) as a new rectangle in the region
				if (pData->rdh.nCount >= maxRects)
				{
					GlobalUnlock(hData);
					maxRects += ALLOC_UNIT;
					hData = GlobalReAlloc(hData, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), GMEM_MOVEABLE);
					pData = (RGNDATA *)GlobalLock(hData);
				}
				RECT *pr = (RECT *)&pData->Buffer;
				SetRect(&pr[pData->rdh.nCount], xs, y, xe, y + 1);
				if (xs < pData->rdh.rcBound.left)
					pData->rdh.rcBound.left = xs;
				if (y < pData->rdh.rcBound.top)
					pData->rdh.rcBound.top = y;
				if (xe > pData->rdh.rcBound.right)
					pData->rdh.rcBound.right = xe;
				if (y + 1 > pData->rdh.rcBound.bottom)
					pData->rdh.rcBound.bottom = y + 1;
				pData->rdh.nCount++;

				// On Windows98, ExtCreateRegion() may fail if the number of rectangles is too
				// large (ie: > 4000). Therefore, we have to create the region by multiple steps.
				//if (pData->rdh.nCount == 2000)
				//{
				//	HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
				//	if (hRgn)
				//	{
				//		CombineRgn(hRgn, hRgn, h, RGN_OR);
				//		DeleteObject(h);
				//	}
				//	else
				//		hRgn = h;
				//	pData->rdh.nCount = 0;
				//	SetRect(&pData->rdh.rcBound, MAXLONG, MAXLONG, 0, 0);
				//}
			}

			if (finished)
				break;

			// Create or extend the region with the remaining rectangles
			HRGN h = ExtCreateRegion(NULL, sizeof(RGNDATAHEADER) + (sizeof(RECT) * maxRects), pData);
			if (hRgn)
			{
				CombineRgn(hRgn, hRgn, h, RGN_OR);
				DeleteObject(h);
			}
			else
				hRgn = h;


		}
	}

	return hRgn;
}

void CreateAllResources(HBRUSH CGBrushes[])
{

	CGBrushes_out[SO_RED] = CreateSolidBrush(RGB(128, 0, 0));
	CGBrushes_out[SO_GREEN] = CreateSolidBrush(RGB(0, 128, 0));
	CGBrushes_out[SO_YELLOW] = CreateSolidBrush(RGB(255, 255, 0));
	CGBrushes[NEXTRED] = CreateSolidBrush(RGB(255, 0, 0));
	CGBrushes[PREGREEN] = CreateSolidBrush(RGB(0, 0, 255));
	CGBrushes[FIXEDGREEN] = CreateSolidBrush(RGB(0, 128, 0));
	CGBrushes[WAITGREEN] = CreateSolidBrush(RGB(0, 128, 128));
	CGBrushes[EXTENDGREEN] = CreateSolidBrush(RGB(0, 255, 0));
	CGBrushes[FREEEXGREEN] = CreateSolidBrush(RGB(255, 255, 255));
	CGBrushes[YELLOW] = CreateSolidBrush(RGB(255, 255, 0));
	CGBrushes[WAITRED] = CreateSolidBrush(RGB(128, 0, 0));
}

HWND CreateStatusBar(HWND hwndParent, int idStatus, HINSTANCE
	hinst, int cParts)
{
	HWND hwndStatus;
//	RECT rcClient;
//	HLOCAL hloc;
//	PINT paParts;
//	int i, nWidth;

	// Create the status bar.
	hwndStatus = CreateWindowEx(
		0,                       // no extended styles
		STATUSCLASSNAME,         // name of status bar class
		(PCTSTR)NULL,           // no text when first created
		SBARS_SIZEGRIP |         // includes a sizing grip
		WS_CHILD | WS_VISIBLE,   // creates a visible child window
		0, 0, 0, 0,              // ignores size and position
		hwndParent,              // handle to parent window
		(HMENU)idStatus,       // child window identifier
		hinst,                   // handle to application instance
		NULL);                   // no window creation data

								 // Get the coordinates of the parent window's client area.
								 //GetClientRect(hwndParent, &rcClient);
								 //
								 //// Allocate an array for holding the right edge coordinates.
								 //hloc = LocalAlloc(LHND, sizeof(int) * cParts);
								 //paParts = (PINT)LocalLock(hloc);
								 //
								 //// Calculate the right edge coordinate for each part, and
								 //// copy the coordinates to the array.
								 //nWidth = rcClient.right / cParts;
								 //int rightEdge = nWidth;
								 //for (i = 0; i < cParts; i++) {
								 //	paParts[i] = rightEdge;
								 //	rightEdge += nWidth;
								 //}
								 //
								 //// Tell the status bar to create the window parts.
								 //SendMessage(hwndStatus, SB_SETPARTS, (WPARAM)cParts, (LPARAM)
								 //	paParts);
								 //
								 //// Free the array, and return.
								 //LocalUnlock(hloc);
								 //LocalFree(hloc);
	return hwndStatus;
}

HWND CreateCoolToolbar(HWND hWndParent, HINSTANCE hInst)
{
	// Declare and initialize local constants.
	const int ImageListID = 0;
	const int numButtons = 6;
	const int bitmapSize = 16;
//	TBADDBITMAP buttonsBitMap;
//	COLORMAP colorMap;
//	DWORD backgroundColor;
	HWND hWndToolbar;
//	HBITMAP hbm;

	//const DWORD buttonStyles = BTNS_AUTOSIZE;
	const BYTE buttonStyles = (BTNS_AUTOSIZE | CCS_ADJUSTABLE | BTNS_CHECK);

	// Create the toolbar.
	hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
		WS_CHILD | TBSTYLE_WRAPABLE | TBSTYLE_FLAT, 0, 0, 0, 0,
		hWndParent, (HMENU)ID_TOOLBAR, hInst, NULL);

	if (hWndToolbar == NULL)
		return NULL;

	// Send the TB_BUTTONSTRUCTSIZE message, which is required for backward compatibility.
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_SETBUTTONSIZE, 0, MAKELPARAM(16, 16));
	SendMessage(hWndToolbar, TB_SETBITMAPSIZE, 0, MAKELPARAM(16, 16));

	// create and add imagelist


	HIMAGELIST hImgList = ImageList_LoadImage(hInst, MAKEINTRESOURCE(ID_TOOLBAR), 16, 16, CLR_DEFAULT, IMAGE_BITMAP, LR_LOADTRANSPARENT);
	SendMessage(hWndToolbar, TB_SETIMAGELIST, 0, (LPARAM)hImgList);


	//backgroundColor = GetSysColor(COLOR_BTNFACE);
	//colorMap.from = RGB(255, 255, 255);
	//colorMap.to = backgroundColor;
	//hbm = CreateMappedBitmap(hInst, (UINT_PTR)IDI_TOOLBAR, 0, &colorMap, 1);
	//buttonsBitMap.hInst = NULL;
	//buttonsBitMap.nID = (INT)hbm;
	//SendMessage(hWndToolbar, TB_ADDBITMAP, numButtons, (LPARAM)&buttonsBitMap);

	// Initialize button info.
	// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.

	TBBUTTON tbButtons[numButtons] =
	{
		{ 0, IDM_TIME_REALTIME, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, NULL },
		{ 1, IDM_TIME_LOWSPEED, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, NULL },
		{ 2, IDM_TIME_MIDSPEED, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, NULL },
		{ 3, IDM_TIME_HIGHSPEED, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, NULL },
		{ 0, 0, TBSTATE_ENABLED, TBSTYLE_SEP, (BYTE)0, 0L, (DWORD_PTR)NULL },
		{ 4, IDM_SIMULATION, TBSTATE_ENABLED, buttonStyles,{ 0 }, 0, NULL },

	};

	//	HWND track_bar = CreateWindowEx(NULL, TRACKBAR_CLASS, "Trackbar",
	//		WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS,
	//		80, 0, 200, 20, hWndToolbar, NULL, hInst, NULL);

	// Add buttons.
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

	// Resize the toolbar, and then show it.
	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);

	SendMessage(hWndToolbar, TB_CHECKBUTTON, (WPARAM)IDM_REALTIME, MAKELPARAM(iSpeed == SPEED_RT, 0));

	ShowWindow(hWndToolbar, TRUE);

	return hWndToolbar;
}