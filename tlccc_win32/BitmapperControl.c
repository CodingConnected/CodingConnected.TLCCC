/*
Copyright (C) 2016-2025 CodingConnected e. U., Menno van der Woude

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

#include "BitmapperControl.h"

static LPCSTR lpcstrBitmapFileName;
static HBITMAP hBitmap;
static HBITMAP hBufferBitmap;
static BITMAP Bitmap;
static HDC Hdc;
static HDC memHdc;
static double dScaling = 1.0;

void BitmapperSetFilename(LPCSTR filename)
{
    lpcstrBitmapFileName = filename;
}

static void BitmapperControlPaint(HWND hWnd, int fcmax, int dpmax)
{
    PAINTSTRUCT ps;
    HDC hdc;

    for (int i = 0; i < CIF_PB_AANT_US_FC; i++)
    {
        if (bInternalState)
        {
            if (SignalGroups_internal_state[i] < STATE_MAX)
            {
                if (SignalGroups_internal_state_alt[i])
                    SelectObject(memHdc, CGBrushes_alt[SignalGroups_internal_state[i]]);
                else
                    SelectObject(memHdc, CGBrushes[SignalGroups_internal_state[i]]);
            }
            ExtFloodFill(memHdc, X_us[i], Y_us[i], 0x000000, FLOODFILLBORDER);
        }
        else
        {
            if (CIF_GUS[i] < STATE_OUT_MAX)
                SelectObject(memHdc, CGBrushes_out[CIF_GUS[i]]);
            ExtFloodFill(memHdc, X_us[i], Y_us[i], 0x000000, FLOODFILLBORDER);
        }
    }

    for (int i = 0; i < CIF_PB_AANT_US_OV; i++)
    {
        if (CIF_GUS[CIF_PB_AANT_US_FC + i] < STATE_MAX)
        {
            if(CIF_GUS[CIF_PB_AANT_US_FC + i])
                SelectObject(memHdc, CGBrushes[EXTENDGREEN]);
            else
                SelectObject(memHdc, CGBrushes[WAITRED]);

        }
        ExtFloodFill(memHdc, X_us[CIF_PB_AANT_US_FC + i], Y_us[CIF_PB_AANT_US_FC + i], 0x000000, FLOODFILLBORDER);
    }

    for (int i = 0; i < CIF_PB_AANT_IS_D; i++)
    {
        if (CIF_IS[i] == CIF_DET_BEZET)
        {
            SetDCBrushColor(memHdc, RGB(0, 255, 255));
            FillRgn(memHdc, inputs[i].hRegion, (HBRUSH)GetStockObject(DC_BRUSH));
        }
        else
        {
            SetDCBrushColor(memHdc, RGB(192, 192, 192));
            FillRgn(memHdc, inputs[i].hRegion, (HBRUSH)GetStockObject(DC_BRUSH));
        }
    }

    hdc = BeginPaint(hWnd, &ps);
    StretchBlt(hdc, 0, 0, (int)((double)Bitmap.bmWidth * dScaling), (int)((double)Bitmap.bmHeight * dScaling), memHdc, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, SRCCOPY);
    //BitBlt(hdc, 0, 0, Bitmap.bmWidth, Bitmap.bmHeight, memHdc, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
}



static LRESULT CALLBACK BitmapperControlWinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_CREATE:
        hBitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)lpcstrBitmapFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (!hBitmap)
        {
            MessageBox(hWnd, TEXT("Bitmap was not found"), TEXT("Bitmap not found"), MB_OK);
            SendMessage(hWnd, WM_CLOSE, (WPARAM)NULL, (LPARAM)NULL);
        }
        GetObject(hBitmap, sizeof(BITMAP), (LPVOID)&Bitmap);
        
        Hdc = GetDC(hWnd);
        memHdc = CreateCompatibleDC(Hdc);
        hBufferBitmap = CreateCompatibleBitmap(Hdc, Bitmap.bmWidth, Bitmap.bmHeight);

        //inputs = new struct IS_STRUCT[CIF_PB_AANT_IS_D];
        // TODO free!!!
        inputs = (struct IS_STRUCT *)malloc(sizeof(struct IS_STRUCT) * CIF_PB_AANT_IS_D);

        SelectObject(memHdc, hBitmap);
        for (int i = 0; i < CIF_PB_AANT_IS_D; i++)
        {
            int x = X_is[i];
            int y = Y_is[i];
            COLORREF cr = GetPixel(memHdc, x, y);
            while (1)
            {
                if (x > 0)
                {
                    // go left
                    COLORREF cr2 = GetPixel(memHdc, x - 1, y);
                    // if not same, check y
                    if (cr != cr2)
                    {
                        if (y > 0)
                        {
                            // go up
                            cr2 = GetPixel(memHdc, x, y - 1);
                            // if not same, found end
                            if (cr != cr2)
                            {
                                break;
                            }
                            else
                            {
                                --y;
                            }
                        }
                        // y is 0, found end
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        --x;
                    }
                }
                else
                {
                    // check y
                    if (y > 0)
                    {
                        // go up
                        COLORREF cr2 = GetPixel(memHdc, x, y - 1);
                        // if not same, found end
                        if (cr != cr2)
                        {
                            break;
                        }
                        else
                        {
                            --y;
                        }
                    }
                    // y is 0, found end (top left)
                    else
                    {
                        break;
                    }
                }
            }
            cr = GetPixel(memHdc, x, y);
            inputs[i].hRegion = BitmapToRegion(memHdc, cr, x, y);
            inputs[i].iIndex = i;
        }

        return 0;
    case WM_SIZE:
        dScaling = ((double)(HIWORD(lParam))) / ((double)(Bitmap.bmHeight));
        SetWindowPos(hWnd, HWND_TOP, 0, 0, LOWORD(lParam), (int)(dScaling * (double)Bitmap.bmHeight), SWP_NOMOVE);
        InvalidateRect(hWnd, NULL, FALSE);
        return 0;

    case WM_LBUTTONDOWN:
    {
        //POINT pt;
        //GetCursorPos(&pt);
        //int mX = pt.x;
        //int mY = pt.y;

        int xPos = (int)((double)LOWORD(lParam) / dScaling);
        int yPos = (int)((double)HIWORD(lParam) / dScaling);

        for (int i = 0; i < CIF_PB_AANT_IS_D; i++)
        {
            if (PtInRegion(inputs[i].hRegion, xPos, yPos) != 0)
            {
                CIF_IS[i] = CIF_IS[i] != 0 ? 0 : 1;
                CIF_ISWIJZ = TRUE;
                break;
            }
        }
    }
    break;

    case WM_PAINT:
        BitmapperControlPaint(hWnd, CIF_PB_AANT_US_FC, CIF_PB_AANT_IS_D);
        return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void BitmapperControlRegister(void)
{
    WNDCLASS wc = { 0 };

    wc.style = CS_GLOBALCLASS | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = BitmapperControlWinProc;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = BITMAPPER_WC;
    RegisterClass(&wc);
}

void BitmapperControlUnregister(void)
{
    UnregisterClass(BITMAPPER_WC, NULL);
}