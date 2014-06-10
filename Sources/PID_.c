/*
 * File:   PID_.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 20 mai 2014, 23:59
 */

#include <xc.h>
#include "../Headers/PID_.h"

void initPID_(sPID_ *spid)
{
    spid->pid[0] = 0.0;
    spid->pid[1] = 0.0;
    spid->pid[2] = 0.0;
    spid->i= 0.0;
    spid->e= 0.0;
    spid->overshoot = 0;
    spid->overshootval = 0.0;
    spid->output = 0.0;
    spid->reference = 0.0;
    spid->measure = 0.0;
}

void setPID_Coeffs(sPID_* spid, float* Kpid)
{
    spid->pid[2] = Kpid[2];
    spid->pid[1] = Kpid[1];
    spid->pid[0] = Kpid[0];
}


void setPID_Overshoot(sPID_* spid, char os)
{
    spid->overshoot = os;
}

void setPID_OvershootVal(sPID_* spid, float os)
{
    spid->overshootval = os;
}

void resetPID_IVal(sPID_* spid)
{
    spid->i = 0;
}

void setPID_Ref(sPID_* spid, float ref)
{
    spid->reference = ref;
}

void setPID_Meas(sPID_* spid, float meas)
{
    spid->measure = meas;
}

float getPID_Out(sPID_* spid)
{
    return spid->output;
}

void computePID_(sPID_* spid)
{
    float e = spid->reference - spid->measure;
    spid->i  += e;
    if (spid->overshoot == 1)
    {
        if (spid->i > spid->overshootval)
        {
            spid->i = spid->overshootval;
        }
        else if (spid->i < -spid->overshootval)
        {
            spid->i = -spid->overshootval;
        }
    }
    spid->output = e * spid->pid[0];
    spid->output += spid->i * spid->pid[1];
    spid->output += (e - spid->e) * spid->pid[2];
    spid->e = e;
}