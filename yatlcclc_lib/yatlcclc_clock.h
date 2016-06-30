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

#ifndef YATLCCLC_KLOK_H_INCLUDED
#define YATLCCLC_KLOK_H_INCLUDED

#include "yatlcclc_main.h"
#include "CIF_INC.h"

#define TCOUNTERS_MAX 32767

void Clock_CIF_init(CLOCK * clock);
void Clock_update(CLOCK * clock);

struct CLOCK_STRUCT
{
	short TSecCounter;
	short TSecCounter_prev;
	short SecCounter;
	short SecCounter_prev;
	short Year;
	short Month;
	short Day;
	short DayType;
	short Hour;
	short Minute;
	short Second;

	short TE;
	short TS;
	short TM;
};

#endif // YATLCCLC_KLOK_H_INCLUDED