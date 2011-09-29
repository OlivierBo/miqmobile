#include "config.h"
#include "include.h"
#include "brochage.h"


	//-------------------initppal--------------------------------------------------
	//Initialisations des différents modules

void initppal(void)
{
	// Régler l'oscillateur pour 8 MHz
	OSCCONbits.IRCF0=0;
	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF2=1;
	
	//choisir la primary clock
	OSCCONbits.SCS1=0;
	OSCCONbits.SCS0=0;
	
	//utiliser la pll
	OSCTUNEbits.PLLEN=1;
	
	//attendre la stabilisation de l'oscillateur
	while(!OSCCONbits.HFIOFS);
	
	//configuration des entrées/sorties
	TRISAbits.RA0=1; //GYRO
	TRISAbits.RA1=1; //ACC_X
	TRISAbits.RA4=0; //LED_HAUT
	TRISAbits.RA5=1; //ACC_Z
	TRISAbits.RA6=0; //LED_CENTRE_VERT
	TRISAbits.RA7=0; //LED_CENTRE_ORANGE
	TRISBbits.RB0=1; //CODEUR_A_DROITE
	TRISBbits.RB1=1; //CODEUR_A_GAUCHE
	TRISBbits.RB3=1; //CODEUR_B_DROITE
	TRISBbits.RB4=1; //CODEUR_B_GAUCHE
	TRISBbits.RB6=1; //PATTE_PGC
	TRISBbits.RB7=1; //PATTE_PGD
	TRISCbits.RC0=0; //LED_DROITE
	TRISCbits.RC1=0; //LED_TEMOIN
	TRISCbits.RC2=1; //BOUTON_VERT
	TRISCbits.RC3=1; //BOUTON_ROUGE
	TRISCbits.RC4=0; //LED_ERREUR
	TRISCbits.RC6=0; //USART_TX1
	TRISCbits.RC7=1; //USART_RX1
	TRISDbits.RD0=0; //LED_BAS
	TRISDbits.RD1=0; //LED_GAUCHE
	TRISDbits.RD2=0; //LED_USART2
	TRISDbits.RD3=0; //LED_USART1
	TRISDbits.RD5=1; //PRESENCE_UTILISATEUR
	TRISDbits.RD5=1; //BOUTON_LIMITATION
	TRISDbits.RD6=0; //USART_TX2
	TRISDbits.RD7=1; //USART_RX2
	TRISEbits.RE0=1; //POTENTIOMETRE_GUIDON
	TRISEbits.RE1=1; //BATTERIE
	TRISEbits.RE2=1; //ACC_CENTRIFUGE
	PORTA=0;
	PORTB=0;
	PORTC=0;
	PORTD=0;
	PORTE=0;
	
	// Initialisation du port analogique
	ANSELA=0;
	ANSELB=0;
	ANSELC=0;
	ANSELD=0;
	ANSELE=0;
	ANSELAbits.ANSA0=1; //GYRO
	ANSELAbits.ANSA1=1; //ACC_X
	ANSELAbits.ANSA5=1; //ACC_Z
	ANSELDbits.ANSD5=1; //PRESENCE_UTILISATEUR
	ANSELEbits.ANSE0=1; //POTENTIOMETRE_GUIDON
	ANSELEbits.ANSE1=1; //BATTERIE
	ANSELEbits.ANSE2=1; //ACC_CENTRIFUGE


	// activer les timers
		//OpenTimer0(TIMER_INT_OFF & T0_16BIT & T0_SOURCE_INT & T0_PS_1_256); 
	// Incrémentation toutes les 0.032ms


	// activer les interruptions

	//Initialisation USART
	Open1USART(USART_TX_INT_OFF &
	              USART_RX_INT_ON &
	              USART_ASYNCH_MODE &
	              USART_EIGHT_BIT &
	              USART_CONT_RX , 51); //baud 38400
		IPR1bits.RC1IP=0;

	return;
}


