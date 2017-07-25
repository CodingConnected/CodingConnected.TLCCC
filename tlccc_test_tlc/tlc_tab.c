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

#include "tlc_sys.h"

void application_init(SIGNALGROUP signalgroups[], DETECTOR detectors[], OUTGOING_SIGNAL os[], MODULEMILL * modulemill, MODULE modules[], CLOCK * clock)
{
	int i;

	short CT_max[SGMAX * SGMAX] = { 0 };

	/* Specify signalgroups
	                 PHASE-pointer  code    index tgg tgf tge  tye trg thm */
	SignalGroup_init(&signalgroups[sg01], "sg01", sg01, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg02], "sg02", sg02, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg03], "sg03", sg03, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg05], "sg05", sg05, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg06], "sg06", sg06, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg07], "sg07", sg07, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg08], "sg08", sg08, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg09], "sg09", sg09, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg11], "sg11", sg11, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg12], "sg12", sg12, 40, 50, 300, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg24], "sg24", sg24, 40, 50, 100, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg28], "sg28", sg28, 40, 50, 100, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg34], "sg34", sg34, 40, 50, 100, 30, 20, 80);
	SignalGroup_init(&signalgroups[sg38], "sg38", sg38, 40, 50, 100, 30, 20, 80);

	/* Specify conflicts */
	for (i = 0; i < SGMAX * SGMAX; ++i)
	{
		CT_max[i] = -1;
	}
	SignalGroup_conflict_init(sg01, sg05, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg01, sg09, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg01, sg28, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg01, sg38, CT_max, SGMAX, 20);

	SignalGroup_conflict_init(sg02, sg05, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg02, sg06, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg02, sg09, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg02, sg11, CT_max, SGMAX, 40);
	SignalGroup_conflict_init(sg02, sg12, CT_max, SGMAX, 30);

	SignalGroup_conflict_init(sg03, sg05, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg03, sg06, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg03, sg07, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg03, sg08, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg03, sg11, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg03, sg12, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg03, sg24, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg03, sg34, CT_max, SGMAX, 40);

	SignalGroup_conflict_init(sg05, sg01, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg05, sg02, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg05, sg03, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg05, sg08, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg05, sg09, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg05, sg12, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg05, sg24, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg05, sg28, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg05, sg34, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg05, sg38, CT_max, SGMAX, 40);

	SignalGroup_conflict_init(sg06, sg02, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg06, sg03, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg06, sg08, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg06, sg09, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg06, sg11, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg06, sg24, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg06, sg34, CT_max, SGMAX, 0);

	SignalGroup_conflict_init(sg07, sg03, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg07, sg11, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg07, sg24, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg07, sg34, CT_max, SGMAX, 30);

	SignalGroup_conflict_init(sg08, sg03, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg08, sg05, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg08, sg06, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg08, sg11, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg08, sg12, CT_max, SGMAX, 0);

	SignalGroup_conflict_init(sg09, sg01, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg09, sg02, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg09, sg05, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg09, sg06, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg09, sg11, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg09, sg12, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg09, sg28, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg09, sg38, CT_max, SGMAX, 40);

	SignalGroup_conflict_init(sg11, sg02, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg11, sg03, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg11, sg06, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg11, sg07, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg11, sg08, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg11, sg09, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg11, sg24, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg11, sg28, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg11, sg34, CT_max, SGMAX, 40);
	SignalGroup_conflict_init(sg11, sg38, CT_max, SGMAX, 10);

	SignalGroup_conflict_init(sg12, sg02, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg12, sg03, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg12, sg05, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg12, sg08, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg12, sg09, CT_max, SGMAX, 10);
	SignalGroup_conflict_init(sg12, sg28, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg12, sg38, CT_max, SGMAX, 10);

	SignalGroup_conflict_init(sg24, sg03, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg24, sg05, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg24, sg06, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg24, sg07, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg24, sg11, CT_max, SGMAX, 0);

	SignalGroup_conflict_init(sg34, sg03, CT_max, SGMAX, 60);
	SignalGroup_conflict_init(sg34, sg05, CT_max, SGMAX, 80);
	SignalGroup_conflict_init(sg34, sg06, CT_max, SGMAX, 70);
	SignalGroup_conflict_init(sg34, sg07, CT_max, SGMAX, 50);
	SignalGroup_conflict_init(sg34, sg11, CT_max, SGMAX, 30);

	SignalGroup_conflict_init(sg28, sg01, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg28, sg05, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg28, sg09, CT_max, SGMAX, 0);
	SignalGroup_conflict_init(sg28, sg11, CT_max, SGMAX, 20);
	SignalGroup_conflict_init(sg28, sg12, CT_max, SGMAX, 30);

	SignalGroup_conflict_init(sg38, sg01, CT_max, SGMAX, 60);
	SignalGroup_conflict_init(sg38, sg05, CT_max, SGMAX, 30);
	SignalGroup_conflict_init(sg38, sg09, CT_max, SGMAX, 40);
	SignalGroup_conflict_init(sg38, sg11, CT_max, SGMAX, 80);
	SignalGroup_conflict_init(sg38, sg12, CT_max, SGMAX, 70);

	SignalGroups_set_conflict_pointers(signalgroups, SGMAX, CT_max);

	/* Specify modules */
	Module_init(&modules[ML1], ML1, "ML1", 6, &signalgroups[sg02], &signalgroups[sg08], &signalgroups[sg24], &signalgroups[sg34], &signalgroups[sg28], &signalgroups[sg38]);
	Module_init(&modules[ML2], ML2, "ML2", 2, &signalgroups[sg03], &signalgroups[sg09]);
	Module_init(&modules[ML3], ML3, "ML3", 2, &signalgroups[sg11], &signalgroups[sg05]);
	Module_init(&modules[ML4], ML4, "ML4", 4, &signalgroups[sg01], &signalgroups[sg06], &signalgroups[sg07], &signalgroups[sg12]);
	ModuleMill_init(modulemill, modules, 4, ML1);

	/* Specify alternative conditions */
	Modules_set_alternative_space_default(signalgroups, SGMAX, 60);

	/* Specify detectors */
	Detector_init(&detectors[d01_1], "d01_1", &CIF_IS[d01_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d01_2], "d01_2", &CIF_IS[d01_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d02_1], "d02_1", &CIF_IS[d02_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d02_2], "d02_2", &CIF_IS[d02_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d03_1], "d03_1", &CIF_IS[d03_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d03_2], "d03_2", &CIF_IS[d03_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d05_1], "d05_1", &CIF_IS[d05_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d05_2], "d05_2", &CIF_IS[d05_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d06_1], "d06_1", &CIF_IS[d06_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d06_2], "d06_2", &CIF_IS[d06_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d07_1], "d07_1", &CIF_IS[d07_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d07_2], "d07_2", &CIF_IS[d07_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d08_1], "d08_1", &CIF_IS[d08_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d08_2], "d08_2", &CIF_IS[d08_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d09_1], "d09_1", &CIF_IS[d09_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d09_2], "d09_2", &CIF_IS[d09_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d11_1], "d11_1", &CIF_IS[d11_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d11_2], "d11_2", &CIF_IS[d11_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d12_1], "d12_1", &CIF_IS[d12_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 0, 30, 360, 10);
	Detector_init(&detectors[d12_2], "d12_2", &CIF_IS[d12_2], D_LONG, DET_REQ_REDNONGAR, DET_EXT_MEASURE, 10, 0, 360, 10);
	Detector_init(&detectors[d24_1], "d24_1", &CIF_IS[d24_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 15, 30, 360, 10);
	Detector_init(&detectors[dk24], "dk24", &CIF_IS[dk24], D_BUTTON, DET_REQ_YELLOW, DET_EXT_NONE, 0, 0, 360, 10);
	Detector_init(&detectors[d28_1], "d28_1", &CIF_IS[d28_1], D_HEAD, DET_REQ_REDNONGAR, DET_EXT_HEADMAX, 15, 30, 360, 10);
	Detector_init(&detectors[dk28], "dk28", &CIF_IS[dk28], D_BUTTON, DET_REQ_YELLOW, DET_EXT_NONE, 0, 0, 360, 10);
	Detector_init(&detectors[dk34a], "dk34a", &CIF_IS[dk34a], D_BUTTON, DET_REQ_YELLOW, DET_EXT_NONE, 0, 0, 360, 10);
	Detector_init(&detectors[dk34b], "dk34b", &CIF_IS[dk34b], D_BUTTON, DET_REQ_YELLOW, DET_EXT_NONE, 0, 0, 360, 10);
	Detector_init(&detectors[dk38a], "dk38a", &CIF_IS[dk38a], D_BUTTON, DET_REQ_YELLOW, DET_EXT_NONE, 0, 0, 360, 10);
	Detector_init(&detectors[dk38b], "dk38b", &CIF_IS[dk38b], D_BUTTON, DET_REQ_YELLOW, DET_EXT_NONE, 0, 0, 360, 10);

	/* Assign detectors to signalgroups */
	SignalGroup_add_detectors(&signalgroups[sg01], 2, &detectors[d01_1], &detectors[d01_2]);
	SignalGroup_add_detectors(&signalgroups[sg02], 2, &detectors[d02_1], &detectors[d02_2]);
	SignalGroup_add_detectors(&signalgroups[sg03], 2, &detectors[d03_1], &detectors[d03_2]);
	SignalGroup_add_detectors(&signalgroups[sg05], 2, &detectors[d05_1], &detectors[d05_2]);
	SignalGroup_add_detectors(&signalgroups[sg06], 2, &detectors[d06_1], &detectors[d06_2]);
	SignalGroup_add_detectors(&signalgroups[sg07], 2, &detectors[d07_1], &detectors[d07_2]);
	SignalGroup_add_detectors(&signalgroups[sg08], 2, &detectors[d08_1], &detectors[d08_2]);
	SignalGroup_add_detectors(&signalgroups[sg09], 2, &detectors[d09_1], &detectors[d09_2]);
	SignalGroup_add_detectors(&signalgroups[sg11], 2, &detectors[d11_1], &detectors[d11_2]);
	SignalGroup_add_detectors(&signalgroups[sg12], 2, &detectors[d12_1], &detectors[d12_2]);
	SignalGroup_add_detectors(&signalgroups[sg24], 2, &detectors[d24_1], &detectors[dk24]);
	SignalGroup_add_detectors(&signalgroups[sg28], 2, &detectors[d28_1], &detectors[dk28]);
	SignalGroup_add_detectors(&signalgroups[sg34], 2, &detectors[dk34a], &detectors[dk34b]);
	SignalGroup_add_detectors(&signalgroups[sg38], 2, &detectors[dk38a], &detectors[dk38b]);

	/* Initiate outgoing signals */
	Outgoing_signal_init(&os[ossegm1], "segm1", ossegm1+SGMAX);
	Outgoing_signal_init(&os[ossegm2], "segm2", ossegm2+SGMAX);
	Outgoing_signal_init(&os[ossegm3], "segm3", ossegm3+SGMAX);
	Outgoing_signal_init(&os[ossegm4], "segm4", ossegm4+SGMAX);
	Outgoing_signal_init(&os[ossegm5], "segm5", ossegm5+SGMAX);
	Outgoing_signal_init(&os[ossegm6], "segm6", ossegm6+SGMAX);
	Outgoing_signal_init(&os[ossegm7], "segm7", ossegm7+SGMAX);

	/* Initiate clock structure */
	Clock_CIF_init(clock);

	atexit(application_exit);
}