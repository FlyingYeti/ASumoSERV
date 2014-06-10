/*
 * File:   PID.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 20 mai 2014, 23:59
 */

#ifndef PID_H
#define	PID_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct sPID {
        float abc[3];
        float history[3];
        float output;
        float reference;
        float measure;
    } sPID;

    void initPID(sPID*);
    void setPIDCoeffs(sPID* , float*);
    void setPIDRef(sPID* , float);
    void setPIDMeas(sPID* , float);
    float getPIDOut(sPID*);
    void computePID(sPID* );

#ifdef	__cplusplus
}
#endif

#endif	/* PID_H */

