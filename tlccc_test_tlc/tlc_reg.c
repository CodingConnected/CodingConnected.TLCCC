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

static char running = TRUE;

/* TLCCC variables */
SIGNALGROUP signalgroups[SGMAX] = { 0 };
OUTGOING_SIGNAL outging_signals[OSMAX] = { 0 };
DETECTOR detectors[DMAX] = { 0 };
TIMER timers[TMMAX] = { 0 };
MODULE modules[MLMAX] = { 0 };
SWITCH switches[SWMAX] = { 0 };
PARAMETER parameters[PRMMAX] = { 0 };
MODULEMILL modulemill = { 0 };
CLOCK clock = { 0 };

#ifdef TLCCC_WIN32
    short SignalGroups_internal_state[SGMAX];
    short SignalGroups_internal_state_alt[SGMAX];
#endif

s_int16 applicatieprogramma(s_int16 state)
{
    
    if (state == CIF_INIT)
    {
        /* Initialize */
        application_init(signalgroups, detectors, outging_signals, &modulemill, modules, &clock);
    }
    else if(running == TRUE)
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
        Detectors_update(detectors, DMAX);
        if (CIF_PARM1WIJZPB)
        {
            // TODO
        }

        /* Update clock and timers */
        Clock_update(&clock);
        SignalGroups_timers_update(signalgroups, SGMAX, &clock);
        Detectors_timers_update(detectors, DMAX, &clock);
        Timers_update(timers, TMMAX, &clock);

        /* Update state */
        SignalGroups_requests(signalgroups, SGMAX);
        // TODO: update waiting green (later)
        SignalGroups_extending(signalgroups, SGMAX);
        // TODO: update free extending
        SignalGroups_update_conflicts(signalgroups, SGMAX);
        
        Modules_update_primary(&modulemill);
        //Modules_update_alternative(&modulemill, signalgroups, FCMAX);
        SignalGroups_state_update_ML(signalgroups, SGMAX, &CIF_GUSWIJZ);
        Modules_move_the_mill(&modulemill, signalgroups, SGMAX);

        Modules_update_segment_display(&modulemill, outging_signals, ossegm1, &CIF_GUSWIJZ);
        
        if (CIF_GUSWIJZ)
        {
            SignalGroups_state_out_update(signalgroups, SGMAX);
            Set_GUS(signalgroups, SGMAX, outging_signals, OSMAX- SGMAX);
        }

#ifdef TLCCC_WIN32
        /* Internal state to WIN32 environment */
        int i;
        for (i = 0; i < SGMAX; ++i)
        {
            SignalGroups_internal_state[i] = signalgroups[i].CycleState;
            SignalGroups_internal_state_alt[i] = signalgroups[i].ML_Alternative;
        }
#endif
        
        // TODO: check if we need to copy params from tlccc to outside buffers
    }

    return 0;
}

void application_exit(void)
{
    // Set running state to false, cause otherwise the application
    // will try to access freed memory if running at high speeds
    running = FALSE;

    // Free all allocated memory; good programming practice!
    SignalGroups_free(signalgroups, SGMAX);
    Detectors_free(detectors, DMAX);
    ModuleMill_free(&modulemill, MLMAX);
    Parameters_free(parameters, PRMMAX);
    Timers_free(timers, TMMAX);
    Switches_free(switches, SWMAX);
}