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

#include "tlccc_det_func.h"

void Detector_init(DETECTOR * detector, const char * code, short * cif_is_val, short type, short request, short extend, short tdbmax, short tdhmax, short togmax, short tbgmax)
{
    char temp[128];

    detector->Code = malloc((strlen(code) + 1) * sizeof(char));
    snprintf(detector->Code, (strlen(code) + 1), "%s", code);

    detector->Type = type;
    detector->Request = request;
    detector->Extend = extend;

    detector->CIF_IS_value = cif_is_val;

    snprintf(temp, 128, "TOCC%s", detector->Code);
    Timer_init(&detector->Timer_Occ, temp, tdbmax, TE_type);
    snprintf(temp, 128, "TGAP%s", detector->Code);
    Timer_init(&detector->Timer_Gap, temp, tdhmax, TE_type);
    snprintf(temp, 128, "TERH%s", detector->Code);
    Timer_init(&detector->Timer_ErrorHi, temp, tbgmax, TE_type);
    snprintf(temp, 128, "TERL%s", detector->Code);
    Timer_init(&detector->Timer_ErrorLo, temp, togmax, TE_type);
}

void Detector_free(DETECTOR * detector)
{
    if (detector->Code != NULL)
        free(detector->Code);
}

void Detectors_free(DETECTOR detectors[], short detector_count)
{
    int i;
    for (i = 0; i < detector_count; ++i)
    {
        Detector_free(&detectors[i]);
    }
}

void Detectors_update(DETECTOR detectors[], short detector_count)
{
    int i;
    for (i = 0; i < detector_count; ++i)
    {
        Detector_update(&detectors[i]);
    }
}

void Detector_update(DETECTOR * detector)
{
    /* Reset start/end states */
    detector->PresenceStart = FALSE;
    detector->PresenceEnd = FALSE;

    /* Actions on detector newly presence detected */
    if (((*detector->CIF_IS_value) & CIF_DET_BEZET) && detector->Presence == FALSE)
    {
        detector->Presence = TRUE;
        detector->PresenceStart = TRUE;
        if (detector->Timer_Occ.Maximum > 0)
            detector->Timer_Occ.Restart = TRUE;
        else
            detector->Occupied = TRUE;
        detector->Timer_ErrorLo.Stop = TRUE;
        detector->Timer_ErrorHi.Restart = TRUE;
    }

    /* Actions on detector no more presence detected */
    if (!((*detector->CIF_IS_value) & CIF_DET_BEZET) && detector->Presence == TRUE)
    {
        detector->Presence = FALSE;
        detector->Occupied = FALSE;
        detector->PresenceEnd = TRUE;
        detector->Timer_Occ.Stop = TRUE;
        detector->Timer_Gap.Restart = TRUE;
        detector->Timer_ErrorHi.Stop = TRUE;
        detector->Timer_ErrorLo.Restart = TRUE;
    }

    /* Set detector occupied if presence detected, and Timer_occ ends */
    if (detector->Presence == TRUE)
    {
        if (detector->Timer_Occ.Ended) detector->Occupied = TRUE;
    }

    /* Set Gap variable */
    if (detector->Presence || (detector->Timer_Gap.Maximum > 0 && (detector->Timer_Gap.Restart || detector->Timer_Gap.Active)))
    {
        detector->GapRunning = TRUE;
    }
    else
    {
        detector->GapRunning = FALSE;
    }
}

void Detectors_timers_update(DETECTOR detectors[], short detector_count, CLOCK * clock)
{
    int i;
    for (i = 0; i < detector_count; ++i)
    {
        Detector_timers_update(&detectors[i], clock);
    }
}

void Detector_timers_update(DETECTOR * detector, CLOCK * clock)
{
    Timer_update(&detector->Timer_Gap, clock);
    Timer_update(&detector->Timer_Occ, clock);
    Timer_update(&detector->Timer_ErrorHi, clock);
    Timer_update(&detector->Timer_ErrorLo, clock);
}