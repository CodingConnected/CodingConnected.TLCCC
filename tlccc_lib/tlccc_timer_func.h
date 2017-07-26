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

#ifndef TLCCC_TIMERFUNC_H_INCLUDED
#define TLCCC_TIMERFUNC_H_INCLUDED

#include "tlccc_main.h"

void Timer_init(TIMER * timer, char * code, short maximum, short t_type);
void Timer_free(TIMER * timer);
void Timers_free(TIMER timers[], short timers_count);
void Timers_update(TIMER timers[], int timers_count, CLOCK * klok);
void Timer_update(TIMER * timer, CLOCK * klok);

struct TIMER_STRUCT
{
    /* Timer fixed data*/
    short TimeType;
    char * Code;
    
    /* Timer state (read only) */
    short Maximum;   /* Timer max value */
    short Current;   /* Timer current value */
    short Remaining; /* Timer current value */
    char Active;     /* Timer is active/inactive */
    char Started;    /* Timer has started */
    char Ended;      /* Timer has ended after reaching maximum */

    /* Instructions */
    char Start;    /* Set to TRUE to start the timer */
    char Restart;  /* Set to TRUE to restart the timer */
    char Stop;     /* Set to TRUE to stop (abort) the timer */
};

#endif // TLCCC_TIMERFUNC_H_INCLUDED