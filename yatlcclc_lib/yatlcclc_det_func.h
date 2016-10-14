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

#ifndef YATLCCLC_DETFUNC_H_INCLUDED
#define YATLCCLC_DETFUNC_H_INCLUDED

#include "yatlcclc_main.h"
#include "yatlcclc_fc_func.h"
#include "yatlcclc_timer_func.h"

void Detector_init(DETECTOR * detector, const char * code, short * cif_is_val, short type, short request, short extend, short tdbmax, short tdhmax, short togmax, short tbgmax);
void Detector_free(DETECTOR * detector);
void Detectors_free(DETECTOR detectors[]);
void Detectors_update(DETECTOR detectors[], short detector_count);
void Detector_update(DETECTOR * detector);
void Detectors_timers_update(DETECTOR detectors[], short detector_count, CLOCK * klok);
void Detector_timers_update(DETECTOR * detector, CLOCK * klok);

struct DETECTOR_STRUCT
{
	/* State */
	TIMER Timer_Occ;
	TIMER Timer_Gap;
	TIMER Timer_ErrorHi;
	TIMER Timer_ErrorLo;
	short * CIF_IS_value;
	short PresenceStart;
	short Presence;
	short PresenceEnd;
	short Occupied;
	short GapRunning;

	/* Settings */
	short Type;
	short Request;
	short Extend;

	/* Info */
	char * Code;
	PHASE * Phase;
};

#define DET_EXT_NONE    0
#define DET_EXT_HEADMAX 1
#define DET_EXT_MEASURE 2

#define DET_REQ_NONE      0
#define DET_REQ_YELLOW    1
#define DET_REQ_RED       2
#define DET_REQ_REDNONGAR 3

#endif // YATLCCLC_DETFUNC_H_INCLUDED