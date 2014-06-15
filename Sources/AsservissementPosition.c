#define LT
#define PID_

#include <math.h>
#include "../Headers/math.h"
#include "../Headers/AsservissementPosition.h"

#ifndef PID_
#include "../Headers/PID.h"
#else
#include "../Headers/PID_.h"
#endif

#include "../Headers/PWM.h"
#include "../Headers/Mouvement.h"

static float lc, tc, l0, t0;
static Position *pos;

void setConsignePosition(float dl, float dt)
{
    float dlc = 0;
    float dtc = 0;
    if(dl>MAXDIST) dlc = MAXDIST;
    else if (dl<-MAXDIST) dlc = -MAXDIST;
    else dlc = dl;
    if(dt>MAXANGLE) dtc = MAXANGLE;
    else if (dt<-MAXANGLE) dtc = -MAXANGLE;
    else dtc = dt;

    l0 = pos->l;
    t0 = pos->t;
    lc = l0;
    tc = t0;
    lc += dlc;
    tc += dtc;
}

static void runPIDs(void);
static void setPWMs(void);

#ifndef LT

static void setConsignePIDgd(float, float);

#ifndef PID_
sPID PIDPd, PIDPg;
#else
sPID_ PIDPd, PIDPg;
#endif

static float kCoeffsgP[] = {0, 0, 0};
static float kCoeffsdP[] = {0, 0, 0};

void runAsservPosition()
{
    float dl = lc - l0;
    float dt = tc - t0;
    float dp1 = dl + ENTRAXE * dt / 2;
    float dp2 = dl - ENTRAXE * dt / 2;
    setConsignePIDgd(dp2, dp1);
    runPIDs();
    setPWMs();
}

void voidrunAsservPosition(void)
{
    setConsignePIDgd(pos->p2, pos->p1);
#ifdef PID_
    resetPID_IVal(&PIDPd);
    resetPID_IVal(&PIDPg);
#endif
    runPIDs();
}

void initAsservPosition(void) {
    /*
    Step 1: Initialize the PID data structure, PID
     */
    pos = getPosition();

    kCoeffsgP[0] = 0.25;
    kCoeffsgP[1] = 0.;
    kCoeffsgP[2] = 1.;

    kCoeffsdP[0] = .25;
    kCoeffsdP[1] = 0.;
    kCoeffsdP[2] = 1.;
#ifndef PID_
    initPID(&PIDPd); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDPd, kCoeffs1P); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDPd, pos->p1);

    initPID(&PIDPg); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDPg, kCoeffs2P); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDPg, pos->p2);
#else
    initPID_(&PIDPd); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDPd, kCoeffsdP); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDPd, pos->p1);

    initPID_(&PIDPg); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDPg, kCoeffsgP); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDPg, pos->p2);

    setPID_Overshoot(&PIDPd,1);
    setPID_OvershootVal(&PIDPd, 10.0);

    setPID_Overshoot(&PIDPg,1);
    setPID_OvershootVal(&PIDPg, 10.0);
#endif

    setConsignePIDgd(0.0,0.0);
}

void setConsignePIDgd(float g, float d)
{
#ifndef PID_
    setPIDRef(&PIDPd,d); /*Set the Reference Input for your controller */
    setPIDRef(&PIDPg,g); /*Set the Reference Input for your controller */
#else
    setPID_Ref(&PIDPd,d); /*Set the Reference Input for your controller */
    setPID_Ref(&PIDPg,g); /*Set the Reference Input for your controller */
#endif
}

void runPIDs(void) {
#ifndef PID_
    setPIDMeas(&PIDPd, pos->p1);
    setPIDMeas(&PIDPg, pos->p2);
    computePID(&PIDPd);
    computePID(&PIDPg);
#else
    setPID_Meas(&PIDPd, pos->p1);
    setPID_Meas(&PIDPg, pos->p2);
    computePID_(&PIDPd);
    computePID_(&PIDPg);
#endif
}

void setPWMs(void)
{
#ifndef PID_
    setSpeed1((int)(getPIDOut(&PIDPd) * MAXDC));
    setSpeed2((int)(getPIDOut(&PIDPg) * MAXDC));
#else
    setSpeed1((int)(getPID_Out(&PIDPd) * MAXDC));
    setSpeed2((int)(getPID_Out(&PIDPg) * MAXDC));
#endif
}

#else

static void setConsignePIDlt(float, float);

#ifndef PID_
sPID PIDl, PIDt;
#else
sPID_ PIDl, PIDt;
#endif

float kCoeffsl[] = {0, 0, 0};
float kCoeffst[] = {0, 0, 0};
float p = 10;

void runAsservPosition(void)
{
    setConsignePIDlt(lc,tc);
    runPIDs();
    setPWMs();
}

void voidrunAsservPosition(void)
{
    setConsignePIDlt(pos->l,pos->t);
#ifdef PID_
    resetPID_IVal(&PIDl);
    resetPID_IVal(&PIDt);
#endif
    runPIDs();
}

void initAsservPosition()
{
    /*
    Step 1: Initialize the PID data structure, PID
     */
    pos = getPosition();

    kCoeffsl[0] = p;
    kCoeffsl[1] = 0.049;
    kCoeffsl[2] = 0.0;

    kCoeffst[0] = p/2;
    kCoeffst[1] = 0.1;
    kCoeffst[2] = 0.0;

#ifndef PID_
    initPID(&PIDl); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDl, kCoeffsl); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDl, pos->l);

    initPID(&PIDt); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDt, kCoeffst); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDt, pos->T);
#else
    initPID_(&PIDl); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDl, kCoeffsl); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDl, pos->l);

    initPID_(&PIDt); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDt, kCoeffst); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDt, pos->t);

    setPID_Overshoot(&PIDl,1);
    setPID_OvershootVal(&PIDl, 1.);

    setPID_Overshoot(&PIDt,1);
    setPID_OvershootVal(&PIDt, 2.);
#endif

    setConsignePIDlt(0.0,0.0);
}

static void setConsignePIDlt(float l, float t)
{
#ifndef PID_
    setPIDRef(&PIDl,l); /*Set the Reference Input for your controller */
    setPIDRef(&PIDt,t); /*Set the Reference Input for your controller */
#else
    setPID_Ref(&PIDl,l); /*Set the Reference Input for your controller */
    setPID_Ref(&PIDt,t); /*Set the Reference Input for your controller */
#endif
}

void runPIDs(void)
{
#ifndef PID_
    setPIDMeas(&PIDl, pos->l);
    setPIDMeas(&PIDt, pos->t);
    computePID(&PIDl); /*Call the PID controller using the new measured input */
    computePID(&PIDt); /*Call the PID controller using the new measured input */
#else
    setPID_Meas(&PIDl, pos->l);
    setPID_Meas(&PIDt, pos->t);
    computePID_(&PIDl); /*Call the PID controller using the new measured input */
    computePID_(&PIDt); /*Call the PID controller using the new measured input */
#endif
}

void setPWMs(void) {
    float vg, vd;
#ifndef PID_
    transformVMots(getPIDOut(&PIDl), getPIDOut(&PIDt) * ENTRAXE / 2, &vg, &vd);
#else
    transformVMots(getPID_Out(&PIDl), getPID_Out(&PIDt) * ENTRAXE / 2, &vg, &vd);
#endif
    setSpeed1((int)(vd * MAXDC));
    setSpeed2((int)(vg * MAXDC));
}

#endif