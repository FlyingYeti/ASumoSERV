#include <xc.h>
#include <Generic.h>
#include <timer.h>
#include "../Headers/Asservissement.h"
#include "../Headers/AsservissementVitesse.h"
#include "../Headers/AsservissementPosition.h"
#include "../Headers/PID.h"

AsservType asservType;

void __attribute__((interrupt,no_auto_psv)) _T2Interrupt(void)
{
    if(asservType == ASSERV_POSITION)
    {
        runAsservPosition();
        voidrunAsservVitesse();
    }
    else if(asservType == ASSERV_VITESSE)
    {
        runAsservVitesse();
        voidrunAsservPosition();
    }
    
    IFS0bits.T2IF = 0; /* Clear timer 2 interrupt flag*/
}

void initAsservissement()
{
    initAsservVitesse();
    initAsservPosition();
    setConsigneVitesse(0.0,0.0);
    setConsignePosition(0.0,0.0);
    setAsservType(ASSERV_VITESSE);

    /* On ouvre le Timer2 qui gère l'asservissement toutes les 10ms */
    OpenTimer2(T2_OFF & T2_GATE_OFF & T2_IDLE_CON & T2_SOURCE_INT & T2_PS_1_64 & T2_32BIT_MODE_OFF, 6249);
    ConfigIntTimer2(T2_INT_PRIOR_4 & T2_INT_ON); //Interruption ON et priorité 4
    T2CONbits.TON = 1;  /* Turn on timer 2 */
}

void setAsservType(AsservType asserv)
{
    asservType = asserv;
}