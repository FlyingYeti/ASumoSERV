/*
 * File:   PID_.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 20 mai 2014, 23:59
 */

#ifndef PID__H
#define	PID__H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct sPID_ {
        float pid[3];
        float i;
        float e;
        char overshoot;
        float overshootval;
        float output;
        float reference;
        float measure;
    } sPID_;

    extern void initPID_(sPID_*);
    extern void setPID_Coeffs(sPID_* , float*);
    extern void setPID_Overshoot(sPID_* , char);
    extern void setPID_OvershootVal(sPID_* , float);
    extern void resetPID_IVal(sPID_*);
    extern void setPID_Ref(sPID_* , float);
    extern void setPID_Meas(sPID_* , float);
    extern float getPID_Out(sPID_*);
    extern void computePID_(sPID_* );

#ifdef	__cplusplus
}
#endif

#endif	/* PID__H */

