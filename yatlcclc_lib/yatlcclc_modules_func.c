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

void Module_init(MODULE * module, char * code, short phases_count, ...)
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

void Modules_move_the_mill(MODULEMILL * modulemill, MODULE modules[], short modules_count, PHASE phases[], short phases_count)
{
	int i = modulemill->ActiveModule_index;
	int k;
	short ModGreenStarted = FALSE;

	modulemill->ModuleStart = FALSE;

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
		/* Reset flags for the current module */
		for (k = 0; k < modules[i].Phases_count; ++k)
		{
			modules[i].Phases[k]->ML_Primary = FALSE;
			modules[i].Phases[k]->ML_Primary_done = FALSE;
		}

		/* Check if we wait in the waiting module */
		int wait = TRUE;
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