/*
 * File:   Interpreter.c
 * Author: Paul Rousse
 *
 * Created on 12 mai 2014, 18:33
 */
#include <stdlib.h>
#include <stdio.h>

#include <xc.h>
#include "../Headers/Asservissement.h"
#include "../Headers/AsservissementPosition.h"
#include "../Headers/AsservissementVitesse.h"
#include "../Headers/Interpreter.h"
#include "../Headers/Mouvement.h"
#include "../Headers/PWM.h"
#include "../Headers/UART.h"


float l,theta;
float v,w;

float xOdometrie,yOdometrie,thetaOdometrie;

/*
// Machine a états pour le traitement des données entrantes
typedef enum {
    COMMANDE1, COMMANDE2, DATA1,DATA2,DATA3,DATA4
} EtatReception;

EtatReception etatRcv;

float param;
int data1, data2;

union
{
    struct {
          unsigned int data4:8;
          unsigned int data3:8;
          unsigned int data2:8;
          unsigned int data1:8;
    };
    float reel;
} data;
union
{
    struct {
          unsigned int data2:8;
          unsigned int data1:8;
    };
    unsigned int data;
} commande;

void interpreteData(unsigned int rcv)
{
    if(etatRcv == COMMANDE1)
    {
        commande.data1 = rcv;
        etatRcv = COMMANDE2;
    }
    else if(etatRcv == COMMANDE2)
    {
        commande.data2 = rcv;
        etatRcv = DATA1;
    }
    else if(etatRcv == DATA1)
    {
        data.data1 = rcv;
        etatRcv = DATA2;
    }
    else if(etatRcv == DATA2)
    {
        data.data2 = rcv;
        etatRcv = DATA3;
    }
    else if(etatRcv == DATA3)
    {
        data.data3 = rcv;
        etatRcv = DATA4;
    }
    else if(etatRcv == DATA4)
    {
        data.data4 = rcv;
        etatRcv = COMMANDE1;

        param = data.reel;

        WriteUART('H');
        interpreteCommande(commande.data, param);
    }
}*/
char commande[100] = "\0";
int indexCommande;
void interpreteData(char rcv)
{
    float param;

    if(indexCommande >= 100)
    {
        indexCommande = 0;
        
        puts("\n\nBuffer Overflow!\n\n");
    }

    if(rcv != '\n')
        commande[indexCommande++] = rcv;
    else
    {
        commande[indexCommande] = '\0';

        putsUART(&(commande[1]));
        param = atof(&(commande[1]));
        interpreteCommande(commande[0], param);
        indexCommande = 0;
    }
}

void initInterpreter() {
   /* etatRcv = COMMANDE1;*/
    indexCommande = 0;
}


/*
int interpreteCommande(Commande commande, float param) {

            char str[100];

            sprintf(str,"\n%i %f\n",commande, param);
            putsUART(str);
    switch(commande)
    {

        // Asservissement en position
        case ASSERVISSEMENT_POSITION_X:
            x = param;
            break;
        case ASSERVISSEMENT_POSITION_Y:
            y = param;
            break;
        case ASSERVISSEMENT_POSITION_THETA:
            theta = param;
            break;
        case ASSERVISSEMENT_POSITION_OK:
            setConsignePosition(x, y, theta);
            setAsservType(ASSERV_POSITION);
            break;

        // Asservissement en vitesse
        case ASSERVISSEMENT_VITESSE_V:
            v = param;
            break;
        case ASSERVISSEMENT_VITESSE_W:
            w = param;
            break;
        case ASSERVISSEMENT_VITESSE_OK:
            setConsigneVitesse(v,w);
            setAsservType(ASSERV_VITESSE);
            sprintf(str,"V(%f)W(%f)\n",v,w);
            putsUART(str);
            break;

        // Gestion de l'odométrie
        case RESET_ODOMETRIE:
            resetOdometrie();
            break;
        case PRINT_ODOMETRIE:
            sendOdometrie();
            break;
        case ODOMETRIE_X:
            xOdometrie = param;
            break;
        case ODOMETRIE_Y:
            yOdometrie = param;
            break;
        case ODOMETRIE_THETA:
            thetaOdometrie = param;
            break;
        case ODOMETRIE_OK:
            setPosition(xOdometrie,yOdometrie,thetaOdometrie);
            break;

        default:

            ;
            
    }

    return 0;
}*/


int interpreteCommande(char commande, float param)
{
    switch(commande)
    {

        // Asservissement en position
        case 'L':
            l = param;
            break;
        case 'T':
            theta = param;
            break;
        case 'o':
            setConsignePosition(l,theta);
            setAsservType(ASSERV_POSITION);
            break;

        // Asservissement en vitesse
        case 'V':
            v = param;
            break;
        case 'W':
            w = param;
            break;
        case 'O':
            setConsigneVitesse(v,w);
            setAsservType(ASSERV_VITESSE);
            //sprintf(str,"V %f W %f",v,w);
            //puts(str);
            break;

        // Gestion de l'odométrie
        case 'S':
            resetOdometrie();
            break;
        case 'R':
	    asm("RESET");
            break;
        case 'P':
            sendOdometrie();
            break;

        // Gestion des moteurs
        case 'E':
            enablePWM;
            break;
        case 'D':
            disablePWM;
            break;
            
        default:
            puts("\n\nCommande inconnue!\n\n");
            break;

    }

    return 0;
}
