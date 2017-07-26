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

#include <tchar.h>
#include <windows.h>

/* Window class */
#define BITMAPPER_WC   _T("BitmapperControl")

/* Register/unregister the window class */
void BitmapperControlRegister(void);
void BitmapperControlUnregister(void);
void BitmapperSetFilename(LPCSTR filename);

#include "tlccc_win32.h"
#include "applfunc.h"

//extern "C"
//{
    extern short X_is[];
    extern short X_us[];
    extern short Y_is[];
    extern short Y_us[];
//}

extern HBRUSH CGBrushes[];
extern HBRUSH CGBrushes_alt[];
extern HBRUSH CGBrushes_out[];
extern struct IS_STRUCT * inputs;
//extern "C"
//{
    extern short SignalGroups_internal_state[];
    extern short SignalGroups_internal_state_alt[];
//}
extern char bInternalState;
