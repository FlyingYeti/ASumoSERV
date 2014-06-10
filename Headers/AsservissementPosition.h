/*
 * File:   AsservissementPosition.h
 * Author: Paulo
 *
 * Created on 12 mai 2014, 11:21
 */

#ifndef ASSERVISSEMENTPOSITION_H
#define	ASSERVISSEMENTPOSITION_H

#ifdef	__cplusplus
extern "C" {
#endif

    #define MAXDIST 0.5
    #define MAXANGLE 2
    extern void initAsservPosition(void);
    extern void runAsservPosition(void);
    extern void setConsignePosition(float, float);
    extern void voidrunAsservPosition(void);

#ifdef	__cplusplus
}
#endif

#endif	/* ASSERVISSEMENTPOSITION_H */