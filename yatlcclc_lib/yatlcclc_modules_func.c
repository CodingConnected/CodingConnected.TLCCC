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

#include "yatlcclc_modules_func.h"

void Module_init(MODULE * module, short index, char * code, short phases_count, ...)
{
	module->Code = (char *)malloc((strlen(code) + 1) * sizeof(char));
	snprintf(module->Code, strlen(code) + 1, "%s", code);

	if (phases_count > 0)
	{
		va_list a_list;
		int i;

		module->Phases = malloc(phases_count * sizeof(PHASE *));
		va_start(a_list, phases_count);

		module->Phases_count = phases_count;
		module->Index = index;

		for (i = 0; i < phases_count; ++i)
		{
			PHASE * p = va_arg(a_list, PHASE *);
			module->Phases[i] = p;
			if (p->Modules_primary_count < PRIMAIRY_REAL_MAX)
			{
				p->Module_primary[p->Modules_primary_count] = module;
				p->Modules_primary_count++;
			}
		}
	}
}

void ModuleMill_init(MODULEMILL * modulemill, MODULE modules[], short modules_count, short waiting_module)
{
	if (modules_count <= 0 || waiting_module >= modules_count)
		return;

	modules[0].IsActive = TRUE;
	modulemill->ActiveModule = &modules[0];
	modulemill->ActiveModule_index = 0;

	modulemill->WaitingModule = &modules[waiting_module];
	modulemill->WaitingModule_index = waiting_module;

	modulemill->ModuleStart = TRUE;
	modulemill->Modules_count = modules_count;
}

void Modules_set_alternative_space_default(PHASE phases[], short phases_count, short space)
{
	int i;
	for (i = 0; i < phases_count; ++i)
	{
		phases[i].ML_Alt_Space = space;
	}
}

void Modules_update_primary(MODULEMILL * modulemill, MODULE modules[], short modules_count)
{
	int i = modulemill->ActiveModule_index;
	int k;
	char ModGreenStarted = FALSE;
	
	/* Determine if the module has really begun: one or more phases green */
	for (k = 0; k < modules[i].Phases_count; ++k)
	{
		if (modules[i].Phases[k]->State_out != SO_RED)
		{
			ModGreenStarted = TRUE;
			break;
		}
	}

	/* Set phases ML primary realisation state */
	for (k = 0; k < modules[i].Phases_count; ++k)
	{
		/* Set primary realisation: phase may realize */
		if ((modules[i].Phases[k]->Request) &&
			!(modules[i].Phases[k]->ML_Primary_done))
		{
			modules[i].Phases[k]->ML_Primary = TRUE;
		}
		/* Set primary realisation done if phase is in primary green */
		if ((modules[i].Phases[k]->State_out == SO_GREEN) &&
			(modules[i].Phases[k]->ML_Primary) &&
			!(modules[i].Phases[k]->ML_Primary_done))
		{
			modules[i].Phases[k]->ML_Primary_done |= PR_REAL;
		}
	}

	/* Set phases ML skipped primary realisation */
	if (ModGreenStarted)
	{
		for (k = 0; k < modules[i].Phases_count; ++k)
		{
			if (!modules[i].Phases[k]->ML_Primary_done && !modules[i].Phases[k]->Request)
			{
				int l, m = TRUE;
				for (l = 0; l < modules[i].Phases_count; ++l)
				{
					if (!modules[i].Phases[k]->ML_Primary_done && modules[i].Phases[k]->Request)
					{
						m = FALSE;
						break;
					}
				}
				if (m)
				{
					modules[i].Phases[k]->ML_Primary_done |= PR_SKIP;
				}
			}
		}
	}
}

void Modules_update_alternative(MODULEMILL * modulemill, MODULE modules[], short modules_count, PHASE phases[], short phases_count)
{
	int i, k, l;
	for (k = 0; k < phases_count; ++k)
	{
		if (phases[k].Request && !phases[k].ML_Primary && !phases[k].HasConflict)
		{
			phases[k].ML_Alternative |= AR_REAL_POSSIBLE;
		}
	}
	/* Check for remaining space */
	for (k = 0; k < phases_count; ++k)
	{
		if (phases[k].ML_Alternative & AR_REAL_POSSIBLE)
		{
			/* TODO: needs more intelligence: take into account clearing times, yellow, etc */
			char alt = FALSE;
			for (l = 0; l < phases_count; ++l)
			{
				/* Skip conflicts */
				for (i = 0; i < phases[k].Conflict_count; ++i)
				{
					if (phases[k].Conflicts[i]->ConflictPhase->Index == phases[l].Index)
						continue;
				}
				/* Check space */
				if (phases[l].ML_Primary_active &&
					(phases[l].CycleState > NEXTRED && phases[l].CycleState < EXTENDGREEN ||
					 phases[l].CycleState == EXTENDGREEN && phases[l].Timer_GE.Remaining > phases[k].ML_Alt_Space))
				{
					alt = TRUE;
					break;
				}
			}
			if (!alt)
				phases[k].ML_Alternative &= ~AR_REAL_POSSIBLE;
		}
	}
	/* Check longer waiting conflicting alternatives */
	for (k = 0; k < phases_count; ++k)
	{
		if (phases[k].ML_Alternative & AR_REAL_POSSIBLE)
		{
			for (l = 0; l < phases[k].Conflict_count; ++l)
			{
				if (phases[k].Conflicts[l]->ConflictPhase->Module_primary[0]->Index == modulemill->ActiveModule_index &&
					phases[k].Conflicts[l]->ConflictPhase->ML_Primary && !phases[k].Conflicts[l]->ConflictPhase->ML_Primary_done ||
					phases[k].Conflicts[l]->ConflictPhase->ML_Alternative && phases[k].Conflicts[l]->ConflictPhase->Timer_PG_act > phases[k].Timer_PG_act)
					phases[k].ML_Alternative &= ~AR_REAL_POSSIBLE;
			}
		}
	}
}

void Modules_move_the_mill(MODULEMILL * modulemill, MODULE modules[], short modules_count, PHASE phases[], short phases_count)
{
	int i = modulemill->ActiveModule_index;
	int k;
	modulemill->ModuleStart = FALSE;

	/* Set current module state */
	modules[i].AllRealised = TRUE;
	for (k = 0; k < modules[i].Phases_count; ++k)
	{
		if (modules[i].Phases[k]->Request && !modules[i].Phases[k]->ML_Primary_done)
		{
			modules[i].AllRealised = FALSE;
			break;
		}
	}

	/* Move the mill */
	if (modules[i].AllRealised)
	{
		int wait = TRUE;

		/* Reset flags for the current module */
		for (k = 0; k < modules[i].Phases_count; ++k)
		{
			modules[i].Phases[k]->ML_Primary = FALSE;
			modules[i].Phases[k]->ML_Primary_done = FALSE;
		}

		/* Check if we wait in the waiting module */
		if (modulemill->ActiveModule_index == modulemill->WaitingModule_index)
		{
			for (k = 0; k < phases_count; ++k)
			{
				if (phases[k].Request)
				{
					wait = FALSE;
				}
			}
		}
		else
		{
			wait = FALSE;
		}

		/* Move the mill forward */
		if (!wait)
		{
			modulemill->ActiveModule_index++;
			if (modulemill->ActiveModule_index >= modulemill->Modules_count)
				modulemill->ActiveModule_index = 0;
			modulemill->ActiveModule = &modules[modulemill->ActiveModule_index];
			modulemill->ModuleStart = TRUE;
		}
	}
}

void Modules_update_segment_display(MODULEMILL * modulemill, OUTGOING_SIGNAL os[], short index, short * cif_guswijz)
{
	switch (modulemill->ActiveModule_index)
	{
	case 1:
		Outgoing_signal_set_desired(&os[index + 0], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 1], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 2], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 3], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 4], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 5], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 6], 0, cif_guswijz);
		break;
	case 2:
		Outgoing_signal_set_desired(&os[index + 0], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 1], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 2], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 3], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 4], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 5], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 6], 1, cif_guswijz);
		break;
	case 3:
		Outgoing_signal_set_desired(&os[index + 0], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 1], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 2], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 3], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 4], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 5], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 6], 1, cif_guswijz);
		break;
	case 4:
		Outgoing_signal_set_desired(&os[index + 0], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 1], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 2], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 3], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 4], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 5], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 6], 0, cif_guswijz);
		break;
	default:
		Outgoing_signal_set_desired(&os[index + 0], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 1], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 2], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 3], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 4], 1, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 5], 0, cif_guswijz);
		Outgoing_signal_set_desired(&os[index + 6], 1, cif_guswijz);
		break;
	}
}