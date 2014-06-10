/*
 * File:   Init.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 13 mai 2014, 13:33
 */
#include <xc.h>
#include <Generic.h>
#include <pps.h>
#include <libpic30.h>
#include "../Headers/Clock.h"
#include "../Headers/PWM.h"
#include "../Headers/UART.h"
#include "../Headers/Mouvement.h"
#include "../Headers/ADC.h"
#include "../Headers/Asservissement.h"
#include "../Headers/PID.h"
#include "../Headers/Interpreter.h"

void Init(void)
{
    _NSTDIS = 0;
    mSET_CPU_IP(0);
    _NSTDIS = 1;
    PPSUnLock;
    Clock_Init();
    OpenQEI();
    OpenUART();
    OpenPWM();
    PPSLock;
    
    initInterpreter();
    initOdometrie();
    initAsservissement();
    
    __delay32(1000000);       /*kill some time here- make sure PPS is set up*/

    putsUART("A");
    enablePWM;
    ch1Run;
    ch2Run;
}