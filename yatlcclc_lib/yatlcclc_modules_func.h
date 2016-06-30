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

#ifndef YATLCCLC_MODULESFUNC_H_INCLUDED
#define YATLCCLC_MODULESFUNC_H_INCLUDED

#include "yatlcclc_main.h"
#include "yatlcclc_clock.h"
#include "yatlcclc_fc_func.h"

void Module_init(MODULE * module, char * code, short phases_count, ...);
void ModuleMill_init(MODULEMILL * modulemill, MODULE modules[], short modules_count, short waiting_module);
void Modules_move_the_mill(MODULEMILL * modulemill, MODULE modules[], short modules_count, PHASE phases[], short phases_count);

struct MODULE_STRUCT
{
	/* State */
	short Hold;
	short AllRealised;
	short Number;
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
	short WaitingModule_index;
	short Modules_count;
	short ModuleStart;

	short CurrentCycleTime;
	short CurrentModuleTime;
};

#endif /* YATLCCLC_MODULESFUNC_H_INCLUDED */