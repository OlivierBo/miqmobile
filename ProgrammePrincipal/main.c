
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

//liste des phrases des diff�rents printf
const far rom char printf_main_angle[]="\r\n%d";
const far rom char printf_main_testgyro[]="\r\nX:%d Z:%d G:%d";
const far rom char printf_main_ok[]="\r\nok!";
const far rom char printf_main_guidon[]="\r\nraw %d, 0 %d, max %d, lu %d";
const far rom char printf_main_codeur[]="\r\n 1000acc %d, pos %d, 100vit %d, sgn %d";
const far rom char printf_main_tmr[]="\r\n t1 %d, t3 %d, t5 %d";
const far rom char printf_main_us[]="\r\n us %d";
ram char bufprint[TAILLE_BUFPRINT]; 

//d�claration de la fonction main (il n'y a pas de main.h, donc on la d�clare ici)
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
temp=roues.positionDroite+roues.positionGauche;
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
			pauseMs(83);
		}
		//printf( printf_main_guidon,acquisition(CH_POTENTIOMETRE_GUIDON), tGuidon0, tGuidonMax, (short)guidonTrMin(acquisition(CH_POTENTIOMETRE_GUIDON)));


interruptionCodeurG(SENS_D);
roues = lancerCalculsCodeur(500);
sprintf(bufprint,printf_main_codeur,(int)(roues.accMoyenne*1000),(int)roues.positionDroite, (int)(roues.vitesseDroite*100), (char) roues.signeDroite); puts2USART (bufprint); 


/*
sprintf(bufprint,printf_main_testgyro, acquisition(CH_ACC_X),acquisition(CH_ACC_Z),acquisition(CH_GYRO)); puts2USART (bufprint);
*/
/*
sprintf(bufprint,printf_main_us,distanceUS()); puts2USART (bufprint);
lancerUS();
*/
}


while(1);
}




//=============================================================================
//Programme principal
//=============================================================================
void main (void)
{


	char continuer = 1;


	initppal();		//Initialisation g�n�rale
	chargerAsservissement();
	chargerVitesse();
	chargerDemarrage();
	chargerTangage(); //acc�l�rom�tre
	chargerGuidon();
	lancerUS();
	pauseMs(1000);

	main_test();

	while(1)
	{
		lancerUS();
		//si le d�marrage est autoris� (verifier aussi la batterie un jour..)
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
		//si on veut entrer en mode param�trage tangage
		if(BOUTON_ROUGE)
		{
			calibrageTangage();
		}
		if(BOUTON_VERT)
		{
			calibrerGuidon();
		}
		//envoi de donn�es...
		//envoyerCoefficientsStatiques();

	}


while(1); //while 1 de fin de programme
}


