
//=============================================================================
// BOUTON Olivier JAEGY Adrien
// Programmation principale
//=============================================================================
//
// 
// Programme principal de la Miqmobile ou M2
//
//=============================================================================
#include "pragma_config.h"

#include "include.h"
#include "interruption.h"
#include "codeur.h"
#include "brochage.h"
#include "tools.h"
#include "communication.h"
#include "variablesGlobales.h"
#include "config.h"
#include "asserv.h"
#include "tangage.h"
#include "autresES.h"
#include "ultrason.h"

//liste des phrases des différents printf
const far rom char printf_main_angle[]="\r\nang: %d";
const far rom char printf_main_testgyro[]="\r\nX:%d Z:%d G:%d";
const far rom char printf_main_ok[]="\r\nok!";
const far rom char printf_main_guidon[]="\r\nraw %d, 0 %d, max %d, lu %d";
const far rom char printf_main_codeur[]="\r\n nbftmoy %ld, vmoy %ld";
//const far rom char printf_main_codeur[]="\r\n accMoy %ld, umot %ld, vmoy %ld, dmoy %ld, coef %ld";
const far rom char printf_main_tmr[]="\r\n t1 %d, t3 %d, t5 %d";
const far rom char printf_main_us[]="\r\n us %d";
ram char bufprint[TAILLE_BUFPRINT]; 

//déclaration de la fonction main (il n'y a pas de main.h, donc on la déclare ici)
void main (void);
void main_test(void);
void testLumiere(void);

void main_test(void)
{
struct Sroues roues;
unsigned char tab=1;
float temp=42.12345;
unsigned short ancien=globalTime,te;
short tAccX,tAccZ, tGyro,tGuidon, tBatterie,tCentrifuge;
float anglePrec=0;
struct Stangage tangage;

COEF_KALMAN=0.2;
ACCELERATION_COEF_FILTRE=0.1;
initCodeurs();


	while(1)
{

te=tempsEcouleDepuisMs(ancien);
ancien=globalTime;


/*
	{
printf( printf_main_testgyro, acquisition(CH_ACC_X),acquisition(CH_ACC_Z),acquisition(CH_GYRO));
roues = lancerCalculsCodeur(100);
temp=roues.positionDroite+roues.positionGauche;
printf( printf_main_angle, temp);
pauseMs(100);
}

		printf( printf_main_guidon,acquisition(CH_POTENTIOMETRE_GUIDON), tGuidon0, tGuidonMax, guidonTrMin(acquisition(CH_POTENTIOMETRE_GUIDON)));
*/


		for(tab=1;tab<34;tab*=2)
		{
			LED_HAUT = getbit(tab,0);
			LED_BAS = getbit(tab,1);
			LED_GAUCHE = getbit(tab,2);
			LED_DROITE = getbit(tab,3);
			LED_CENTRE_VERTE = getbit(tab,4);
			LED_CENTRE_ORANGE = getbit(tab,5);
			pauseMs(50);
		}
		//printf( printf_main_guidon,acquisition(CH_POTENTIOMETRE_GUIDON), tGuidon0, tGuidonMax, (short)guidonTrMin(acquisition(CH_POTENTIOMETRE_GUIDON)));



//interruptionCodeurD(SENS_D);
//interruptionCodeurG(SENS_G);
roues = lancerCalculsCodeur(te);

pauseMs(20);
//sprintf(bufprint,printf_main_codeur,(long)(roues.accMoyenne),(long)roues.positionDroite, (long)(roues.vitesseDroite*10.), (char) roues.signeDroite, (long) roues.distanceMoyenneParcourue); puts2USART (bufprint); 
//sprintf(bufprint,printf_main_codeur,(long)(roues.accMoyenne),(long)roues.positionGauche, (long)(roues.vitesseGauche*10.), (char) roues.signeGauche, (long) roues.distanceMoyenneParcourue); puts2USART (bufprint); 
//sprintf(bufprint,printf_main_codeur,(long)roues.positionDroite, (long)(roues.vitesseDroite*10.),(long)roues.positionGauche, (long)(roues.vitesseGauche*10.),(char) roues.signeGauche);puts2USART (bufprint);

//envoiTrameUart1(TYPE_TRAME_INF_ACCELERATION,(void*)(&roues.accMoyenne),LG_TRAME_INF_ACCELERATION);



//sprintf(bufprint,printf_main_codeur,(long)(roues.accMoyenne), (long)(roues.utilisationMoteur*100),(long)(roues.vitesseMoyenne*10), (long)(roues.distanceMoyenneParcourue*100),(long) (te*10));puts2USART (bufprint);
//sprintf(bufprint,printf_main_codeur,(long)(roues.accMoyenne),(long)(roues.accMoyenne), (long)(roues.vitesseMoyenne*10), (long)(roues.distanceMoyenneParcourue*100),(long) (ACCELERATION_COEF_FILTRE*10));puts2USART (bufprint);
//sprintf(bufprint,printf_main_codeur,(long)(roues.nbFtMoy),(long)roues.vitesseMoyenne*10); puts2USART (bufprint); 



sprintf(bufprint,printf_main_testgyro, acquisition(CH_ACC_X),acquisition(CH_ACC_Z),acquisition(CH_GYRO)); puts2USART (bufprint);


/*
sprintf(bufprint,printf_main_us,distanceUS()); puts2USART (bufprint);
lancerUS();

*/

	


tAccX=acquisition(CH_ACC_X);
tAccZ=acquisition(CH_ACC_Z);
tGyro=acquisition(CH_GYRO);
COEF_KALMAN=1;
tangage = angleTangage(tAccX, tAccZ, tGyro, 0, anglePrec, te);
anglePrec=tangage.teta;
//sprintf(bufprint,printf_main_angle,(short)(anglePrec*10)); puts2USART (bufprint); 
envoiTrameUart1(TYPE_TRAME_INF_ANGLE_TANGAGE,(void*)(&anglePrec),LG_TRAME_INF_ANGLE_TANGAGE);


}


while(1);
}

//=============================================================================

void testLumiere(void)
{
	pauseMs(500);
	LED_USART2 = LED_OFF;
	LED_HAUT = LED_ON;
	pauseMs(500);
	LED_HAUT = LED_OFF;
	LED_BAS = LED_ON;
	pauseMs(500);
	LED_BAS = LED_OFF;
	LED_GAUCHE = LED_ON;
	pauseMs(500);
	LED_GAUCHE = LED_OFF;
	LED_DROITE = LED_ON;
	pauseMs(500);
	LED_DROITE = LED_OFF;
	LED_CENTRE_VERTE = LED_ON;
	pauseMs(500);
	LED_CENTRE_VERTE = LED_OFF;
	LED_CENTRE_ORANGE = LED_ON;
	pauseMs(500);
	LED_CENTRE_ORANGE = LED_OFF;
	LED_ERREUR = LED_ON;
	pauseMs(500);
	LED_ERREUR = LED_OFF;
	LED_USART1 = LED_ON;
	pauseMs(500);
	LED_USART1 = LED_OFF;
	LED_USART2 = LED_ON;
}


//=============================================================================
//Programme principal
//=============================================================================
void main (void)
{


	char continuer = 1;
	initppal();		//Initialisation générale
	LED_CENTRE_VERTE = LED_ON;
	LED_CENTRE_ORANGE = LED_ON;
	chargerAsservissement();
	chargerVitesse();
	chargerDemarrage();
	chargerTangage(); //accéléromètre
	chargerGuidon();
	lancerUS();
	pauseMs(1000);
	LED_CENTRE_VERTE = LED_OFF;
	LED_CENTRE_ORANGE = LED_OFF;


	while(BOUTON_VERT)
	{
		testLumiere();
	}


	if(BOUTON_ROUGE)
	main_test();



	while(1)
	{
		lancerUS();
		//si le démarrage est autorisé (verifier aussi la batterie un jour..)
		if((testDemarrage()==OK)||(inf_demandeOnOff==2))
		{
			if(inf_demandeOnOff!=2) inf_demandeOnOff=1;

			//on signale qu'on est vivant!
			envoiTrameUart1(TYPE_TRAME_INF_ETAT,(void*)(&inf_demandeOnOff),LG_TRAME_INF_ETAT);

			boucleAsservissement(1);  //reset des parametres static
			continuer=1;

			//la boucle qui s'execute lorsque le segway est en marche normale
			while(continuer)
			{
				lancerUS();
				if(boucleAsservissement(0)==ERREUR) continuer=0;
				
				//si commande STOP, continuer=0;
				if(inf_demandeOnOff==8) continuer=0;
			}

			//on signale la fin
			inf_demandeOnOff=0;
			envoiTrameUart1(TYPE_TRAME_INF_ETAT,(void*)(&inf_demandeOnOff),LG_TRAME_INF_ETAT);
		}
		//si on veut entrer en mode paramétrage tangage
		if(BOUTON_ROUGE)
		{
			calibrageTangage();
		}
		if(BOUTON_VERT)
		{
			calibrerGuidon();
		}
		//envoi de données...
		//envoyerCoefficientsStatiques();

	}


while(1); //while 1 de fin de programme
}


