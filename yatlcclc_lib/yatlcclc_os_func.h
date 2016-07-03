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

#ifndef YATLCCLC_OSFUNC_H_INCLUDED
#define YATLCCLC_OSFUNC_H_INCLUDED

#include "yatlcclc_main.h"

void Outgoing_signal_init(OUTGOING_SIGNAL * os, const char * code, short index);
void Outgoing_signals_update_real(OUTGOING_SIGNAL os[], short os_count);
static void Outgoing_signal_update_real(OUTGOING_SIGNAL * os);
void Outgoing_signals_update_desired(OUTGOING_SIGNAL os[], short os_count);
static void Outgoing_signal_update_desired(OUTGOING_SIGNAL * os);
void Outgoing_signal_set_desired(OUTGOING_SIGNAL * os, short state_desired, short * cif_guswijz);

struct OUTGOING_SIGNAL_STRUCT
{
	/* Outgoing signal state */
	short State_desired;
	short State_real;

	/* Outgoing signal info */
	char * Code;
	short Index;
};

#endif /* YATLCCLC_OSFUNC_H_INCLUDED */