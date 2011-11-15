#include "config.h"
#include "include.h"
#include "brochage.h"




	//-------------------initppal--------------------------------------------------
	//Initialisations des différents modules

void initppal(void)
{
	// Régler l'oscillateur pour 16 MHz
	OSCCONbits.IRCF0=1;
	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF2=1;
	
	//choisir la primary clock
	OSCCONbits.SCS1=0;
	OSCCONbits.SCS0=0;
	
	//utiliser la pll (freq x 4 soit 64MHz pour le cycle d'horloge, 16MHz pour le cycle d'instruction)
	OSCTUNEbits.PLLEN=1; 
	
	//attendre la stabilisation de l'oscillateur
	while(!OSCCONbits.HFIOFS);
	
	//configuration des entrées/sorties
	TRISAbits.RA0=1; //GYRO
	TRISAbits.RA1=1; //ACC_CENTRIFUGE
	TRISAbits.RA2=1; //VREF_MOINS
	TRISAbits.RA3=1; //VREF_PLUS
	TRISAbits.RA4=0; //LED_HAUT
	TRISAbits.RA5=1; //ACC_Z
	TRISAbits.RA6=0; //LED_CENTRE_VERTE
	TRISAbits.RA7=0; //LED_CENTRE_ORANGE
	TRISBbits.RB0=1; //ULTRASON_INT
	TRISBbits.RB1=1; //INTER_1
	TRISBbits.RB2=1; //INTER_2
	TRISBbits.RB3=0; //LED_GAUCHE
	TRISBbits.RB4=0; //LED_DROITE
	TRISBbits.RB5=1; //CODEUR_GAUCHE
	TRISBbits.RB6=1; //PATTE_PGC
	TRISBbits.RB7=1; //PATTE_PGD
	TRISCbits.RC0=1; //CODEUR_DROITE
	TRISCbits.RC1=0; //LED_TEMOIN
	TRISCbits.RC2=1; //BOUTON_VERT
	TRISCbits.RC3=1; //BOUTON_ROUGE
	TRISCbits.RC4=0; //LED_ERREUR
	TRISCbits.RC5=0; //LED_BAS
	TRISCbits.RC6=0; //USART_TX1
	TRISCbits.RC7=1; //USART_RX1
	TRISDbits.RD0=1; //SCL2_RES
	TRISDbits.RD1=1; //SDA2_RES
	TRISDbits.RD2=0; //LED_USART2
	TRISDbits.RD3=0; //LED_USART1
	TRISDbits.RD4=0; //ULTRASON_TRIG
	TRISDbits.RD5=1; //BOUTON_LIMITATION
	TRISDbits.RD6=0; //USART_TX2
	TRISDbits.RD7=1; //USART_RX2
	TRISEbits.RE0=1; //POTENTIOMETRE_GUIDON
	TRISEbits.RE1=1; //BATTERIE
	TRISEbits.RE2=1; //ACC_X
	//TRISEbits.RE3=1; //MCLR_VPP



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
	ANSELAbits.ANSA1=1; //ACC_CENTRIFUGE
	ANSELAbits.ANSA5=1; //ACC_Z
	ANSELEbits.ANSE0=1; //POTENTIOMETRE_GUIDON
	ANSELEbits.ANSE1=1; //BATTERIE
	ANSELEbits.ANSE2=1; //ACC_X







	// activer les timers
		//global time : incrément toutes les 1/2µs (priorité HAUTE)
		OpenTimer3(TIMER_INT_ON & T3_16BIT_RW & T3_SOURCE_FOSC_4 & T3_OSC1EN_OFF & T3_SYNC_EXT_OFF &  T3_PS_1_8 , 0) ;
		WriteTimer3(63535); //une interruption chaque ms
		IPR2bits.TMR3IP=1;
		//unsigned int ReadTimer3(void)  ;

		//timer clignotement de diode (2 interruptions par seconde) (priorité BASSE)
		OpenTimer0(TIMER_INT_ON & T0_16BIT & T0_SOURCE_INT & T0_PS_1_128); 
		INTCON2bits.TMR0IP=0;

		//timers compteurs de fronts
		OpenTimer3(TIMER_INT_OFF & T3_16BIT_RW &  T3_SOURCE_PINOSC & T3_OSC1EN_OFF & T3_PS_1_1 & T3_SYNC_EXT_OFF, 0) ; //gauche
		OpenTimer5(TIMER_INT_OFF & T5_16BIT_RW &  T5_SOURCE_PINOSC & T5_OSC1EN_OFF & T5_PS_1_1 & T5_SYNC_EXT_OFF, 0) ; //droite


	// activer les interruptions INT
	//OpenRB0INT( PORTB_CHANGE_INT_ON & FALLING_EDGE_INT & PORTB_INT_PRIO_HIGH & PORTB_PULLUPS_OFF );//(priorité HAUTE) ultrason
	//OpenRB1INT( PORTB_CHANGE_INT_ON & FALLING_EDGE_INT & PORTB_INT_PRIO_LOW & PORTB_PULLUPS_OFF);//(priorité BASSE) signe codeur
	//OpenRB2INT( PORTB_CHANGE_INT_ON & FALLING_EDGE_INT & PORTB_INT_PRIO_LOW & PORTB_PULLUPS_OFF );//(priorité BASSE) signe codeur
		//INTCON2bits.INTEDG0: External Interrupt 0 Edge Select bit  = 0 : falling

	//Initialisation USART (priorité BASSE)
	Open1USART(USART_TX_INT_OFF &   USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_BRGH_LOW & USART_CONT_RX , 25); 
	IPR1bits.RC1IP=0;
	Open2USART(USART_TX_INT_OFF &   USART_RX_INT_ON & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_BRGH_LOW & USART_CONT_RX , 25); 
	IPR3bits.RC2IP=0;

	//USART_BRGH_HIGH USART_BRGH_LOW
	//Asynchronous mode, high speed: Fosc / (16 * (spbrg + 1))
	//Asynchronous mode, low speed: Fosc / (64 * (spbrg + 1))
	//freq		spbrg
	//38400		25
	//57600		16
	//115200	8
	//230400	3


	//activer les interruptions globales, en effacant d'abord les "bugs"
	INTCONbits.INT0IF=0;
	INTCONbits.TMR0IF=0;
	INTCON3bits.INT1IF=0;
	INTCON3bits.INT2IF=0;
	PIR1bits.RC1IF=0; // EUSART1 Receive Interrupt Flag bit (cleared when RCREG1 is read) 
	PIR2bits.TMR3IF=0;
	PIR3bits.RC2IF=0; // EUSART2 Receive Interrupt Flag bit (cleared by reading RCREG2)

	//INTCON2bits.RBPU=0; //pullup port B (si INT détectent n'importe quoi...)

	RCONbits.IPEN=1;
	INTCONbits.GIEL=1;
	INTCONbits.GIEH=1;
	return;
}


