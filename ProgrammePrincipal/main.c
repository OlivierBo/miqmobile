
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
const far rom char printf_main_angle[]="\r\n%d";
const far rom char printf_main_testgyro[]="\r\nX:%d Z:%d G:%d";
const far rom char printf_main_ok[]="\r\nok!";
const far rom char printf_main_guidon[]="\r\nraw %d, 0 %d, max %d, lu %d";
const far rom char printf_main_codeur[]="\r\ntmr %d, pos %d, vit %d";

const far rom char printf_main_tmr[]="\r\nt1 %d, t3 %d, t5 %d";

//déclaration de la fonction main (il n'y a pas de main.h, donc on la déclare ici)
void main (void);
void main_test(void);


void main_test(void)
{
struct Sroues roues;
unsigned char tab=1;
float temp=42.12345;


initCodeurs();

	while(1)

/*
	{
printf( printf_main_testgyro, acquisition(CH_ACC_X),acquisition(CH_ACC_Z),acquisition(CH_GYRO));
roues = lancerCalculsCodeur(100);
temp=roues.positionDroit+roues.positionGauche;
printf( printf_main_angle, temp);
pauseMs(100);
}

		printf( printf_main_guidon,acquisition(CH_POTENTIOMETRE_GUIDON), tGuidon0, tGuidonMax, guidonTrMin(acquisition(CH_POTENTIOMETRE_GUIDON)));
*/

{
		for(tab=1;tab<34;tab*=2)
		{
			LED_HAUT = getbit(tab,0);
			LED_BAS = getbit(tab,1);
			LED_GAUCHE = getbit(tab,2);
			LED_DROITE = getbit(tab,3);
			LED_CENTRE_VERTE = getbit(tab,4);
			LED_CENTRE_ORANGE = getbit(tab,5);
			pauseMs(100);
		}
		//printf( printf_main_guidon,acquisition(CH_POTENTIOMETRE_GUIDON), tGuidon0, tGuidonMax, (short)guidonTrMin(acquisition(CH_POTENTIOMETRE_GUIDON)));

//interruptionCodeurG(SENS_G);
//roues = lancerCalculsCodeur(600);
//printf(printf_main_codeur,LireCodeurGauche(),(int)roues.positionGauche, (int)roues.vitesseGauche);


printf(printf_main_tmr,ReadTimer1(),ReadTimer3(),ReadTimer5());

}


while(1);
}




//=============================================================================
//Programme principal
//=============================================================================
void main (void)
{


	char continuer = 1;


	initppal();		//Initialisation générale
	chargerAsservissement();
	chargerVitesse();
	chargerDemarrage();
	chargerTangage(); //accéléromètre
	chargerGuidon();
	lancerUS();
	pauseMs(1000);

	main_test();

	while(1)
	{
		lancerUS();
		//si le démarrage est autorisé (verifier aussi la batterie un jour..)
		if((testDemarrage()==OK)&&(0))
		{
			boucleAsservissement(1);  //reset des parametres static
			continuer=1;

			//la boucle qui s'execute lorsque le segway est en marche normale
			while(continuer)
			{
				lancerUS();
				if(boucleAsservissement(0)==ERREUR) continuer=0;
				//envoi de données... peut etre en deplacer une partie ds la fonction d'asserv pour accéder aux variables
				envoiTrameUart1 (TYPE_TRAME_CON_TEST_COM, (void*)&globalTime, 2);
				//si commande STOP, continuer=0;
				//...
			}
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
		//envoiTrameUart1 (TYPE_TRAME_CON_TEST_COM, (char*)(&globalTime), 1);


	}


while(1); //while 1 de fin de programme
}


