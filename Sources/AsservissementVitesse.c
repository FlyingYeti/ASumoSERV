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
sPID PIDV1, PIDV2;
#else
sPID_ PIDV1, PIDV2;
#endif

float kCoeffs1V[] = {0, 0, 0};
float kCoeffs2V[] = {0, 0, 0};

void runAsservVitesse()
{
    float v1;
    float v2;
    transformVRoues(vc,wc,&v1,&v2);
    setConsignePIDgd(v1,v2);
    runPIDs();
    setPWMs();
}

void voidrunAsservVitesse()
{
    setConsignePIDgd(vit->v1,vit->v2);
#ifdef PID_
    resetPID_IVal(&PIDV1);
    resetPID_IVal(&PIDV2);
#endif
    runPIDs();
}

void initAsservVitesse(void) {
    /*
    Step 1: Initialize the PID data structure, PID
     */
    vit = getVitesse();

    kCoeffs1V[0] = 0.4; // 1.125
    kCoeffs1V[1] = 0.0836;
    kCoeffs1V[2] = 0.;
    
    kCoeffs2V[0] = 0.4;
    kCoeffs2V[1] = 0.0836;
    kCoeffs2V[2] = 0.;
#ifndef PID_
    initPID(&PIDV1); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDV1, kCoeffs1V); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDV1, vit->v1);
    
    initPID(&PIDV2); /*Clear the controller history and the controller output */
    setPIDCoeffs(&PIDV2, kCoeffs2V); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPIDMeas(&PIDV2, vit->v2);
#else
    initPID_(&PIDV1); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDV1, kCoeffs1V); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDV1, vit->v1);

    initPID_(&PIDV2); /*Clear the controller history and the controller output */
    setPID_Coeffs(&PIDV2, kCoeffs2V); /*Derive the a,b, & c coefficients from the Kp, Ki & Kd */
    setPID_Meas(&PIDV2, vit->v2);

    setPID_Overshoot(&PIDV1,1);
    setPID_OvershootVal(&PIDV1, 10.0);

    setPID_Overshoot(&PIDV2,1);
    setPID_OvershootVal(&PIDV2, 10.0);
#endif

    setConsignePIDgd(0.0,0.0);
}

void setConsignePIDgd(float vg, float vd)
{
#ifndef PID_
    setPIDRef(&PIDV1,vg); /*Set the Reference Input for your controller */
    setPIDRef(&PIDV2,vd); /*Set the Reference Input for your controller */
#else
    setPID_Ref(&PIDV1,vg); /*Set the Reference Input for your controller */
    setPID_Ref(&PIDV2,vd); /*Set the Reference Input for your controller */
#endif
}

void runPIDs(void)
{
#ifndef PID_
    setPIDMeas(&PIDV1, vit->v1);
    setPIDMeas(&PIDV2, vit->v2);
    computePID(&PIDV1);
    computePID(&PIDV2);
#else
    setPID_Meas(&PIDV1, vit->v1);
    setPID_Meas(&PIDV2, vit->v2);
    computePID_(&PIDV1);
    computePID_(&PIDV2);
#endif
}

void setPWMs(void)
{
#ifndef PID_
    setSpeed1((int)(getPIDOut(&PIDV1) * MAXDC));
    setSpeed2((int)(getPIDOut(&PIDV2) * MAXDC));
#else
    setSpeed1((int)(getPID_Out(&PIDV1) * MAXDC));
    setSpeed2((int)(getPID_Out(&PIDV2) * MAXDC));
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
    
    kCoeffsv[0] = 1.0;
    kCoeffsv[1] = 0.25;
    kCoeffsv[2] = 0.0;
    
    kCoeffsw[0] = 1.0;
    kCoeffsw[1] = 0.25;
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
    float v1, v2;
#ifndef PID_
    transformVRoues(getPIDOut(&PIDv), getPIDOut(&PIDw), &v1, &v2);
#else
    transformVRoues(getPID_Out(&PIDv), getPID_Out(&PIDw), &v1, &v2);
#endif
    setSpeed1((int)(v1 * MAXDC));
    setSpeed2((int)(v2 * MAXDC));
}

#endif