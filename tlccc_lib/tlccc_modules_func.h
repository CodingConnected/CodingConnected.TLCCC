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

#ifndef TLCCC_MODULESFUNC_H_INCLUDED
#define TLCCC_MODULESFUNC_H_INCLUDED

#include "tlccc_main.h"
#include "tlccc_clock.h"
#include "tlccc_fc_func.h"
#include "tlccc_os_func.h"

void Module_init(MODULE * module, short index, char * code, short phases_count, ...);
void Module_free(MODULE * module);
void ModuleMill_init(MODULEMILL * modulemill, MODULE modules[], short modules_count, short waiting_module);
void ModuleMill_free(MODULEMILL * modulemill, short modules_count);
void Modules_update_primary(MODULEMILL * modulemill);
void Modules_update_alternative(MODULEMILL * modulemill, PHASE phases[], short phases_count);
void Modules_move_the_mill(MODULEMILL * modulemill, PHASE phases[], short phases_count);
void Modules_set_alternative_space_default(PHASE phases[], short phases_count, short space);
void Modules_update_segment_display(MODULEMILL * modulemill, OUTGOING_SIGNAL os[], short index, short * cif_guswijz);

struct MODULE_STRUCT
{
	/* State */
	short Hold;
	short AllRealised;
	short Index;
	short ModuleStart;
	short IsActive;

	/* Information */
	char * Code;
	PHASE ** Phases;
	short Phases_count;
};

struct MODULEMILL_STRUCT
{
	MODULE * ActiveModule;
	short ActiveModule_index;
	MODULE * WaitingModule;
	MODULE ** Modules;
	short WaitingModule_index;
	short Modules_count;
	short ModuleStart;

	short CurrentCycleTime;
	short CurrentModuleTime;
};

#endif /* TLCCC_MODULESFUNC_H_INCLUDED */
