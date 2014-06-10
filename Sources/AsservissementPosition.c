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
sPID PIDP1, PIDP2;
#else
sPID_ PIDP1, PIDP2;
#endif

static float kCoeffs1P[] = {0, 0, 0};
static float kCoeffs2P[] = {0, 0, 0};

void runAsservPosition()
{
    float dl = lc - l0;
    float dt = tc - t0;
    float dp1 = dl + ENTRAXE * dt / 2;
    float dp2 = dl - ENTRAXE * dt / 2;
    setConsignePIDgd(dp1, dp2);
    runPIDs();
    setPWMs();
}

void voidrunAsservPosition(void)
{
    setConsignePIDgd(pos->p1, pos->p2);
#ifdef PID_
    resetPID_IVal(&PIDP1);
    resetPID_IVal(&PIDP2);
#endif
    runPIDs();
}

void initAsservPosition(void) {
    /*
    Step 1: Initialize the PID data structure, PID
     */
    pos = getPosition();

    kCoeffs1P[0] = 0.25;
    kCoeffs1P[1] = 0.;
    kCoeffs1P[2] = 1.;

    kCoeffs2P[0] = .25;
    kCoeffs2P[1] = 0.;
    kCoeffs2P[2] = 1.;
#ifndef PID_
    initPID(&PIDP1); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDP1, kCoeffs1P); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDP1, pos->p1);

    initPID(&PIDP2); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDP2, kCoeffs2P); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDP2, pos->p2);
#else
    initPID_(&PIDP1); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDP1, kCoeffs1P); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDP1, pos->p1);

    initPID_(&PIDP2); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDP2, kCoeffs2P); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDP2, pos->p2);

    setPID_Overshoot(&PIDP1,1);
    setPID_OvershootVal(&PIDP1, 10.0);

    setPID_Overshoot(&PIDP2,1);
    setPID_OvershootVal(&PIDP2, 10.0);
#endif

    setConsignePIDgd(0.0,0.0);
}

void setConsignePIDgd(float p1, float p2)
{
#ifndef PID_
    setPIDRef(&PIDP1,p1); /*Set the Reference Input for your controller */
    setPIDRef(&PIDP2,p2); /*Set the Reference Input for your controller */
#else
    setPID_Ref(&PIDP1,p1); /*Set the Reference Input for your controller */
    setPID_Ref(&PIDP2,p2); /*Set the Reference Input for your controller */
#endif
}

void runPIDs(void) {
#ifndef PID_
    setPIDMeas(&PIDP1, pos->p1);
    setPIDMeas(&PIDP2, pos->p2);
    computePID(&PIDP1);
    computePID(&PIDP2);
#else
    setPID_Meas(&PIDP1, pos->p1);
    setPID_Meas(&PIDP2, pos->p2);
    computePID_(&PIDP1);
    computePID_(&PIDP2);
#endif
}

void setPWMs(void)
{
#ifndef PID_
    setSpeed1((int)(getPIDOut(&PIDP1) * MAXDC));
    setSpeed2((int)(getPIDOut(&PIDP2) * MAXDC));
#else
    setSpeed1((int)(getPID_Out(&PIDP1) * MAXDC));
    setSpeed2((int)(getPID_Out(&PIDP2) * MAXDC));
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
float p = 2;

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
    float v1, v2;
#ifndef PID_
    v1 = getPIDOut(&PIDl) + getPIDOut(&PIDt) * ENTRAXE / 2;
    v2 = getPIDOut(&PIDl) - getPIDOut(&PIDt) * ENTRAXE / 2;
#else
    v1 = getPID_Out(&PIDl) + getPID_Out(&PIDt) * ENTRAXE / 2;
    v2 = getPID_Out(&PIDl) - getPID_Out(&PIDt) * ENTRAXE / 2;
#endif
    setSpeed1((int)(v1 * MAXDC));
    setSpeed2((int)(v2 * MAXDC));
}

#endif