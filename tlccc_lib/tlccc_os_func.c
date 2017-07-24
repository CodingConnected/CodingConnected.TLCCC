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

#include "tlccc_os_func.h"

void Outgoing_signal_init(OUTGOING_SIGNAL * os, const char * code, short index)
{
	os->Code = (char *)malloc((strlen(code) + 1) * sizeof(char));
	snprintf(os->Code, strlen(code) + 1, "%s", code);

	os->Index = index;
}

void Outgoing_signal_free(OUTGOING_SIGNAL * os)
{
	if (os->Code != NULL)
		free(os->Code);
}

void Outgoing_signals_free(OUTGOING_SIGNAL os[], short os_count)
{
	int i;
	for (i = 0; i < os_count; ++i)
	{
		Outgoing_signal_free(&os[i]);
	}
}

void Outgoing_signals_update_real(OUTGOING_SIGNAL os[], short os_count)
{
	int i;
	for (i = 0; i < os_count; i++)
	{
		Outgoing_signal_update_real(&os[i]);
	}
}
static void Outgoing_signal_update_real(OUTGOING_SIGNAL * os)
{
	os->State_real = CIF_WUS[os->Index];
}

void Outgoing_signal_set_desired(OUTGOING_SIGNAL * os, short state_desired, short * cif_guswijz)
{
	os->State_desired = state_desired;
	*cif_guswijz = TRUE;
}