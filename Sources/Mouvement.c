/*
 * File:   Mouvement.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */

#include <xc.h>
#include <Generic.h>
#include <qei.h>
#include <timer.h>
#include <pps.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Headers/Mouvement.h"
#include "../Headers/UART.h"
#include "../Headers/PWM.h"
#include "../Headers/math.h"

static enc_cnt enc_Cnt1;
static enc_cnt enc_Cnt2;
static enc_cnt AngPos1[2]; // Two variables are used for Speed Calculation
static enc_cnt AngPos2[2]; // Two variables are used for Speed Calculation

#define     GAIN1       1.0
#define     GAIN2       1.0


// Vitesse des roues codeuses
static float v1;
static float v2;


static float DAngle1 = 0.0;
static float DAngle2 = 0.0;



Position position;
Vitesse vitesse;


void OpenQEI(void)
{
    MAX1CNT = 0xFFFF;
    MAX2CNT = 0xFFFF;

    POS1CNT = 0x0000;
    POS2CNT = 0x0000;

    enc_Cnt1.cnt = 0;
    enc_Cnt2.cnt = 0;
    AngPos1[0].cnt = 0;
    AngPos1[1].cnt = 0;
    AngPos2[0].cnt = 0;
    AngPos2[1].cnt = 0;

    PPSInput(IN_FN_PPS_QEA1,IN_PIN_PPS_RP6);
    PPSInput(IN_FN_PPS_QEB1,IN_PIN_PPS_RP7);
    PPSInput(IN_FN_PPS_QEB2,IN_PIN_PPS_RP8);
    PPSInput(IN_FN_PPS_QEA2,IN_PIN_PPS_RP9);

    unsigned int config1;
    unsigned int config2;
    config1 = QEI_MODE_x4_MATCH & QEI_NORMAL_IO & QEI_IDLE_CON & QEI_INDEX_RESET_DISABLE;
    config2 = QEI_QE_CLK_DIVIDE_1_256 & QEI_QE_OUT_ENABLE & POS_CNT_ERR_INT_DISABLE;

    OpenQEI1(config1 & QEI_INPUTS_SWAP,config2);
    OpenQEI2(config1 & QEI_INPUTS_NOSWAP,config2);
    ConfigIntQEI1(QEI_INT_PRI_6 & QEI_INT_ENABLE);
    ConfigIntQEI2(QEI_INT_PRI_6 & QEI_INT_ENABLE);
    
    
    /* Initialisation du timer de mise à jour des variables de mouvement toutes les 5ms */
    OpenTimer1(T1_OFF & T1_GATE_OFF & T1_IDLE_CON & T1_PS_1_64 & T1_SOURCE_INT,3124);
    ConfigIntTimer1(T1_INT_PRIOR_5 & T1_INT_ON);
    T1CONbits.TON = 1;  /* Turn on timer 1 */

    /* On ouvre le Timer4 qui envoie la position toutes les 50ms */
    OpenTimer4(T4_OFF & T4_GATE_OFF & T4_IDLE_CON & T4_SOURCE_INT & T4_PS_1_256 & T4_32BIT_MODE_OFF, 23436);
    ConfigIntTimer4(T4_INT_PRIOR_2 & T4_INT_ON); //Interruption ON et priorité 3
    T4CONbits.TON = 1;  /* Turn on timer 4 */
}
void closeQEI(void)
{
    CloseQEI1();
    CloseQEI2();
}


/* Interruptions de gestion des over/underflow de POSCNT */
void __attribute__((interrupt,no_auto_psv)) _QEI1Interrupt(void)
{
    DisableIntQEI1;
    if(QEI1CONbits.UPDN)
    {
        enc_Cnt1.count_ints.overflow++;
    }
    else
    {
        enc_Cnt1.count_ints.overflow--;
    }
    
    _QEI1IF = 0;

    EnableIntQEI1;
}
void __attribute__((interrupt,no_auto_psv)) _QEI2Interrupt(void)
{
    DisableIntQEI2;
    if(QEI2CONbits.UPDN)
    {
        enc_Cnt2.count_ints.overflow++;
    }
    else
    {
        enc_Cnt2.count_ints.overflow--;
    }

    _QEI2IF = 0;

    EnableIntQEI2;
}


void __attribute__((interrupt,auto_psv)) _T1Interrupt(void)
{
    DisableIntQEIs

    /* Calcul de la position des roues */
    enc_Cnt1.count_ints.poscnt = (unsigned int)POS1CNT;
    enc_Cnt2.count_ints.poscnt = (unsigned int)POS2CNT;

    AngPos1[1] = AngPos1[0];
    AngPos1[0] = enc_Cnt1;

    AngPos2[1] = AngPos2[0];
    AngPos2[0] = enc_Cnt2;

    EnableIntQEIs
   
    DAngle1 = GAIN1 * ((float)(AngPos1[0].cnt - AngPos1[1].cnt)) * 2.0 * PI / ((float)MAX_CNT_PER_REV);
    DAngle2 = GAIN2 * ((float)(AngPos2[0].cnt - AngPos2[1].cnt)) * 2.0 * PI / ((float)MAX_CNT_PER_REV);

    // Calcul des vitesses des roues codeuses
    v1 = R_ROUE * DAngle1 / DT;
    v2 = R_ROUE * DAngle2 / DT;

    float vdt;
    float wdt;
    vdt = (DAngle1 + DAngle2) * R_ROUE / 2.0;
    wdt = (DAngle1 - DAngle2) * R_ROUE / ENTRAXE;

    // calcul de la position
    position.x += vdt * cos(position.t);
    position.y += vdt * sin(position.t);
    position.t += wdt;
    position.p1 = ((float) AngPos1[0].cnt) * R_ROUE * PI * 2.0 / ((float)MAX_CNT_PER_REV);
    position.p2 = ((float) AngPos2[0].cnt) * R_ROUE * PI * 2.0 / ((float)MAX_CNT_PER_REV);
    position.l += vdt;

    // calcul de la vitesse
    vitesse.v = vdt / DT;
    vitesse.w = wdt / DT;
    vitesse.v1 = v1;
    vitesse.v2 = v2;


    _T1IF = 0; // Clear timer 1 interrupt flag
}

void resetOdometrie() {
    position.x = 0.;
    position.y = 0.;
    position.t = 0.;
    position.p1 = 0.;
    position.p2 = 0.;
    position.l = 0.;

    vitesse.v = 0.;
    vitesse.w = 0.;
    vitesse.v1 = 0.;
    vitesse.v2 = 0.;
}
void initOdometrie() __attribute__((alias("resetOdometrie")));

void sendOdometrie() {
    char transmit[200];
    sprintf(transmit, "X%fY%fT%fV%fW%f\n", (double)position.x, (double)position.y, (double)position.t, (double)vitesse.v, (double)vitesse.w);

    putsUART(transmit);
}

void transformVRoues(float v, float w, float *vg, float *vd) {
    *vg = v - ENTRAXE * w / 2.0;
    *vd = v + ENTRAXE * w / 2.0;
}

void transformVMots(float v, float w, float *vg, float *vd) {
    *vg = v - ENTRAXEM * w / 2.0;
    *vd = v + ENTRAXEM * w / 2.0;
}

Vitesse* getVitesse(void)
{
    return &vitesse;
}

void setPosition(float x, float y, float theta)
{
    position.x = x;
    position.y = y;
    position.t = theta;
}

Position* getPosition(void)
{
    return &position;
}

void __attribute__((interrupt,no_auto_psv)) _T4Interrupt(void)
{
    char transmit[200];
    sprintf(transmit, "X%fY%fT%fV%fW%f\n", (double)position.x, (double)position.y, (double)position.t, (double)vitesse.v, (double)vitesse.w);

    putsUART(transmit);

    IFS1bits.T4IF = 0; /* Clear timer 4 interrupt flag*/
}