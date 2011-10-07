#ifndef INCLUDE_H
#define INCLUDE_H

#define BIT(x) (1<<(x))                          // equivalence de décalage
#define setbit(p,b) (p)|=BIT(b)                  // positionne le bit b de l'octet p à 1
#define clrbit(p,b) (p)&=~BIT(b)                 // positionne le bit b de l'octet p à 0
#define getbit(p,b) ((p)&BIT(b))>>(b)

//#include <p18F45K22.h> //Déclaration du micro utilisé
#include <p18cxxx.h>  // marche mieux pour les librairies



//=============================================================================
//Librairies utilisées
//=============================================================================

#include <stdio.h>		//Pour le traitement de chaines de caractères
#include <math.h>		//Fonctons mathématiques de bases
#include <stdlib.h>		//Fonctions générales
#include <delays.h>		//Fonction de delay
#include <timers.h>		//Fonction sur les timers
#include <usart.h>		//Fonction pour le module USART
#include <adc.h>		//Fonction pour la conversion A/D
#include <EEP.h>		//Fonction pour la mémoire EEPROM
#include <i2c.h>		//Fonction pour la communication I2C
#include <portb.h>
#include <timers.h>
#include <string.h>



#define OK 1
#define ERREUR 0
#define LED_ON 1
#define LED_OFF 0
#define TRUE 1
#define FALSE 0
//=============================================================================
//Definition de constantes
//=============================================================================
#define q 4.888e-3	//quantum pour un CAN 10bits 0v-5v
#define qbis 3.226e-3	//quantum pour un CAN 10bits 0v-3.3v

#define USE_AND_MASKS

#endif

