/*
 * File:   PWM.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define PER         0x3FF /* = 1023 */
    #define MAXDC       0x7FF/* = 2*PER+1 = 2047 */
    #define MAXUDC      0x5FF /* = 1023 */
    #define DCSTARTMIN  0x136 /* = 310 */
    #define DCZERO      0x066 /* = 102 */

    #define enablePWM                      P1TCONbits.PTEN = 1;
    #define disablePWM                     P1TCONbits.PTEN = 0;
    #define disablePWM2                    P2TCONbits.PTEN = 0;

    extern void OpenPWM(void);

    #define ch1Break                        P1OVDCONbits.POVD1L = 0;
    #define ch1Run                          P1OVDCONbits.POVD1L = 1;
    extern void setSpeed1(int);

    #define ch2Break                        P1OVDCONbits.POVD2L = 0;
    #define ch2Run                          P1OVDCONbits.POVD2L = 1;
    extern void setSpeed2(int);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

