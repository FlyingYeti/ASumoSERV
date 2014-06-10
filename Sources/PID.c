/*
 * File:   PID.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 20 mai 2014, 23:59
 */

#include <xc.h>
#include "../Headers/PID.h"

void initPID(sPID *spid)
{
    spid->abc[0] = 0.0;
    spid->abc[1] = 0.0;
    spid->abc[2] = 0.0;
    spid->history[0] = 0.0;
    spid->history[1] = 0.0;
    spid->history[2] = 0.0;
    spid->output = 0.0;
    spid->reference = 0.0;
    spid->measure = 0.0;
}

void setPIDCoeffs(sPID* spid, float* Kpid)
{
    spid->abc[2] = Kpid[2];
    spid->abc[1] = - (Kpid[0] + 2.0 * Kpid[2]);
    spid->abc[0] = Kpid[0] + Kpid[1] + Kpid[2];
}

void setPIDRef(sPID* spid, float ref)
{
    spid->reference = ref;
}

void setPIDMeas(sPID* spid, float meas)
{
    spid->measure = meas;
}

float getPIDOut(sPID* spid)
{
    return spid->output;
}

void computePID(sPID* spid)
{
    spid->history[2] = spid->history[1];
    spid->history[1] = spid->history[0];
    spid->history[0] = spid->reference - spid->measure;
    spid->output += spid->history[2] * spid->abc[2];
    spid->output +=  spid->history[1] * spid->abc[1];
    spid->output +=  spid->history[0] * spid->abc[0];
}