/*
Copyright (C) 2016-2025 CodingConnected e. U., Menno van der Woude

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

#ifndef TLCCC_FCFUNC_H_INCLUDED
#define TLCCC_FCFUNC_H_INCLUDED

#include "tlccc_main.h"
#include "tlccc_timer_func.h"
#include "tlccc_switch_func.h"
#include "tlccc_det_func.h"
#include "tlccc_clock.h"

void SignalGroup_init(SIGNALGROUP * signalgroup, const char * code, short index, short tggmax, short tgfmax, short tgemax, short tyemax, short trgmax, short headmax);
void SignalGroup_free(SIGNALGROUP * signalgroup);
void SignalGroups_free(SIGNALGROUP signalgroups[], short signalgroups_count);
void SignalGroup_add_detectors(SIGNALGROUP * signalgroups, short detectors_count, ...);
void SignalGroup_conflict_init(short sgc1, short sgc2, short conflictstable[], short signalgroups_count, short clearingtime);
void SignalGroups_set_conflict_pointers(SIGNALGROUP signalgroups[], short signalgroups_count, short conflictstable[]);
void SignalGroups_timers_update(SIGNALGROUP signalgroups[], short signalgroups_count, CLOCK * clock);
void SignalGroup_timers_update(SIGNALGROUP * signalgroup, CLOCK * clock);
void SignalGroups_requests(SIGNALGROUP signalgroups[], short signalgroups_count);
void SignalGroups_extending(SIGNALGROUP signalgroups[], short signalgroups_count);
void SignalGroups_state_update_ML(SIGNALGROUP signalgroups[], short signalgroups_count, short * cif_guswijz);
void SignalGroups_state_update_FIX(SIGNALGROUP signalgroups[], short signalgroups_count, short * cif_guswijz);
void SignalGroups_state_out_update(SIGNALGROUP signalgroups[], short signalgroups_count);
void SignalGroups_update_conflicts(SIGNALGROUP signalgroups[], short signalgroups_count);

#define PRIMAIRY_REAL_MAX 3
#define ALTERNATIVE_REAL_MAX 3

struct CONFLICT_STRUCT
{
    TIMER Timer_clearing;
    SIGNALGROUP * ConflictingSignalGroup;
};

struct SIGNALGROUP_STRUCT
{
    /* State */
    short CycleState;
    short State_out;
    short Request;
    short Extend;
    short FreeExtend;
    short StartGreen;
    short StartGP;
    short StartGF;
    short StartGW;
    short StartGE;
    short StartGFR;
    short StartYE;
    short StartRG;
    short EndGP;
    short EndGF;
    short EndGW;
    short EndGE;
    short EndGFR;
    short EndYE;
    short EndRG;
    short EndGreen;
    short StartRed;
    short EndRed;
    short StartYellow;
    short EndYellow;
    TIMER Timer_GG;
    TIMER Timer_GF;
    TIMER Timer_GE;
    TIMER Timer_YE;
    TIMER Timer_RG;
    TIMER Timer_HeadMax;
    short Timer_PG_act;
    short HasConflict;

    /* Modules state */
    short ML_Primary;
    short ML_Primary_active;
    short ML_Primary_done;
    short ML_Alternative;
    short ML_Alt_Space;

    /* Settings */
    SWITCH Fixed_request;
    SWITCH Co_extend;
    MODULE * Module_primary[PRIMAIRY_REAL_MAX];
    short Modules_primary_count;
    MODULE * Module_alternative[ALTERNATIVE_REAL_MAX];
    short Modules_alternative_count;

    /* Info */
    short Index;
    char * Code;
    short Detectors_count;
    DETECTOR ** Detectors;
    short Conflict_count;
    CONFLICT ** Conflicts;

};

#define ML_PR 0x0001

#define PR_REAL 0x0001
#define PR_SKIP 0x0002

#define AR_REAL_POSSIBLE 0x0001

#define REQ_DET  0x0001
#define REQ_FIX  0x0002
#define REQ_CO   0x0004
#define REQ_DIR  0x0008
#define REQ_EX1  0x0100
#define REQ_EX2  0x0200
#define REQ_EX3  0x0400
#define REQ_EX4  0x0800

#define EXT_HEADMAX 0x0001
#define EXT_MEASURE 0x0002
#define EXT_EX1     0x0100
#define EXT_EX2     0x0200
#define EXT_EX3     0x0400
#define EXT_EX4     0x0800

#define FREE_CO     0x0001
#define FREE_FOLLOW 0x0002
#define FREE_EX1    0x0100
#define FREE_EX2    0x0200
#define FREE_EX3    0x0400
#define FREE_EX4    0x0800

#endif // TLCCC_FCFUNC_H_INCLUDED
