/* 
 * File:   AsservissementVitesse.h
 * Author: Paulo
 *
 * Created on 12 mai 2014, 11:25
 */

#ifndef ASSERVISSEMENTVITESSE_H
#define	ASSERVISSEMENTVITESSE_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define MAXSPEED    0.5
    #define MAXANGVEL   3.2
    extern void initAsservVitesse(void);
    extern void runAsservVitesse(void);
    extern void setConsigneVitesse(float, float);
    extern void voidrunAsservVitesse(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ASSERVISSEMENTVITESSE_H */

