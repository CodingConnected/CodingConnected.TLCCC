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

#include "tlccc_clock.h"

void Clock_CIF_init(CLOCK * clock)
{ 
}

void Clock_update(CLOCK * clock)
{
	/* Update all values */
	clock->TSecCounter = CIF_KLOK[CIF_TSEC_TELLER];
	clock->SecCounter = CIF_KLOK[CIF_SEC_TELLER];
	clock->Year = CIF_KLOK[CIF_JAAR];
	clock->Month = CIF_KLOK[CIF_MAAND];
	clock->Day = CIF_KLOK[CIF_DAG];
	clock->DayType = CIF_KLOK[CIF_DAGSOORT];
	clock->Hour = CIF_KLOK[CIF_UUR];
	clock->Minute = CIF_KLOK[CIF_MINUUT];
	clock->Second = CIF_KLOK[CIF_SECONDE];

	/* Loop TE teller */
	if (clock->TSecCounter > TCOUNTERS_MAX) clock->TSecCounter -= TCOUNTERS_MAX;
	if (clock->TSecCounter < 0) clock->TSecCounter += TCOUNTERS_MAX;
	if (clock->TSecCounter < clock->TSecCounter_prev)
		clock->TSecCounter_prev -= TCOUNTERS_MAX;

	/* Set TE */
	clock->TE = clock->TSecCounter - clock->TSecCounter_prev;
	clock->TSecCounter_prev = clock->TSecCounter;

	/* Loop TS teller */
	if (clock->SecCounter > TCOUNTERS_MAX) clock->SecCounter -= TCOUNTERS_MAX;
	if (clock->SecCounter < 0) clock->SecCounter += TCOUNTERS_MAX;
	if (clock->SecCounter < clock->SecCounter_prev)
		clock->SecCounter_prev -= TCOUNTERS_MAX;

	/* Set TS */
	clock->TS = clock->SecCounter - clock->SecCounter_prev;
	clock->SecCounter_prev = clock->SecCounter;
}
