
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
#include "initialisation.h"
#include "conversion.h"
#include "tangage.h"
#include "time.h"
#include "parametrage.h"
#include "commoteur.h"
#include "compan.h"
#include "compc.h"
#include "consigne.h"



//=============================================================================
//Programme principal
//=============================================================================
void main (void)
{	
unsigned short tx_i=0;
struct analogMesures anMes0;
initppal();


anMes0=lectureAN();
		//Initialisation g�n�rale
	


//=============================================================================
//Test des valeurs converties
//=============================================================================
/*
while(1)
{
	printf("%d;%d;%d;%d;%d\n\r", acquisitionX(),  acquisitionZ(), acquisitionG(),acquisitionVrefplus(),acquisitionVrefminus());
	pause_ms(20);
}
*/
//INTCONbits.GIE=0;



//=============================================================================
//Test calibrage
//=============================================================================
/*calibrageTangage();
while(1);*/

//=============================================================================
//Test de la fonction testInit
//=============================================================================
//	OpenTimer0(TIMER_INT_OFF & T0_16BIT & T0_SOURCE_INT & T0_PS_1_256); 
	// Incr�mentation toutes les 0.032ms
//	testInit();		//Test permettant de savoir si la miqmobile est stable 
					// avant que la boucle d'asservissement se mette en place



//=============================================================================
//Test �criture EEPROM
//=============================================================================

//testEEPROM();


//=============================================================================
//Test envoi donn�es PC
//=============================================================================
/*
	switch(tx_i)			// tx_i prend � chaque boucle une valeur diff�rente 
							// et permet donc d'envoyer une donn�e diff�rente
	{
	case(0):						// Suite d'exemple qui peuvent �tre envoy�s
		printf("Gyro: ");
		envoiPC(anMes0.anGyro);
		break;
	case(1):
		printf("ACCX: ");
		envoiPC(anMes0.anAccX);
		break;
	case(2):
		printf("ACCZ: ");
		envoiPC(anMes0.anAccZ);
		break;
	case(3):
		printf("Guidon: ");
		envoiPC(anMes0.anGuidon);
		break;
	case(4):
		printf("Batterie: ");
		envoiPC(anMes0.anBatterie);
		break;
	case(5):
		printf("Angle: ");
		envoiPC(anMes0.anGyro);
		break;
	case(6):
		printf("Consigned: ");
		envoiPC(anMes0.anGyro);
		break;
	case(7):
		printf("Consigneg: ");
		envoiPC(anMes0.anGyro);
		break;
	}
	if(tx_i==7)				// 7 repr�sente le nombre de donn�es envoy�es
							// Nous avons donc par exemple toutes les valeurs
							// lues par le PC apr�s 7 cycles d'asservissement
		{tx_i=0;}
	else
		{tx_i++;}

*/

//=============================================================================
//Une fois tous les effectu�s, �criture pas � pas du programme ppal en commentaires
//=============================================================================
//	OpenTimer0(TIMER_INT_OFF & T0_16BIT & T0_SOURCE_INT & T0_PS_1_256); 
	// Incr�mentation toutes les 0.032ms
//	testInit();		//Test permettant de savoir si la miqmobile est stable 
					// avant que la boucle d'asservissement se mette en place



//	while (1);	
	// Lecture des entr�es  analogiques
//	lectureAN();
	
	//Transforme les valeurs pour d�terminer l'angle de tangage

	// Calcul des vitesses de rotation + acc�l�ration


	// Calcul de l�angle (filtre Kalman)
	//	angleTangage(570,516,449,0,0,1000);
//	angleTangage(X_acc,Z_acc,gyro,acc_cod,teta_prec,tps_inter);

	// Calcul de la consigne de couple g�n�rale

	// Prise en consid�ration de l�inclinaison du guidon

	// Envoi des consignes de couple moteur droit et gauche au microcontr�leur de commande moteur 

	// Communication s�rie avec PC

	// Test pr�sence utilisateur

	// Communication s�rie I2C avec panneau de contr�le	


}






