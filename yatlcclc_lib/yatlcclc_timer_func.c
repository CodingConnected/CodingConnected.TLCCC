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

#include "yatlcclc_timer_func.h"
#include "yatlcclc_clock.h"

void Timer_init(TIMER * timer, char * code, short maximum, short t_type)
{
	timer->Code = (char *)malloc((strlen(code) + 1) * sizeof(char));
	snprintf(timer->Code, strlen(code) + 1, "%s", code);

	timer->Maximum = maximum;
	timer->TimeType = t_type;
}

void Timers_update(TIMER timers[], int timers_count, CLOCK * clock)
{
	int i;
	for (i = 0; i < timers_count; ++i)
	{
		Timer_update(&timers[i], clock);
	}
}

void Timer_update(TIMER * timer, CLOCK * clock)
{
	timer->Started = timer->Ended = FALSE;

	if (timer->Start)
	{
		timer->Start = FALSE;
		timer->Active = TRUE;
		timer->Started = TRUE;
	}
	if (timer->Restart)
	{
		timer->Restart = FALSE;
		timer->Current = 0;
		timer->Active = TRUE;
		timer->Started = TRUE;
	}
	if (timer->Stop)
	{
		timer->Active = FALSE;
		timer->Stop = FALSE;
	}
	if (timer->Active)
	{
		if (clock->TE && timer->TimeType == TE_type)
		{
			timer->Current += clock->TE;
		}
		if (clock->TS && timer->TimeType == TS_type)
		{
			timer->Current += clock->TS;
		}
		if (clock->TM && timer->TimeType == TM_type)
		{
			timer->Current += clock->TM;
		}
	}
	if (timer->Active && timer->Current >= timer->Maximum)
	{
		timer->Ended = TRUE;
		timer->Stop = TRUE;
	}
}