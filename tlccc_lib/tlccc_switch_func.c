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

#include "tlccc_switch_func.h"

void Switch_init(SWITCH * _switch, const char * code, short setting)
{
    _switch->Code = (char *)malloc((strlen(code) + 1) * sizeof(char));
    snprintf(_switch->Code, strlen(code) + 1, "%s", code);

    _switch->Setting = setting;
}


void Switch_free(SWITCH * _switch)
{
    if (_switch->Code != NULL)
        free(_switch->Code);
}

void Switches_free(SWITCH switches[], short switches_count)
{
    int i;
    for (i = 0; i < switches_count; ++i)
    {
        Switch_free(&switches[i]);
    }
}