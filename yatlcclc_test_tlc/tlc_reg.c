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

#define CIF_PUBLIC
#define NO_CIF_MON
#include "tlc_sys.h"

/* YATLCCLC variables */
PHASE phases[FCMAX] = { 0 };
OUTGOING_SIGNAL outging_signals[USMAX] = { 0 };
DETECTOR detectors[DPMAX] = { 0 };
TIMER timers[TMMAX] = { 0 };
MODULE modules[MLMAX] = { 0 };
MODULEMILL modulemill = { 0 };
CLOCK clock = { 0 };

#ifdef YATLCCLC_WIN32
	short Phases_internal_state[FCMAX];
	short Phases_internal_state_alt[FCMAX];
#endif

/* Variables to exchange info externaly */
short CT_max[FCMAX * FCMAX];

s_int16 applicatieprogramma(s_int16 state)
{
	
	if (state == CIF_INIT)
	{		
		/* Initialize */
		application_init(phases, detectors, outging_signals, CT_max, &modulemill, modules, &clock);
	}
	else
	{
		/* Read data from interface */
		if (CIF_ISWIJZ)
		{
			CIF_ISWIJZ = FALSE;
		}
		if (CIF_WUSWIJZ)
		{
			CIF_WUSWIJZ = FALSE;
		}
		// TODO: process other inputs
		Detectors_update(detectors, DPMAX);
		if (CIF_PARM1WIJZPB)
		{
			// TODO
		}

		/* Update clock and timers */
		Clock_update(&clock);
		Phases_timers_update(phases, FCMAX, &clock);
		Detectors_timers_update(detectors, DPMAX, &clock);
		Timers_update(timers, TMMAX, &clock);

		/* Update state */
		Phases_requests(phases, FCMAX);
		// TODO: update waiting green (later)
		Phases_extending(phases, FCMAX);
		// TODO: update free extending
		Phases_update_conflicts(phases, FCMAX);
		
		Modules_update_primary(&modulemill, modules, MLMAX);
		Modules_update_alternative(&modulemill, modules, MLMAX, phases, FCMAX);
		Phases_state_update_ML(phases, FCMAX, &CIF_GUSWIJZ);
		Modules_move_the_mill(&modulemill, modules, MLMAX, phases, FCMAX);

		Modules_update_segment_display(&modulemill, outging_signals, ossegm1, &CIF_GUSWIJZ);
		
		if (CIF_GUSWIJZ)
		{
			Phases_state_out_update(phases, FCMAX);
			Set_GUS(phases, FCMAX, outging_signals, USMAX-FCMAX);
		}

#ifdef YATLCCLC_WIN32
		/* Internal state to WIN32 environment */
		int i;
		for (i = 0; i < FCMAX; ++i)
		{
			Phases_internal_state[i] = phases[i].CycleState;
			Phases_internal_state_alt[i] = phases[i].ML_Alternative;
		}
#endif
		
		// TODO: check if we need to copy params from yatlcclc to outside buffers
	}

	return 0;
}