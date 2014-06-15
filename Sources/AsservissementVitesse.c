//#define VW
#define PID_


#include "../Headers/AsservissementVitesse.h"

#ifndef PID_
#include "../Headers/PID.h"
#else
#include "../Headers/PID_.h"
#endif

#include "../Headers/PWM.h"
#include "../Headers/Mouvement.h"

static float vc, wc;
static Vitesse *vit;

void setConsigneVitesse(float v, float w)
{
    if(v>MAXSPEED) vc = MAXSPEED;
    else if (v<-MAXSPEED) vc = -MAXSPEED;
    else vc = v;
    if(w>MAXANGVEL) wc = MAXANGVEL;
    else if (w<-MAXANGVEL) wc = -MAXANGVEL;
    else wc = w;
}


static void runPIDs(void);
static void setPWMs(void);

#ifndef VW

static void setConsignePIDgd(float, float);

#ifndef PID_
sPID PIDVd, PIDVg;
#else
sPID_ PIDVd, PIDVg;
#endif

float kCoeffsdV[] = {0, 0, 0};
float kCoeffsgV[] = {0, 0, 0};

void runAsservVitesse()
{
    float vd;
    float vg;
    transformVRoues(vc,wc,&vg,&vd);
    setConsignePIDgd(vg,vd);
    runPIDs();
    setPWMs();
}

void voidrunAsservVitesse()
{
    setConsignePIDgd(vit->v2,vit->v1);
#ifdef PID_
    resetPID_IVal(&PIDVd);
    resetPID_IVal(&PIDVg);
#endif
    runPIDs();
}

void initAsservVitesse(void) {
    /*
    Step 1: Initialize the PID data structure, PID
     */
    vit = getVitesse();

    kCoeffsdV[0] = 0.4; // 1.125
    kCoeffsdV[1] = 0.0836;
    kCoeffsdV[2] = 0.;
    
    kCoeffsgV[0] = 0.4;
    kCoeffsgV[1] = 0.0836;
    kCoeffsgV[2] = 0.;
#ifndef PID_
    initPID(&PIDVd); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDVd, kCoeffsdV); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDVd, vit->v1);
    
    initPID(&PIDVg); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDVg, kCoeffsgV); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDVg, vit->v2);
#else
    initPID_(&PIDVd); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDVd, kCoeffsdV); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDVd, vit->v1);

    initPID_(&PIDVg); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDVg, kCoeffsgV); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDVg, vit->v2);

    setPID_Overshoot(&PIDVd,1);
    setPID_OvershootVal(&PIDVd, 10.0);

    setPID_Overshoot(&PIDVg,1);
    setPID_OvershootVal(&PIDVg, 10.0);
#endif

    setConsignePIDgd(0.0,0.0);
}

void setConsignePIDgd(float vg, float vd)
{
#ifndef PID_
    setPIDRef(&PIDVd,vd); /*Set the Reference Input for your controller */
    setPIDRef(&PIDVg,vg); /*Set the Reference Input for your controller */
#else
    setPID_Ref(&PIDVd,vd); /*Set the Reference Input for your controller */
    setPID_Ref(&PIDVg,vg); /*Set the Reference Input for your controller */
#endif
}

void runPIDs(void)
{
#ifndef PID_
    setPIDMeas(&PIDVd, vit->v1);
    setPIDMeas(&PIDVg, vit->v2);
    computePID(&PIDVd);
    computePID(&PIDVg);
#else
    setPID_Meas(&PIDVd, vit->v1);
    setPID_Meas(&PIDVg, vit->v2);
    computePID_(&PIDVd);
    computePID_(&PIDVg);
#endif
}

void setPWMs(void)
{
#ifndef PID_
    setSpeed1((int)(getPIDOut(&PIDVd) * MAXDC));
    setSpeed2((int)(getPIDOut(&PIDVg) * MAXDC));
#else
    setSpeed1((int)(getPID_Out(&PIDVd) * MAXDC));
    setSpeed2((int)(getPID_Out(&PIDVg) * MAXDC));
#endif
}

#else

static void setConsignePIDvw(float, float);

#ifndef PID_
sPID PIDv, PIDw;
#else
sPID_ PIDv, PIDw;
#endif

float kCoeffsv[] = {0, 0, 0};
float kCoeffsw[] = {0, 0, 0};

void runAsservVitesse()
{
    setConsignePIDvw(vc, wc);
    runPIDs();
    setPWMs();
}

void voidrunAsservVitesse()
{
    setConsignePIDvw(vit->v,vit->w);
#ifdef PID_
    resetPID_IVal(&PIDv);
    resetPID_IVal(&PIDw);
#endif
    runPIDs();
}

void initAsservVitesse(void)
{
    /*
    Step 1: Initialize the PID data structure, PID
     */
    vit = getVitesse();

    kCoeffsv[0] = 0.4;
    kCoeffsv[1] = 0.0836;
    kCoeffsv[2] = 0.0;
    
    kCoeffsw[0] = 0.4*2./ENTRAXE;
    kCoeffsw[1] = 0.0836*2./ENTRAXE;
    kCoeffsw[2] = 0.0;

#ifndef PID_
    initPID(&PIDv); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDv, kCoeffsv); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDv, vit->v);

    initPID(&PIDw); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDw, kCoeffsw); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDw, vit->w);
#else
    initPID_(&PIDv); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDv, kCoeffsv); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDv, vit->v);

    initPID_(&PIDw); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDw, kCoeffsw); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDw, vit->w);

    setPID_Overshoot(&PIDv,1);
    setPID_OvershootVal(&PIDv, 10.);

    setPID_Overshoot(&PIDw,1);
    setPID_OvershootVal(&PIDw, 10.);
#endif

    setConsignePIDvw(0.0,0.0);
}

static void setConsignePIDvw(float v, float w)
{
#ifndef PID_
    setPIDRef(&PIDv,v); /*Set the Reference Input for your controller */
    setPIDRef(&PIDw,w); /*Set the Reference Input for your controller */
#else
    setPID_Ref(&PIDv,v); /*Set the Reference Input for your controller */
    setPID_Ref(&PIDw,w); /*Set the Reference Input for your controller */
#endif
}

void runPIDs(void)
{
#ifndef PID_
    setPIDMeas(&PIDv, vit->v);
    setPIDMeas(&PIDw, vit->w);
    computePID(&PIDv); /*Call the PID controller using the new measured input */
    computePID(&PIDw);
#else
    setPID_Meas(&PIDv, vit->v);
    setPID_Meas(&PIDw, vit->w);
    computePID_(&PIDv); /*Call the PID controller using the new measured input */
    computePID_(&PIDw);
#endif
}

void setPWMs(void) {
    float vg, vd;
#ifndef PID_
    transformVMots(getPIDOut(&PIDv), getPIDOut(&PIDw), &vg, &vd);
#else
    transformVMots(getPID_Out(&PIDv), getPID_Out(&PIDw), &vg, &vd);
#endif
    setSpeed1((int)(vd * MAXDC));
    setSpeed2((int)(vg * MAXDC));
}

#endif