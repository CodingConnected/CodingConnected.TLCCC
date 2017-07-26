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

#include "tlccc_modules_func.h"

void Module_init(MODULE * module, short index, char * code, short signalgroups_count, ...)
{
    module->Code = (char *)malloc((strlen(code) + 1) * sizeof(char));
    snprintf(module->Code, strlen(code) + 1, "%s", code);

    if (signalgroups_count > 0)
    {
        va_list a_list;
        int i;

        module->SignalGroups = malloc(signalgroups_count * sizeof(SIGNALGROUP *));
        va_start(a_list, signalgroups_count);

        module->SignalGroups_count = signalgroups_count;
        module->Index = index;

        for (i = 0; i < signalgroups_count; ++i)
        {
            SIGNALGROUP * p = va_arg(a_list, SIGNALGROUP *);
            module->SignalGroups[i] = p;
            if (p->Modules_primary_count < PRIMAIRY_REAL_MAX)
            {
                p->Module_primary[p->Modules_primary_count] = module;
                p->Modules_primary_count++;
            }
        }
    }
}

void ModuleMill_free(MODULEMILL * modulemill, short modules_count)
{
    int ml;

    if (modulemill == NULL)
        return;

    for (ml = 0; ml < modules_count; ++ml)
    {
        if (modulemill->Modules[ml] != NULL)
        {
            Module_free(modulemill->Modules[ml]);
        }
    }
}

void Module_free(MODULE * module)
{
    if (module->Code != NULL)
        free(module->Code);

    if (module->SignalGroups != NULL)
        free(module->SignalGroups);
}

void ModuleMill_init(MODULEMILL * modulemill, MODULE modules[], short modules_count, short waiting_module)
{
    int i;

    if (modules_count <= 0 || waiting_module >= modules_count)
        return;

    modulemill->Modules = (MODULE **)malloc(modules_count * sizeof(MODULE *));
    
    for (i = 0; i < modules_count; ++i)
    {
        modulemill->Modules[i] = &modules[i];
    }

    modules[0].IsActive = TRUE;
    modulemill->ActiveModule = &modules[0];
    modulemill->ActiveModule_index = 0;

    modulemill->WaitingModule = &modules[waiting_module];
    modulemill->WaitingModule_index = waiting_module;

    modulemill->ModuleStart = TRUE;
    modulemill->Modules_count = modules_count;
}

void Modules_set_alternative_space_default(SIGNALGROUP signalgroups[], short signalgroups_count, short space)
{
    int i;
    for (i = 0; i < signalgroups_count; ++i)
    {
        signalgroups[i].ML_Alt_Space = space;
    }
}

void Modules_update_primary(MODULEMILL * modulemill)
{
    int i = modulemill->ActiveModule_index;
    int k;
    char ModGreenStarted = FALSE;
    
    /* Determine if the module has really begun: one or more signalgroups green */
    for (k = 0; k < modulemill->Modules[i]->SignalGroups_count; ++k)
    {
        if (modulemill->Modules[i]->SignalGroups[k]->State_out != SO_RED)
        {
            ModGreenStarted = TRUE;
            break;
        }
    }

    /* Set signalgroups ML primary realisation state */
    for (k = 0; k < modulemill->Modules[i]->SignalGroups_count; ++k)
    {
        /* Set primary realisation: signalgroup may realize */
        if ((modulemill->Modules[i]->SignalGroups[k]->Request) &&
            !(modulemill->Modules[i]->SignalGroups[k]->ML_Primary_done))
        {
            modulemill->Modules[i]->SignalGroups[k]->ML_Primary = TRUE;
        }
        /* Set primary realisation done if signalgroup is in primary green */
        if ((modulemill->Modules[i]->SignalGroups[k]->State_out == SO_GREEN) &&
            (modulemill->Modules[i]->SignalGroups[k]->ML_Primary) &&
            !(modulemill->Modules[i]->SignalGroups[k]->ML_Primary_done))
        {
            modulemill->Modules[i]->SignalGroups[k]->ML_Primary_done |= PR_REAL;
        }
    }
    
    /* Set signalgroups ML skipped primary realisation */
    if (ModGreenStarted)
    {
        for (k = 0; k < modulemill->Modules[i]->SignalGroups_count; ++k)
        {
            if (!modulemill->Modules[i]->SignalGroups[k]->ML_Primary_done && !modulemill->Modules[i]->SignalGroups[k]->Request)
            {
                int l, m = TRUE;
                for (l = 0; l < modulemill->Modules[i]->SignalGroups_count; ++l)
                {
                    if (!modulemill->Modules[i]->SignalGroups[k]->ML_Primary_done && modulemill->Modules[i]->SignalGroups[k]->Request)
                    {
                        m = FALSE;
                        break;
                    }
                }
                if (m)
                {
                    modulemill->Modules[i]->SignalGroups[k]->ML_Primary_done |= PR_SKIP;
                }
            }
        }
    }
}

void Modules_update_alternative(MODULEMILL * modulemill, SIGNALGROUP signalgroups[], short signalgroups_count)
{
    int i, k, l;
    for (k = 0; k < signalgroups_count; ++k)
    {
        if (signalgroups[k].Request && !signalgroups[k].ML_Primary && !signalgroups[k].HasConflict)
        {
            signalgroups[k].ML_Alternative |= AR_REAL_POSSIBLE;
        }
    }
    /* Check for remaining space */
    for (k = 0; k < signalgroups_count; ++k)
    {
        if (signalgroups[k].ML_Alternative & AR_REAL_POSSIBLE)
        {
            /* TODO: needs more intelligence: take into account clearing times, yellow, etc */
            char alt = FALSE;
            for (l = 0; l < signalgroups_count; ++l)
            {
                /* Skip conflicts */
                for (i = 0; i < signalgroups[k].Conflict_count; ++i)
                {
                    if (signalgroups[k].Conflicts[i]->ConflictingSignalGroup->Index == signalgroups[l].Index)
                        continue;
                }
                /* Check space */
                if (signalgroups[l].ML_Primary_active &&
                    (signalgroups[l].CycleState > NEXTRED && signalgroups[l].CycleState < EXTENDGREEN ||
                     signalgroups[l].CycleState == EXTENDGREEN && signalgroups[l].Timer_GE.Remaining > signalgroups[k].ML_Alt_Space))
                {
                    alt = TRUE;
                    break;
                }
            }
            if (!alt)
                signalgroups[k].ML_Alternative &= ~AR_REAL_POSSIBLE;
        }
    }
    /* Check longer waiting conflicting alternatives */
    for (k = 0; k < signalgroups_count; ++k)
    {
        if (signalgroups[k].ML_Alternative & AR_REAL_POSSIBLE)
        {
            for (l = 0; l < signalgroups[k].Conflict_count; ++l)
            {
                if (signalgroups[k].Conflicts[l]->ConflictingSignalGroup->Module_primary[0]->Index == modulemill->ActiveModule_index &&
                    signalgroups[k].Conflicts[l]->ConflictingSignalGroup->ML_Primary && !signalgroups[k].Conflicts[l]->ConflictingSignalGroup->ML_Primary_done ||
                    signalgroups[k].Conflicts[l]->ConflictingSignalGroup->ML_Alternative && signalgroups[k].Conflicts[l]->ConflictingSignalGroup->Timer_PG_act > signalgroups[k].Timer_PG_act)
                    signalgroups[k].ML_Alternative &= ~AR_REAL_POSSIBLE;
            }
        }
    }
}

void Modules_move_the_mill(MODULEMILL * modulemill, SIGNALGROUP signalgroups[], short signalgroups_count)
{
    int i = modulemill->ActiveModule_index;
    int k;
    modulemill->ModuleStart = FALSE;

    /* Set current module state */
    modulemill->Modules[i]->AllRealised = TRUE;
    for (k = 0; k < modulemill->Modules[i]->SignalGroups_count; ++k)
    {
        /* Check if all signalgroups with requests have realised */
        if (modulemill->Modules[i]->SignalGroups[k]->Request && !modulemill->Modules[i]->SignalGroups[k]->ML_Primary_done)
        {
            modulemill->Modules[i]->AllRealised = FALSE;
            break;
        }
        /* Check if all signalgroups that are green are ready to move */
        if (modulemill->Modules[i]->SignalGroups[k]->ML_Primary_done && 
            !(modulemill->Modules[i]->SignalGroups[k]->State_out == SO_RED ||
              modulemill->Modules[i]->SignalGroups[k]->CycleState == FREEEXGREEN || 
              modulemill->Modules[i]->SignalGroups[k]->CycleState == YELLOW))
        {
            modulemill->Modules[i]->AllRealised = FALSE;
            break;
        }
    }

    /* Move the mill */
    if (modulemill->Modules[i]->AllRealised)
    {
        int wait = TRUE;

        /* Reset flags for the current module */
        for (k = 0; k < modulemill->Modules[i]->SignalGroups_count; ++k)
        {
            modulemill->Modules[i]->SignalGroups[k]->ML_Primary = FALSE;
            modulemill->Modules[i]->SignalGroups[k]->ML_Primary_done = FALSE;
        }

        /* Check if we wait in the waiting module */
        if (modulemill->ActiveModule_index == modulemill->WaitingModule_index)
        {
            for (k = 0; k < signalgroups_count; ++k)
            {
                if (signalgroups[k].Request)
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
            modulemill->ActiveModule = modulemill->Modules[modulemill->ActiveModule_index];
            modulemill->ModuleStart = TRUE;
        }
    }
}

void Modules_update_segment_display(MODULEMILL * modulemill, OUTGOING_SIGNAL os[], short index, short * cif_guswijz)
{
    switch (modulemill->ActiveModule_index)
    {
    case 0:
        Outgoing_signal_set_desired(&os[index + 0], 0, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 1], 0, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 2], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 3], 0, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 4], 0, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 5], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 6], 0, cif_guswijz);
        break;
    case 1:
        Outgoing_signal_set_desired(&os[index + 0], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 1], 0, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 2], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 3], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 4], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 5], 0, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 6], 1, cif_guswijz);
        break;
    case 2:
        Outgoing_signal_set_desired(&os[index + 0], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 1], 0, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 2], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 3], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 4], 0, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 5], 1, cif_guswijz);
        Outgoing_signal_set_desired(&os[index + 6], 1, cif_guswijz);
        break;
    case 3:
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