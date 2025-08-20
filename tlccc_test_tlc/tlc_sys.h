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

#ifndef TLC_H_INCLUDED
#define TLC_H_INCLUDED

#define sg01   0
#define sg02   1
#define sg03   2
#define sg05   3
#define sg06   4
#define sg07   5
#define sg08   6
#define sg09   7
#define sg11   8
#define sg12   9
#define sg24  10
#define sg28  11
#define sg34  12
#define sg38  13
#define SGMAX 14

#define ossegm1 0
#define ossegm2 1
#define ossegm3 2
#define ossegm4 3
#define ossegm5 4
#define ossegm6 5
#define ossegm7 6
#define OSMAX   SGMAX+7

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
#define DMAX 28

#define ISMAX DMAX+0

#define TMMAX 1

#define SWMAX 1

#define PRMMAX 1

#define ML1 0
#define ML2 1
#define ML3 2
#define ML4 3
#define MLMAX 4

/* TLCCC includes */
#include "tlccc_main.h"
#include "tlccc_clock.h"
#include "tlccc_sg_func.h"
#include "tlccc_det_func.h"
#include "tlccc_timer_func.h"
#include "tlccc_modules_func.h"
#include "tlccc_prm_func.h"
#include "tlccc_switch_func.h"
#include "tlccc_cif.h"

/* Function declarations */
void application_init(SIGNALGROUP signalgroups[], DETECTOR detectors[], OUTGOING_SIGNAL os[], MODULEMILL * modulemill, MODULE modules[], CLOCK * clock);
void application_exit(void);

#endif // TLC_H_INCLUDED