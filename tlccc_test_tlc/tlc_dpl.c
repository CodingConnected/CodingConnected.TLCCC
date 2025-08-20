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

#include "tlc_sys.h"

short X_is[ISMAX];
short Y_is[ISMAX];

short X_us[OSMAX];
short Y_us[OSMAX];

void DisplayParameters(void)
{
    X_us[sg01] = 295; Y_us[sg01] = 212;
    X_us[sg02] = 295; Y_us[sg02] = 232;
    X_us[sg03] = 295; Y_us[sg03] = 253;
    X_us[sg05] = 247; Y_us[sg05] = 370;
    X_us[sg06] = 226; Y_us[sg06] = 370;
    X_us[sg07] = 137; Y_us[sg07] = 295;
    X_us[sg08] = 137; Y_us[sg08] = 274;
    X_us[sg09] = 137; Y_us[sg09] = 254;
    X_us[sg11] = 186; Y_us[sg11] = 116;
    X_us[sg12] = 207; Y_us[sg12] = 116;
    X_us[sg24] = 196; Y_us[sg24] = 330;
    X_us[sg34] = 196; Y_us[sg34] = 346;
    X_us[sg28] = 190; Y_us[sg28] = 177;
    X_us[sg38] = 190; Y_us[sg38] = 158;

    X_us[ossegm1+SGMAX] = 22; Y_us[ossegm1+SGMAX] = 452;
    X_us[ossegm2+SGMAX] = 10; Y_us[ossegm2+SGMAX] = 461;
    X_us[ossegm3+SGMAX] = 31; Y_us[ossegm3+SGMAX] = 461;
    X_us[ossegm4+SGMAX] = 22; Y_us[ossegm4+SGMAX] = 473;
    X_us[ossegm5+SGMAX] = 10; Y_us[ossegm5+SGMAX] = 484;
    X_us[ossegm6+SGMAX] = 31; Y_us[ossegm6+SGMAX] = 484;
    X_us[ossegm7+SGMAX] = 22; Y_us[ossegm7+SGMAX] = 494;

    X_is[d01_1] = 287; Y_is[d01_1] = 210;
    X_is[d01_2] = 374; Y_is[d01_2] = 210;
    X_is[d02_1] = 287; Y_is[d02_1] = 232;
    X_is[d02_2] = 368; Y_is[d02_2] = 232;
    X_is[d03_1] = 287; Y_is[d03_1] = 252;
    X_is[d03_2] = 369; Y_is[d03_2] = 252;
    X_is[d05_1] = 248; Y_is[d05_1] = 362;
    X_is[d05_2] = 248; Y_is[d05_2] = 448;
    X_is[d06_1] = 227; Y_is[d06_1] = 362;
    X_is[d06_2] = 227; Y_is[d06_2] = 448;
    X_is[d07_1] = 147; Y_is[d07_1] = 296;
    X_is[d07_2] =  70; Y_is[d07_2] = 295;
    X_is[d08_1] = 147; Y_is[d08_1] = 274;
    X_is[d08_2] =  50; Y_is[d08_2] = 274;
    X_is[d09_1] = 147; Y_is[d09_1] = 253;
    X_is[d09_2] =  50; Y_is[d09_2] = 253;
    X_is[d11_1] = 185; Y_is[d11_1] = 143;
    X_is[d11_2] = 185; Y_is[d11_2] =  55;
    X_is[d12_1] = 206; Y_is[d12_1] = 143;
    X_is[d12_2] = 206; Y_is[d12_2] =  55;
    X_is[d24_1] = 171; Y_is[d24_1] = 331;
    X_is[dk24]  = 160; Y_is[dk24]  = 337;
    X_is[d28_1] = 263; Y_is[d28_1] = 175;
    X_is[dk28]  = 274; Y_is[dk28]  = 169;
    X_is[dk34a] = 168; Y_is[dk34a] = 351;
    X_is[dk34b] = 266; Y_is[dk34b] = 351;
    X_is[dk38a] = 168; Y_is[dk38a] = 153;
    X_is[dk38b] = 266; Y_is[dk38b] = 153;
}