/** \file 
Contient des macros de gestion des bits, les biblioth�ques indispensables � tous les fichiers (pic18cxxx, timers, usart, string...), quelques defines (OK, ERREUR, LED_ON, OUI, NON) et le buffer pour les printf.
\author    Adrien Jaegy
 */


#ifndef INCLUDE_H
#define INCLUDE_H

#define BIT(x) (1<<(x))                          // equivalence de d�calage
#define setbit(p,b) (p)|=BIT(b)                  // positionne le bit b de l'octet p � 1
#define clrbit(p,b) (p)&=~BIT(b)                 // positionne le bit b de l'octet p � 0
#define getbit(p,b) ((p)&BIT(b))>>(b)

//#include <p18F45K22.h> //D�claration du micro utilis�
#include <p18cxxx.h>  // marche mieux pour les librairies



//=============================================================================
//Librairies utilis�es
//=============================================================================

#include <stdio.h>		//Pour le traitement de chaines de caract�res
#include <math.h>		//Fonctons math�matiques de bases
#include <stdlib.h>		//Fonctions g�n�rales
#include <delays.h>		//Fonction de delay
#include <timers.h>		//Fonction sur les timers
#include <usart.h>		//Fonction pour le module USART
#include <adc.h>		//Fonction pour la conversion A/D
#include <EEP.h>		//Fonction pour la m�moire EEPROM
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
#define OUI 1
#define NON 0

//r�ponse carte couple
#define PRET 1
#define PROBLEME 2
#define INDEF 0
//=============================================================================
//Definition de constantes
//=============================================================================
#define q 4.888e-3	//quantum pour un CAN 10bits 0v-5v
#define qbis 3.226e-3	//quantum pour un CAN 10bits 0v-3.3v

#define USE_AND_MASKS

#define TAILLE_BUFPRINT 80
extern ram char bufprint[TAILLE_BUFPRINT]; 

#endif

