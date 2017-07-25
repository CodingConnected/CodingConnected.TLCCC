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

#ifndef TLCCC_MAIN_H_INCLUDED
#define TLCCC_MAIN_H_INCLUDED

#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <string.h>     /* spint, etc */
#include <stdarg.h>     /* va_list, va_start, va_arg, va_end */

#ifdef CIF_PUBLIC 
    #define CIF_AANT_IS_D  DMAX
    #define CIF_AANT_IS_OV ISMAX-DMAX
    #define CIF_AANT_US_FC SGMAX
    #define CIF_AANT_US_OV OSMAX-SGMAX
    
    #define CIF_MAX_IBER 1024
    #define CIF_MAX_UBER 4096
    #define CIF_AANT_DSI 36
    #define CIF_AANT_GPS 5
    #define CIF_AANT_WPS 5
    #define CIF_AANT_KLOK 9
    #define CIF_AANT_PARM1 PRMMAX
    #define CIF_AANT_PARM2 1
#endif

#include "CIF_INC.h"

#define SIGNALGROUP struct SIGNALGROUP_STRUCT 
#define DETECTOR struct DETECTOR_STRUCT 
#define CLOCK struct CLOCK_STRUCT
#define TIMER struct TIMER_STRUCT
#define SWITCH struct SWITCH_STRUCT
#define PARAMETER struct PARAMETER_STRUCT
#define MODULE struct MODULE_STRUCT
#define MODULEMILL struct MODULEMILL_STRUCT
#define CONFLICT struct CONFLICT_STRUCT
#define OUTGOING_SIGNAL struct OUTGOING_SIGNAL_STRUCT

#define FALSE 0
#define TRUE  1

enum DetectorTypes { D_HEAD, D_LONG, D_AWAY, D_JAM, D_BUTTON, D_OTHER, DETTYPE_MAX };
enum SignalGroupStates { WAITRED, NEXTRED, PREGREEN, FIXEDGREEN, WAITGREEN, EXTENDGREEN, FREEEXGREEN, YELLOW, STATE_MAX };
enum SignalGroupStatesOut { SO_RED, SO_GREEN, SO_YELLOW, STATE_OUT_MAX};
enum TimeTypes { TE_type, TS_type, TM_type };

#endif // TLCCC_MAIN_H_INCLUDED
