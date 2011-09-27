
//=============================================================================
// BOUTON Olivier JAEGY Adrien
// Programmation principale
//=============================================================================
//
// 
// Programme principal de la Miqmobile ou M2
//
//=============================================================================


#include "include.h"
#include "interruption.h"
#include "config.h"
#include "codeur.h"
#include "brochage.h"
#include "convertisseurAN.h"
#include "tangage.h"
#include "time.h"
#include "parametrage.h"
#include "communication.h"
#include "consigne.h"



//=============================================================================
//Programme principal
//=============================================================================
void main (void)
{	struct analogMesures anMes0;
 short i;

//anMes0=lectureAN();
	initppal();		//Initialisation générale
	
	//Initialisation USART
	Open1USART(USART_TX_INT_OFF &
	              USART_RX_INT_ON &
	              USART_ASYNCH_MODE &
	              USART_EIGHT_BIT &
	              USART_CONT_RX , 51); //baud 38400
		IPR1bits.RC1IP=0;

//	OpenADC(ADC_FOSC_64 | ADC_RIGHT_JUST | ADC_16_TAD, ADC_INT_OFF, ADC_REF_VDD_VREFPLUS | ADC_REF_VDD_VREFMINUS);
//	initAN33();
//	ADCON1=0b00000101;


//=============================================================================
//Test des valeurs converties
//=============================================================================
ledOK=1;
pause_ms(1000);


while(1)
{
i=angleTangage(acquisitionX(), acquisitionZ(), acquisitionG(), 0, i, 10);
pause_ms(100);
printf("\r\n%ddD",i);

	if(PORTCbits.RC2) calibrageTangage();
}






i=0x00;

printf("\r\n");
for(i=0;i<10;i++)
{
	Busy_eep (); printf("%d(%d) ",Read_b_eep(i),i);
}

while(1);


calibrageTangage();

printf("\r\n");
for(i=0;i<10;i++)
{
	Busy_eep (); printf("%d(%d) ",Read_b_eep(i),i);
}


while(1)
{
	
	printf("%d;%d;%d;%d;%d\r\n", acquisitionX(),  acquisitionZ(), acquisitionG(),acquisitionVrefplus(),acquisitionVrefminus());
	pause_ms(10);
//	initAN33();
//	ADCON1=0b00000101;
//	pause_ms(20);
}




//=============================================================================
//Test de la fonction testInit
//=============================================================================
	OpenTimer0(TIMER_INT_OFF & T0_16BIT & T0_SOURCE_INT & T0_PS_1_256); 
	// Incrémentation toutes les 0.032ms
	testInit();		//Test permettant de savoir si la miqmobile est stable 
					// avant que la boucle d'asservissement se mette en place



//	while (1);	
	// Lecture des entrées  analogiques
//	lectureAN();
	
	//Transforme les valeurs pour déterminer l'angle de tangage

	// Calcul des vitesses de rotation + accélération


	// Calcul de l’angle (filtre Kalman)
	//	angleTangage(570,516,449,0,0,1000);
//	angleTangage(X_acc,Z_acc,gyro,acc_cod,teta_prec,tps_inter);

	// Calcul de la consigne de couple générale

	// Prise en considération de l’inclinaison du guidon

	// Envoi des consignes de couple moteur droit et gauche au microcontrôleur de commande moteur 

	// Communication série avec PC

	// Test présence utilisateur

	// Communication série I2C avec panneau de contrôle	


}





