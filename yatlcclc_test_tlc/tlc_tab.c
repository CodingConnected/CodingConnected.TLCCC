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

void application_init(PHASE phases[], DETECTOR detectors[], OUTGOING_SIGNAL os[], short CT_max[], MODULEMILL * modulemill, MODULE modules[], CLOCK * clock)
{
	int i;

	/* Specify phases
	           PHASE-pointer  code    index tgg  tgf  tge  tye  trg  thm */
	Phase_init(&phases[fc01], "fc01", fc01, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc02], "fc02", fc02, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc03], "fc03", fc03, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc05], "fc05", fc05, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc06], "fc06", fc06, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc07], "fc07", fc07, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc08], "fc08", fc08, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc09], "fc09", fc09, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc11], "fc11", fc11, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc12], "fc12", fc12, 40, 50, 300, 30, 20, 80);
	Phase_init(&phases[fc24], "fc24", fc24, 40, 50, 100, 30, 20, 80);
	Phase_init(&phases[fc28], "fc28", fc28, 40, 50, 100, 30, 20, 80);
	Phase_init(&phases[fc34], "fc34", fc34, 40, 50, 100, 30, 20, 80);
	Phase_init(&phases[fc38], "fc38", fc38, 40, 50, 100, 30, 20, 80);

	/* Specify conflicts */
	for (i = 0; i < FCMAX * FCMAX; ++i)
	{
		CT_max[i] = -1;
	}
	Phase_conflict_init(fc01, fc05, CT_max, FCMAX, 0);
	Phase_conflict_init(fc01, fc09, CT_max, FCMAX, 0);
	Phase_conflict_init(fc01, fc28, CT_max, FCMAX, 10);
	Phase_conflict_init(fc01, fc38, CT_max, FCMAX, 20);

	Phase_conflict_init(fc02, fc05, CT_max, FCMAX, 10);
	Phase_conflict_init(fc02, fc06, CT_max, FCMAX, 20);
	Phase_conflict_init(fc02, fc09, CT_max, FCMAX, 30);
	Phase_conflict_init(fc02, fc11, CT_max, FCMAX, 40);
	Phase_conflict_init(fc02, fc12, CT_max, FCMAX, 30);

	Phase_conflict_init(fc03, fc05, CT_max, FCMAX, 0);
	Phase_conflict_init(fc03, fc06, CT_max, FCMAX, 10);
	Phase_conflict_init(fc03, fc07, CT_max, FCMAX, 20);
	Phase_conflict_init(fc03, fc08, CT_max, FCMAX, 20);
	Phase_conflict_init(fc03, fc11, CT_max, FCMAX, 0);
	Phase_conflict_init(fc03, fc12, CT_max, FCMAX, 0);
	Phase_conflict_init(fc03, fc24, CT_max, FCMAX, 30);
	Phase_conflict_init(fc03, fc34, CT_max, FCMAX, 40);

	Phase_conflict_init(fc05, fc01, CT_max, FCMAX, 30);
	Phase_conflict_init(fc05, fc02, CT_max, FCMAX, 30);
	Phase_conflict_init(fc05, fc03, CT_max, FCMAX, 20);
	Phase_conflict_init(fc05, fc08, CT_max, FCMAX, 0);
	Phase_conflict_init(fc05, fc09, CT_max, FCMAX, 10);
	Phase_conflict_init(fc05, fc12, CT_max, FCMAX, 10);
	Phase_conflict_init(fc05, fc24, CT_max, FCMAX, 0);
	Phase_conflict_init(fc05, fc28, CT_max, FCMAX, 30);
	Phase_conflict_init(fc05, fc34, CT_max, FCMAX, 10);
	Phase_conflict_init(fc05, fc38, CT_max, FCMAX, 40);

	Phase_conflict_init(fc06, fc02, CT_max, FCMAX, 0);
	Phase_conflict_init(fc06, fc03, CT_max, FCMAX, 10);
	Phase_conflict_init(fc06, fc08, CT_max, FCMAX, 10);
	Phase_conflict_init(fc06, fc09, CT_max, FCMAX, 20);
	Phase_conflict_init(fc06, fc11, CT_max, FCMAX, 30);
	Phase_conflict_init(fc06, fc24, CT_max, FCMAX, 0);
	Phase_conflict_init(fc06, fc34, CT_max, FCMAX, 0);

	Phase_conflict_init(fc07, fc03, CT_max, FCMAX, 0);
	Phase_conflict_init(fc07, fc11, CT_max, FCMAX, 0);
	Phase_conflict_init(fc07, fc24, CT_max, FCMAX, 20);
	Phase_conflict_init(fc07, fc34, CT_max, FCMAX, 30);

	Phase_conflict_init(fc08, fc03, CT_max, FCMAX, 10);
	Phase_conflict_init(fc08, fc05, CT_max, FCMAX, 0);
	Phase_conflict_init(fc08, fc06, CT_max, FCMAX, 10);
	Phase_conflict_init(fc08, fc11, CT_max, FCMAX, 0);
	Phase_conflict_init(fc08, fc12, CT_max, FCMAX, 0);

	Phase_conflict_init(fc09, fc01, CT_max, FCMAX, 20);
	Phase_conflict_init(fc09, fc02, CT_max, FCMAX, 10);
	Phase_conflict_init(fc09, fc05, CT_max, FCMAX, 0);
	Phase_conflict_init(fc09, fc06, CT_max, FCMAX, 10);
	Phase_conflict_init(fc09, fc11, CT_max, FCMAX, 0);
	Phase_conflict_init(fc09, fc12, CT_max, FCMAX, 10);
	Phase_conflict_init(fc09, fc28, CT_max, FCMAX, 30);
	Phase_conflict_init(fc09, fc38, CT_max, FCMAX, 40);

	Phase_conflict_init(fc11, fc02, CT_max, FCMAX, 0);
	Phase_conflict_init(fc11, fc03, CT_max, FCMAX, 10);
	Phase_conflict_init(fc11, fc06, CT_max, FCMAX, 10);
	Phase_conflict_init(fc11, fc07, CT_max, FCMAX, 20);
	Phase_conflict_init(fc11, fc08, CT_max, FCMAX, 30);
	Phase_conflict_init(fc11, fc09, CT_max, FCMAX, 30);
	Phase_conflict_init(fc11, fc24, CT_max, FCMAX, 30);
	Phase_conflict_init(fc11, fc28, CT_max, FCMAX, 0);
	Phase_conflict_init(fc11, fc34, CT_max, FCMAX, 40);
	Phase_conflict_init(fc11, fc38, CT_max, FCMAX, 10);

	Phase_conflict_init(fc12, fc02, CT_max, FCMAX, 10);
	Phase_conflict_init(fc12, fc03, CT_max, FCMAX, 20);
	Phase_conflict_init(fc12, fc05, CT_max, FCMAX, 30);
	Phase_conflict_init(fc12, fc08, CT_max, FCMAX, 0);
	Phase_conflict_init(fc12, fc09, CT_max, FCMAX, 10);
	Phase_conflict_init(fc12, fc28, CT_max, FCMAX, 0);
	Phase_conflict_init(fc12, fc38, CT_max, FCMAX, 10);

	Phase_conflict_init(fc24, fc03, CT_max, FCMAX, 0);
	Phase_conflict_init(fc24, fc05, CT_max, FCMAX, 30);
	Phase_conflict_init(fc24, fc06, CT_max, FCMAX, 20);
	Phase_conflict_init(fc24, fc07, CT_max, FCMAX, 0);
	Phase_conflict_init(fc24, fc11, CT_max, FCMAX, 0);

	Phase_conflict_init(fc34, fc03, CT_max, FCMAX, 60);
	Phase_conflict_init(fc34, fc05, CT_max, FCMAX, 80);
	Phase_conflict_init(fc34, fc06, CT_max, FCMAX, 70);
	Phase_conflict_init(fc34, fc07, CT_max, FCMAX, 50);
	Phase_conflict_init(fc34, fc11, CT_max, FCMAX, 30);

	Phase_conflict_init(fc28, fc01, CT_max, FCMAX, 0);
	Phase_conflict_init(fc28, fc05, CT_max, FCMAX, 0);
	Phase_conflict_init(fc28, fc09, CT_max, FCMAX, 0);
	Phase_conflict_init(fc28, fc11, CT_max, FCMAX, 20);
	Phase_conflict_init(fc28, fc12, CT_max, FCMAX, 30);

	Phase_conflict_init(fc38, fc01, CT_max, FCMAX, 60);
	Phase_conflict_init(fc38, fc05, CT_max, FCMAX, 30);
	Phase_conflict_init(fc38, fc09, CT_max, FCMAX, 40);
	Phase_conflict_init(fc38, fc11, CT_max, FCMAX, 80);
	Phase_conflict_init(fc38, fc12, CT_max, FCMAX, 70);

	Phases_set_conflict_pointers(phases, FCMAX, CT_max);

	/* Specify modules */
	Module_init(&modules[ML1], ML1, "ML1", 6, &phases[fc02], &phases[fc08], &phases[fc24], &phases[fc34], &phases[fc28], &phases[fc38]);
	Module_init(&modules[ML2], ML2, "ML2", 2, &phases[fc03], &phases[fc09]);
	Module_init(&modules[ML3], ML3, "ML3", 2, &phases[fc11], &phases[fc05]);
	Module_init(&modules[ML4], ML4, "ML4", 4, &phases[fc01], &phases[fc06], &phases[fc07], &phases[fc12]);
	ModuleMill_init(modulemill, modules, 4, ML1);

	/* Specify alternative conditions */
	Modules_set_alternative_space_default(phases, FCMAX, 60);

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

	/* Assign detectors to phases */
	Phase_add_detectors(&phases[fc01], 2, &detectors[d01_1], &detectors[d01_2]);
	Phase_add_detectors(&phases[fc02], 2, &detectors[d02_1], &detectors[d02_2]);
	Phase_add_detectors(&phases[fc03], 2, &detectors[d03_1], &detectors[d03_2]);
	Phase_add_detectors(&phases[fc05], 2, &detectors[d05_1], &detectors[d05_2]);
	Phase_add_detectors(&phases[fc06], 2, &detectors[d06_1], &detectors[d06_2]);
	Phase_add_detectors(&phases[fc07], 2, &detectors[d07_1], &detectors[d07_2]);
	Phase_add_detectors(&phases[fc08], 2, &detectors[d08_1], &detectors[d08_2]);
	Phase_add_detectors(&phases[fc09], 2, &detectors[d09_1], &detectors[d09_2]);
	Phase_add_detectors(&phases[fc11], 2, &detectors[d11_1], &detectors[d11_2]);
	Phase_add_detectors(&phases[fc12], 2, &detectors[d12_1], &detectors[d12_2]);
	Phase_add_detectors(&phases[fc24], 2, &detectors[d24_1], &detectors[dk24]);
	Phase_add_detectors(&phases[fc28], 2, &detectors[d28_1], &detectors[dk28]);
	Phase_add_detectors(&phases[fc34], 2, &detectors[dk34a], &detectors[dk34b]);
	Phase_add_detectors(&phases[fc38], 2, &detectors[dk38a], &detectors[dk38b]);

	/* Initiate outgoing signals */
	Outgoing_signal_init(&os[ossegm1], "segm1", ossegm1+FCMAX);
	Outgoing_signal_init(&os[ossegm2], "segm2", ossegm2+FCMAX);
	Outgoing_signal_init(&os[ossegm3], "segm3", ossegm3+FCMAX);
	Outgoing_signal_init(&os[ossegm4], "segm4", ossegm4+FCMAX);
	Outgoing_signal_init(&os[ossegm5], "segm5", ossegm5+FCMAX);
	Outgoing_signal_init(&os[ossegm6], "segm6", ossegm6+FCMAX);
	Outgoing_signal_init(&os[ossegm7], "segm7", ossegm7+FCMAX);

	/* Initiate clock structure */
	Clock_CIF_init(clock);
}