/* 
 * File:   Mouvement.h
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 20:53
 */

#ifndef MOUVEMENT_H
#define	MOUVEMENT_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef union
    {
        struct {
              unsigned int poscnt:16;
              int overflow:16;
        } count_ints;
        long cnt;
    } enc_cnt;

    typedef struct Position {
        float x, y, t, p1, p2, l;
    } Position;

    typedef struct Vitesse {
        float v, w, v1, v2;
    } Vitesse;

    extern void OpenQEI(void);
    extern void closeQEI(void);

    
    #define EnableIntQEI1                   _QEI1IE = 1;
    #define DisableIntQEI1                  _QEI1IE = 0;

    #define EnableIntQEI2                   _QEI2IE = 1;
    #define DisableIntQEI2                  _QEI2IE = 0;

    #define EnableIntQEIs                   _QEI1IE = 1;_QEI2IE = 1;
    #define DisableIntQEIs                  _QEI1IE = 0;_QEI2IE = 0;

    #define MAX_CNT_PER_REV (500 * 4)



/*Paramètres géométriques du robot*/
#define R_ROUE      0.027
#define ENTRAXE     0.3458
#define ENTRAXEM    0.3

/* Interval de temps d'execution de l'odométrie*/
#define DT 0.005

    extern void initOdometrie(void);
    extern void resetOdometrie(void);

    extern void sendOdometrie(void);       // Envoie la position et la vitesse du robot sur le port série

    extern void transformVRoues(float, float, float*, float*);     // Renvoie la vitesse des roues
    extern void transformVMots(float, float, float*, float*);
    extern Vitesse* getVitesse(void);

    extern void setPosition(float, float, float);
    extern Position* getPosition(void);

#ifdef	__cplusplus
}
#endif

#endif	/* MOUVEMENT_H */

