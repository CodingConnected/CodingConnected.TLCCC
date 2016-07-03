#include "yatlcclc_os_func.h"

void Outgoing_signal_init(OUTGOING_SIGNAL * os, const char * code, short index)
{
	os->Code = (char *)malloc((strlen(code) + 1) * sizeof(char));
	snprintf(os->Code, strlen(code) + 1, "%s", code);

	os->Index = index;
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

void Outgoing_signals_update_desired(OUTGOING_SIGNAL os[], short os_count)
{
	int i;
	for (i = 0; i < os_count; i++)
	{
		Outgoing_signal_update_desired(&os[i]);
	}
}
static void Outgoing_signal_update_desired(OUTGOING_SIGNAL * os)
{
	CIF_GUS[os->Index] = os->State_desired;
}

void Outgoing_signal_set_desired(OUTGOING_SIGNAL * os, short state_desired, short * cif_guswijz)
{
	os->State_desired = state_desired;
	*cif_guswijz = TRUE;
}