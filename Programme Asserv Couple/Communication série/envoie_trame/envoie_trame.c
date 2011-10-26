//**********************************************************************
//        			   												   *
//       Communication usart en émission                			   *  
//                                                                     *
//**********************************************************************
//                                                                     *
//    Date:     25/05/2011                                             *
//    Auteur:   Gauthier Yoann                         				   *
//                                                                     *
//**********************************************************************
#include <pic.h>
#include <ctype.h>
#include <htc.h> //indispensable pour High Tech
#include <math.h>
#ifndef _XTAL_FREQ
 #define _XTAL_FREQ 4000000
#endif


//********************Variables globales********************************



//********************Programme principal******************************

void main(void){

//*******************************Déclaration des variables*************************
//__delay_ms(200);
char code;
char check;
char i,j;
char couple;
#define TYPE_TRAME_CON_COUPLEG 138
#define TYPE_TRAME_CON_COUPLED 139
#define TYPE_TRAME_CON_STOP 180
#define TYPE_TRAME_CON_DEPART 153
#define TYPE_TRAME_INF_ERREUR_CARTE_COURANT 12 //a utiliser
#define TYPE_TRAME_INF_PRET 25
#define TYPE_TRAME_CON_TEST_COM 155




//*******************************Initialisation des registres**********************
//on envoie par RC6 et on recoie par RC7
TXSTA=0b00000110;//assynchrone/8 bits/usart disable(activer avec TXEN)/high speed/TSR empty
RCSTA=0b10001110;//port disable(activer avec SPEN)/8 bits/assychrone/no continous receive/enable addresse detect/Faming error bit/over run error bit
SPBRG=20;//57,6 K bauds

INTCON=0;
PIE1=0;
TXEN=1;//on active la transmission
SPEN=1;//on active les ports
TXIE=1;//on active les intéruptions de transmission
CREN=1;//on active la reception continue
GIE=0;//global interrupt enable
PEIE=1;//Enables peripheral interrupts 
RCIE=1;//Active interuption en reception

//config interruption sur RB0
TMR0IE=1;//Active les interuptions sur TMR0
T0CS=0;//clock interne
PSA=1;//prescaler sur TMR0
PS2=1;//prescaler à 256
PS1=1;
PS0=1;




TRISA=0b00000000;
TRISB=0b11111111;
TRISD=0b00000000;
PORTA=0;
PORTD=0;

while(1){

for(j=0;j<1000;j++){
	TXREG=0b11011001;//perturbation
	while(!TXIF);
	TXIF=0;
	TXREG=TYPE_TRAME_CON_DEPART;//début de transmission
	while(!TXIF);//attente de la fin de la transmission avant d'envoyer un autre caractère
	TXIF=0;
	TXREG=TYPE_TRAME_CON_COUPLED;
	while(!TXIF);
	TXIF=0;
	couple =PORTB;
	TXREG=couple;
	while(!TXIF);
	TXIF=0;
	TXREG=TYPE_TRAME_CON_COUPLED +couple;//octet de vérification de tram
	while(!TXIF);
	TXIF=0;
	/*TXREG=TYPE_TRAME_CON_STOP;
	while(!TXIF);
	TXIF=0;*/
		}



	TXREG=0b11011001;//perturbation
	while(!TXIF);
	TXIF=0;
	TXREG=TYPE_TRAME_CON_DEPART;//début de transmission
	while(!TXIF);//attente de la fin de la transmission avant d'envoyer un autre caractère
	TXIF=0;
	TXREG=TYPE_TRAME_CON_COUPLED;
	while(!TXIF);
	TXIF=0;
	couple =TYPE_TRAME_CON_COUPLED;
	TXREG=couple;
	while(!TXIF);
	TXIF=0;
	TXREG=TYPE_TRAME_CON_COUPLED +couple;//octet de vérification de tram
	while(!TXIF);
	TXIF=0;

	}//end while

}//end prog



