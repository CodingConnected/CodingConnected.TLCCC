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

#include "yatlcclc_fc_func.h"

void Phase_init(PHASE * phase, const char * code, short index, short tggmax, short tgfmax, short tgemax, short tyemax, short trgmax, short headmax)
{
	char temp[128];

	phase->Code = (char *)malloc((strlen(code) + 1) * sizeof(char));
	snprintf(phase->Code, strlen(code) + 1, "%s", code);

	phase->Index = index;

	snprintf(temp, 128, "TGG%s", phase->Code);
	Timer_init(&phase->Timer_GG, temp, tggmax, TE_type);
	snprintf(temp, 128, "TGF%s", phase->Code);
	Timer_init(&phase->Timer_GF, temp, tgfmax, TE_type);
	snprintf(temp, 128, "TGE%s", phase->Code);
	Timer_init(&phase->Timer_GE, temp, tgemax, TE_type);
	snprintf(temp, 128, "TYE%s", phase->Code);
	Timer_init(&phase->Timer_YE, temp, tyemax, TE_type);
	snprintf(temp, 128, "TRG%s", phase->Code);
	Timer_init(&phase->Timer_RG, temp, trgmax, TE_type);

	snprintf(temp, 128, "THM%s", phase->Code);
	Timer_init(&phase->Timer_HeadMax, temp, headmax, TE_type);

	phase->Timer_PG_act = 0;

	phase->CycleState = WAITRED;
	phase->Timer_RG.Restart = TRUE;
	phase->State_out = SO_RED;
}

void Phase_free(PHASE * phase, short phases_count)
{
	int j = 0;

	if (phase->Code != NULL)
		free(phase->Code);

	Timer_free(&phase->Timer_GG);
	Timer_free(&phase->Timer_GF);
	Timer_free(&phase->Timer_GE);
	Timer_free(&phase->Timer_YE);
	Timer_free(&phase->Timer_RG);
	
	if (phase->Detectors != NULL)
		free(phase->Detectors);

	if (phase->Conflicts != NULL)
	{
		for (j = 0; j < phase->Conflict_count; ++j)
		{
			if (phase->Conflicts[j] != NULL)
			{
				TIMER t = (phase->Conflicts[j]->Timer_clearing);
				Timer_free(&(phase->Conflicts[j]->Timer_clearing));
				free(phase->Conflicts[j]);
			}
		}
		free(phase->Conflicts);
	}
}

void Phases_free(PHASE phases[], short phases_count)
{
	int j = 0;

	for (j = 0; j < phases_count; ++j)
	{
		Phase_free(&phases[j], phases_count);
	}
}

void Phase_add_detectors(PHASE * phase, short detectors_count, ...)
{
	if (detectors_count > 0)
	{
		va_list a_list;
		int i;

		phase->Detectors_count = detectors_count;
		phase->Detectors = (DETECTOR **)malloc(detectors_count * sizeof(DETECTOR *));
		va_start(a_list, detectors_count);

		for (i = 0; i < detectors_count; ++i)
		{
			DETECTOR * d = va_arg(a_list, DETECTOR *);
			phase->Detectors[i] = d;
			d->Phase = phase;
		}
	}
}

void Phase_conflict_init(short phc1, short phc2, short conflictstable[], short phases_count, short clearingtime)
{
	conflictstable[phc1 + phc2 * phases_count] = clearingtime;
}

void Phases_set_conflict_pointers(PHASE phases[], short phases_count, short conflictstable[])
{
	int i, j, k;
	char temp[128];
	for (i = 0; i < phases_count; ++i)
	{
		for (j = 0; j < phases_count; ++j)
		{
			if (conflictstable[i + j * phases_count] != -1)
			{
				phases[i].Conflict_count++;
			}
		}
		phases[i].Conflicts = (CONFLICT **)malloc(phases[i].Conflict_count * sizeof(CONFLICT *));
		k = 0;
		for (j = 0; j < phases_count; ++j)
		{
			if (conflictstable[i + j * phases_count] != -1)
			{
				phases[i].Conflicts[k] = (CONFLICT *)malloc(sizeof(CONFLICT));
				phases[i].Conflicts[k]->ConflictPhase = &phases[j];
				snprintf(temp, 128, "TO%s%s", phases[i].Code, phases[j].Code);
				Timer_init(&phases[i].Conflicts[k]->Timer_clearing, temp, conflictstable[i + j * phases_count], TE_type);
				k++;
			}
		}
	}
}

void Phases_timers_update(PHASE phases[], short phases_count, CLOCK * klok)
{
	int i;
	for (i = 0; i < phases_count; ++i)
	{
		Phase_timers_update(&phases[i], klok);
	}
}

void Phase_timers_update(PHASE * phase, CLOCK * clock)
{
	int i;
	Timer_update(&phase->Timer_GG, clock);
	Timer_update(&phase->Timer_GF, clock);
	Timer_update(&phase->Timer_GE, clock);
	Timer_update(&phase->Timer_YE, clock);
	Timer_update(&phase->Timer_RG, clock);
	Timer_update(&phase->Timer_HeadMax, clock);
	for (i = 0; i < phase->Conflict_count; ++i)
	{
		Timer_update(&phase->Conflicts[i]->Timer_clearing, clock);
	}

	if (clock->TS && phase->Request && phase->State_out != SO_GREEN)
	{
		phase->Timer_PG_act += clock->TS;
	}
}

void Phases_state_update_ML(PHASE phases[], short phases_count, short * cif_guswijz)
{
	int i, j;
	for (i = 0; i < phases_count; ++i)
	{
		phases[i].StartGreen = FALSE;

		switch (phases[i].CycleState)
		{
		case WAITRED:
			if (!(phases[i].Timer_RG.Restart || phases[i].Timer_RG.Active) && phases[i].Request)
			{
				if (phases[i].ML_Primary && !phases[i].ML_Primary_done)
				{
					phases[i].CycleState = NEXTRED;
					phases[i].ML_Primary_active = TRUE;
					*cif_guswijz = TRUE;
					// TODO: set start end states ---> ALSO BELOW...
					break;
				}
				else if (phases[i].ML_Alternative)
				{
					phases[i].CycleState = NEXTRED;
					*cif_guswijz = TRUE;
				}
			}
			break;
		case NEXTRED:
			if (!phases[i].HasConflict)
			{
				phases[i].CycleState = PREGREEN;
				*cif_guswijz = TRUE;
			}
			break;
		case PREGREEN:
			// placeholder: move to next 
			phases[i].CycleState = FIXEDGREEN;
			phases[i].StartGreen = TRUE;
			phases[i].Timer_GF.Restart = TRUE;
			phases[i].Timer_HeadMax.Restart = TRUE;
			*cif_guswijz = TRUE;
			break;
		case FIXEDGREEN:
			if (phases[i].Timer_GF.Ended)
			{
				phases[i].CycleState = WAITGREEN;
				*cif_guswijz = TRUE;
			}
			break;
		case WAITGREEN:
			// placeholder: move to next 
			phases[i].CycleState = EXTENDGREEN;
			*cif_guswijz = TRUE;
			phases[i].Timer_GE.Restart = TRUE;
			break;
		case EXTENDGREEN:
			if (phases[i].Timer_GE.Ended || !phases[i].Extend)
			{
				phases[i].CycleState = FREEEXGREEN;
				phases[i].ML_Primary_active = TRUE;
				*cif_guswijz = TRUE;
			}
			break;
		case FREEEXGREEN:
			// placeholder: move to next 
			phases[i].CycleState = YELLOW;
			phases[i].Timer_YE.Restart = TRUE;
			*cif_guswijz = TRUE;
			break;
		case YELLOW:
			if (phases[i].Timer_YE.Ended)
			{
				phases[i].CycleState = WAITRED;
				*cif_guswijz = TRUE;
				phases[i].Timer_RG.Restart = TRUE;
				/* Restart clearing timers */
				for (j = 0; j < phases[i].Conflict_count; ++j)
				{
					phases[i].Conflicts[j]->Timer_clearing.Restart = TRUE;
				}
			}
			break;
		}
	}
}

void Phases_state_out_update(PHASE phases[], short phases_count)
{
	int i;
	for (i = 0; i < phases_count; ++i)
	{
		switch (phases[i].CycleState)
		{
		case WAITRED:
		case NEXTRED:
			phases[i].State_out = SO_RED;
			break;
		case YELLOW:
			phases[i].State_out = SO_YELLOW;
			break;
		default:
			phases[i].State_out = SO_GREEN;
			break;
		}
	}
}

void Phases_update_conflicts(PHASE phases[], short phases_count)
{
	int i, j;
	for (i = 0; i < phases_count; ++i)
	{
		phases[i].HasConflict = FALSE;
	}
	for (i = 0; i < phases_count; ++i)
	{
		for (j = 0; j < phases[i].Conflict_count; ++j)
		{
			if (phases[i].State_out != SO_RED ||
				phases[i].Conflicts[j]->Timer_clearing.Restart || phases[i].Conflicts[j]->Timer_clearing.Active)
			{
				phases[i].Conflicts[j]->ConflictPhase->HasConflict = TRUE;
			}
		}
	}
}

void Phases_extending(PHASE phases[], short phases_count)
{
	int i, k;
	for (i = 0; i < phases_count; ++i)
	{
		phases[i].Extend = FALSE;
		for (k = 0; k < phases[i].Detectors_count; ++k)
		{
			if (phases[i].Detectors[k]->Extend != DET_EXT_NONE)
			{
				switch (phases[i].Detectors[k]->Extend)
				{
				case DET_EXT_HEADMAX:
					if (phases[i].Detectors[k]->GapRunning && 
						phases[i].Timer_HeadMax.Active)
					{
						phases[i].Extend |= EXT_HEADMAX;
					}
					break;
				case DET_EXT_MEASURE:
					if (phases[i].Detectors[k]->GapRunning)
					{
						phases[i].Extend |= EXT_MEASURE;
					}
					break;
				}
			}
		}
	}
}

void Phases_requests(PHASE phases[], short phases_count)
{
	int i, j;
	for (i = 0; i < phases_count; ++i)
	{
		if (!phases[i].State_out == SO_GREEN)
		{
			/* Set requests based on switch */
			if (phases[i].Fixed_request.Setting == TRUE)
			{
				phases[i].Request |= REQ_FIX;
			}

			/* Set requests based on detection */
			for (j = 0; j < phases[i].Detectors_count; ++j)
			{
				if (phases[i].Detectors[j]->Request && phases[i].Detectors[j]->Occupied)
				{
					switch (phases[i].Detectors[j]->Request)
					{
					case DET_REQ_RED:
						if(phases[i].State_out == SO_RED)
							phases[i].Request |= REQ_DET;
						break;
					case DET_REQ_REDNONGAR:
						if (phases[i].State_out == SO_RED && !(phases[i].Timer_RG.Restart || phases[i].Timer_RG.Active))
							phases[i].Request |= REQ_DET;
						break;
					case DET_REQ_YELLOW:
						if(phases[i].State_out != SO_GREEN)
							phases[i].Request |= REQ_DET;
						break;
					default:
						break;
					}
				}
			}
		}
		/* Reset request on start green */
		if (phases[i].StartGreen)
		{
			phases[i].Request = FALSE;
			phases[i].Timer_PG_act = 0;
		}
	}
}