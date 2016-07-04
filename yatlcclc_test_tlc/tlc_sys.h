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

#ifndef TLC_H_INCLUDED
#define TLC_H_INCLUDED

/* Defines for */

#define fc01   0
#define fc02   1
#define fc03   2
#define fc05   3
#define fc06   4
#define fc07   5
#define fc08   6
#define fc09   7
#define fc11   8
#define fc12   9
#define fc24  10
#define fc28  11
#define fc34  12
#define fc38  13
#define FCMAX 14

#define ossegm1 0
#define ossegm2 1
#define ossegm3 2
#define ossegm4 3
#define ossegm5 4
#define ossegm6 5
#define ossegm7 6
#define USMAX   FCMAX+7

#define d01_1 0
#define d01_2 1
#define d02_1 2
#define d02_2 3
#define d03_1 4
#define d03_2 5
#define d05_1 6
#define d05_2 7
#define d06_1 8
#define d06_2 9
#define d07_1 10
#define d07_2 11
#define d08_1 12
#define d08_2 13
#define d09_1 14
#define d09_2 15
#define d11_1 16
#define d11_2 17
#define d12_1 18
#define d12_2 19
#define d24_1 20
#define dk24  21
#define d28_1 22
#define dk28  23
#define dk34a 24
#define dk34b 25
#define dk38a 26
#define dk38b 27
#define DPMAX 28

#define ISMAX DPMAX+0

#define TMMAX 1

#define PARM1MAX 1

#define ML1 0
#define ML2 1
#define ML3 2
#define ML4 3
#define MLMAX 4

/* YATLCCLC includes */
#include "yatlcclc_main.h"
#include "yatlcclc_clock.h"
#include "yatlcclc_fc_func.h"
#include "yatlcclc_det_func.h"
#include "yatlcclc_timer_func.h"
#include "yatlcclc_modules_func.h"
#include "yatlcclc_cif.h"

/* Function declarations */
void application_init(PHASE phases[], DETECTOR detectors[], OUTGOING_SIGNAL os[], short CT_max[], MODULEMILL * modulemill, MODULE modules[], CLOCK * clock);

#endif // TLC_H_INCLUDED