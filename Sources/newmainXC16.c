/*
 * File:   newmainXC16.c
 * Author: Michel "FlyingYeti" Torelli
 *
 * Created on 4 mars 2014, 18:33
 */
#include <xc.h>
#include <Generic.h>
#include <libpic30.h>
#include "../Headers/Init.h"
#include "../Headers/PWM.h"
#include "../Headers/AsservissementVitesse.h"
#include "../Headers/Mouvement.h"
#include "../Headers/UART.h"
#include <stdio.h>
#include <stdlib.h>

//                           // Boot Code Segment Configuration Register
//_FBS( RBS_NO_RAM                // No boot segment Data Ram
//   & BSS_NO_FLASH              // No boot Segment Program Memory
//   & BWRP_WRPROTECT_OFF)       // Boot Write protection disabled
//                           // Secure Code Segment Program Flash
//_FSS( RSS_NO_RAM               // No secure segment data ram
//   & SSS_NO_FLASH              // No secure segment
//   & SWRP_WRPROTECT_OFF)       // Write protect disabled
//                           // General Code Segment Configuration Register
//_FGS( GSS_OFF                   // User program memory not code-protected
//   & GCP_OFF                   // Code protect - in header..not in config window
//   & GWRP_OFF)                 // General segment write protect disabled
                           // Oscillator Source and Start Up Selection Register
_FOSCSEL( IESO_ON               // 2 speed oscillator startup enabled
   & FNOSC_PRIPLL)             // PRI ^(Primary oscillator (XT, HS, EC) w/ PLL)
                           // Oscillator Configuration Register
_FOSC( FCKSM_CSDCMD            // Clock switching and monitor both disabled
   & IOL1WAY_OFF               // OFF = allow multiple remappable I/O
    & OSCIOFNC_OFF             // OSCO pin has clock output function
    & POSCMD_XT)               // XT Oscillator mode
                           // Watchdog Timer Configuration Register
_FWDT( FWDTEN_OFF              // WDT disabled
   & WINDIS_OFF                // Windowed WDT disabled
   & WDTPRE_PR128              // WDT pre-scaler 1:128
   & WDTPOST_PS32768)          // WDT post-scaler 1:32, 768
                           // POR Configuration Register
_FPOR( FPWRT_PWR64            // Power-on Reset value..128ms
   & ALTI2C_ON                 // I2C mapped to SDA1/SCL1
   & LPOL_ON                   // PWM module low side output pins have active-high output polarity
   & HPOL_ON                   // PWM module high side output pins have active-high output polarity
   & PWMPIN_OFF)                // PWM module pins controlled by PORT register at device Reset
                           // In-Circuit Debugger Configuration Register
_FICD( JTAGEN_OFF              // JTAG is disabled
   & ICS_PGD1)                 // ICD communication on PGC1/EMUC1 and PGD1/EMUD1


int main(void)
{
    Init();
    while(1);
    return 0;
}
