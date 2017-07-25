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

#include "tlccc_sg_func.h"

void SignalGroup_init(SIGNALGROUP * signalgroup, const char * code, short index, short tggmax, short tgfmax, short tgemax, short tyemax, short trgmax, short headmax)
{
	char temp[128];

	signalgroup->Code = (char *)malloc((strlen(code) + 1) * sizeof(char));
	snprintf(signalgroup->Code, strlen(code) + 1, "%s", code);

	signalgroup->Index = index;

	snprintf(temp, 128, "TGG%s", signalgroup->Code);
	Timer_init(&signalgroup->Timer_GG, temp, tggmax, TE_type);
	snprintf(temp, 128, "TGF%s", signalgroup->Code);
	Timer_init(&signalgroup->Timer_GF, temp, tgfmax, TE_type);
	snprintf(temp, 128, "TGE%s", signalgroup->Code);
	Timer_init(&signalgroup->Timer_GE, temp, tgemax, TE_type);
	snprintf(temp, 128, "TYE%s", signalgroup->Code);
	Timer_init(&signalgroup->Timer_YE, temp, tyemax, TE_type);
	snprintf(temp, 128, "TRG%s", signalgroup->Code);
	Timer_init(&signalgroup->Timer_RG, temp, trgmax, TE_type);

	snprintf(temp, 128, "THM%s", signalgroup->Code);
	Timer_init(&signalgroup->Timer_HeadMax, temp, headmax, TE_type);

	signalgroup->Timer_PG_act = 0;

	signalgroup->CycleState = WAITRED;
	signalgroup->Timer_RG.Restart = TRUE;
	signalgroup->State_out = SO_RED;
}

void SignalGroup_free(SIGNALGROUP * signalgroup)
{
	int j = 0;

	if (signalgroup->Code != NULL)
		free(signalgroup->Code);

	Timer_free(&signalgroup->Timer_GG);
	Timer_free(&signalgroup->Timer_GF);
	Timer_free(&signalgroup->Timer_GE);
	Timer_free(&signalgroup->Timer_YE);
	Timer_free(&signalgroup->Timer_RG);
	
	if (signalgroup->Detectors != NULL)
		free(signalgroup->Detectors);

	if (signalgroup->Conflicts != NULL)
	{
		for (j = 0; j < signalgroup->Conflict_count; ++j)
		{
			if (signalgroup->Conflicts[j] != NULL)
			{
				Timer_free(&(signalgroup->Conflicts[j]->Timer_clearing));
				free(signalgroup->Conflicts[j]);
			}
		}
		free(signalgroup->Conflicts);
	}
}

void SignalGroups_free(SIGNALGROUP signalgroups[], short signalgroups_count)
{
	int j = 0;

	for (j = 0; j < signalgroups_count; ++j)
	{
		SignalGroup_free(&signalgroups[j]);
	}
}

void SignalGroup_add_detectors(SIGNALGROUP * signalgroup, short detectors_count, ...)
{
	if (detectors_count > 0)
	{
		va_list a_list;
		int i;

		signalgroup->Detectors_count = detectors_count;
		signalgroup->Detectors = (DETECTOR **)malloc(detectors_count * sizeof(DETECTOR *));
		va_start(a_list, detectors_count);

		for (i = 0; i < detectors_count; ++i)
		{
			DETECTOR * d = va_arg(a_list, DETECTOR *);
			signalgroup->Detectors[i] = d;
			d->SignalGroup = signalgroup;
		}
	}
}

void SignalGroup_conflict_init(short phc1, short phc2, short conflictstable[], short signalgroups_count, short clearingtime)
{
	conflictstable[phc1 + phc2 * signalgroups_count] = clearingtime;
}

void SignalGroups_set_conflict_pointers(SIGNALGROUP signalgroups[], short signalgroups_count, short conflictstable[])
{
	int i, j, k;
	char temp[128];
	for (i = 0; i < signalgroups_count; ++i)
	{
		for (j = 0; j < signalgroups_count; ++j)
		{
			if (conflictstable[i + j * signalgroups_count] != -1)
			{
				signalgroups[i].Conflict_count++;
			}
		}
		signalgroups[i].Conflicts = (CONFLICT **)malloc(signalgroups[i].Conflict_count * sizeof(CONFLICT *));
		k = 0;
		for (j = 0; j < signalgroups_count; ++j)
		{
			if (conflictstable[i + j * signalgroups_count] != -1)
			{
				signalgroups[i].Conflicts[k] = (CONFLICT *)malloc(sizeof(CONFLICT));
				signalgroups[i].Conflicts[k]->ConflictingSignalGroup = &signalgroups[j];
				snprintf(temp, 128, "TO%s%s", signalgroups[i].Code, signalgroups[j].Code);
				Timer_init(&signalgroups[i].Conflicts[k]->Timer_clearing, temp, conflictstable[i + j * signalgroups_count], TE_type);
				k++;
			}
		}
	}
}

void SignalGroups_timers_update(SIGNALGROUP signalgroups[], short signalgroups_count, CLOCK * klok)
{
	int i;
	for (i = 0; i < signalgroups_count; ++i)
	{
		SignalGroup_timers_update(&signalgroups[i], klok);
	}
}

void SignalGroup_timers_update(SIGNALGROUP * signalgroup, CLOCK * clock)
{
	int i;
	Timer_update(&signalgroup->Timer_GG, clock);
	Timer_update(&signalgroup->Timer_GF, clock);
	Timer_update(&signalgroup->Timer_GE, clock);
	Timer_update(&signalgroup->Timer_YE, clock);
	Timer_update(&signalgroup->Timer_RG, clock);
	Timer_update(&signalgroup->Timer_HeadMax, clock);
	for (i = 0; i < signalgroup->Conflict_count; ++i)
	{
		Timer_update(&signalgroup->Conflicts[i]->Timer_clearing, clock);
	}

	if (clock->TS && signalgroup->Request && signalgroup->State_out != SO_GREEN)
	{
		signalgroup->Timer_PG_act += clock->TS;
	}
}

void SignalGroups_state_update_ML(SIGNALGROUP signalgroups[], short signalgroups_count, short * cif_guswijz)
{
	int i, j;
	for (i = 0; i < signalgroups_count; ++i)
	{
		signalgroups[i].StartGreen = FALSE;

		switch (signalgroups[i].CycleState)
		{
		case WAITRED:
			if (!(signalgroups[i].Timer_RG.Restart || signalgroups[i].Timer_RG.Active) && signalgroups[i].Request)
			{
				if (signalgroups[i].ML_Primary && !signalgroups[i].ML_Primary_done)
				{
					signalgroups[i].CycleState = NEXTRED;
					signalgroups[i].ML_Primary_active = TRUE;
					*cif_guswijz = TRUE;
					// TODO: set start end states ---> ALSO BELOW...
					break;
				}
				else if (signalgroups[i].ML_Alternative)
				{
					signalgroups[i].CycleState = NEXTRED;
					*cif_guswijz = TRUE;
				}
			}
			break;
		case NEXTRED:
			if (!signalgroups[i].HasConflict)
			{
				signalgroups[i].CycleState = PREGREEN;
				*cif_guswijz = TRUE;
			}
			break;
		case PREGREEN:
			// placeholder: move to next 
			signalgroups[i].CycleState = FIXEDGREEN;
			signalgroups[i].StartGreen = TRUE;
			signalgroups[i].Timer_GF.Restart = TRUE;
			signalgroups[i].Timer_HeadMax.Restart = TRUE;
			*cif_guswijz = TRUE;
			break;
		case FIXEDGREEN:
			if (signalgroups[i].Timer_GF.Ended)
			{
				signalgroups[i].CycleState = WAITGREEN;
				*cif_guswijz = TRUE;
			}
			break;
		case WAITGREEN:
			// placeholder: move to next 
			signalgroups[i].CycleState = EXTENDGREEN;
			*cif_guswijz = TRUE;
			signalgroups[i].Timer_GE.Restart = TRUE;
			break;
		case EXTENDGREEN:
			if (signalgroups[i].Timer_GE.Ended || !signalgroups[i].Extend)
			{
				signalgroups[i].CycleState = FREEEXGREEN;
				signalgroups[i].ML_Primary_active = TRUE;
				*cif_guswijz = TRUE;
			}
			break;
		case FREEEXGREEN:
			// placeholder: move to next 
			signalgroups[i].CycleState = YELLOW;
			signalgroups[i].Timer_YE.Restart = TRUE;
			*cif_guswijz = TRUE;
			break;
		case YELLOW:
			if (signalgroups[i].Timer_YE.Ended)
			{
				signalgroups[i].CycleState = WAITRED;
				*cif_guswijz = TRUE;
				signalgroups[i].Timer_RG.Restart = TRUE;
				/* Restart clearing timers */
				for (j = 0; j < signalgroups[i].Conflict_count; ++j)
				{
					signalgroups[i].Conflicts[j]->Timer_clearing.Restart = TRUE;
				}
			}
			break;
		}
	}
}

void SignalGroups_state_out_update(SIGNALGROUP signalgroups[], short signalgroups_count)
{
	int i;
	for (i = 0; i < signalgroups_count; ++i)
	{
		switch (signalgroups[i].CycleState)
		{
		case WAITRED:
		case NEXTRED:
			signalgroups[i].State_out = SO_RED;
			break;
		case YELLOW:
			signalgroups[i].State_out = SO_YELLOW;
			break;
		default:
			signalgroups[i].State_out = SO_GREEN;
			break;
		}
	}
}

void SignalGroups_update_conflicts(SIGNALGROUP signalgroups[], short signalgroups_count)
{
	int i, j;
	for (i = 0; i < signalgroups_count; ++i)
	{
		signalgroups[i].HasConflict = FALSE;
	}
	for (i = 0; i < signalgroups_count; ++i)
	{
		for (j = 0; j < signalgroups[i].Conflict_count; ++j)
		{
			if (signalgroups[i].State_out != SO_RED ||
				signalgroups[i].Conflicts[j]->Timer_clearing.Restart || signalgroups[i].Conflicts[j]->Timer_clearing.Active)
			{
				signalgroups[i].Conflicts[j]->ConflictingSignalGroup->HasConflict = TRUE;
			}
		}
	}
}

void SignalGroups_extending(SIGNALGROUP signalgroups[], short signalgroups_count)
{
	int i, k;
	for (i = 0; i < signalgroups_count; ++i)
	{
		signalgroups[i].Extend = FALSE;
		for (k = 0; k < signalgroups[i].Detectors_count; ++k)
		{
			if (signalgroups[i].Detectors[k]->Extend != DET_EXT_NONE)
			{
				switch (signalgroups[i].Detectors[k]->Extend)
				{
				case DET_EXT_HEADMAX:
					if (signalgroups[i].Detectors[k]->GapRunning && 
						signalgroups[i].Timer_HeadMax.Active)
					{
						signalgroups[i].Extend |= EXT_HEADMAX;
					}
					break;
				case DET_EXT_MEASURE:
					if (signalgroups[i].Detectors[k]->GapRunning)
					{
						signalgroups[i].Extend |= EXT_MEASURE;
					}
					break;
				}
			}
		}
	}
}

void SignalGroups_requests(SIGNALGROUP signalgroups[], short signalgroups_count)
{
	int i, j;
	for (i = 0; i < signalgroups_count; ++i)
	{
		if (!signalgroups[i].State_out == SO_GREEN)
		{
			/* Set requests based on switch */
			if (signalgroups[i].Fixed_request.Setting == TRUE)
			{
				signalgroups[i].Request |= REQ_FIX;
			}

			/* Set requests based on detection */
			for (j = 0; j < signalgroups[i].Detectors_count; ++j)
			{
				if (signalgroups[i].Detectors[j]->Request && signalgroups[i].Detectors[j]->Occupied)
				{
					switch (signalgroups[i].Detectors[j]->Request)
					{
					case DET_REQ_RED:
						if(signalgroups[i].State_out == SO_RED)
							signalgroups[i].Request |= REQ_DET;
						break;
					case DET_REQ_REDNONGAR:
						if (signalgroups[i].State_out == SO_RED && !(signalgroups[i].Timer_RG.Restart || signalgroups[i].Timer_RG.Active))
							signalgroups[i].Request |= REQ_DET;
						break;
					case DET_REQ_YELLOW:
						if(signalgroups[i].State_out != SO_GREEN)
							signalgroups[i].Request |= REQ_DET;
						break;
					default:
						break;
					}
				}
			}
		}
		/* Reset request on start green */
		if (signalgroups[i].StartGreen)
		{
			signalgroups[i].Request = FALSE;
			signalgroups[i].Timer_PG_act = 0;
		}
	}
}