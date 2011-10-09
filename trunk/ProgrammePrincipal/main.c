
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

//liste des phrases des diff�rents printf
const far rom char printf_main_angle[]="\r\n%ddD";


//d�claration de la fonction main (il n'y a pas de main.h, donc on la d�clare ici)
void main (void);


//=============================================================================
//Programme principal
//=============================================================================
void main (void)
{
	char continuer = 1;

	initppal();		//Initialisation g�n�rale
	genererCoefParDefaut(); //chargerTousLesCoef(); serait mieux
	chargerValeurDeCalibration(); //acc�l�rom�tre
	chargerGuidon();
	pauseMs(1000);

	while(1)
	{
		//si le d�marrage est autoris� (verifier aussi la batterie un jour..)
		if(testDemarrage()==OK)
		{
			boucleAsservissement(1);  //reset des parametres static
			continuer=1;

			//la boucle qui s'execute lorsque le segway est en marche normale
			while(continuer)
			{
				if(boucleAsservissement(0)==ERREUR) continuer=0;
				//envoi de donn�es... peut etre en deplacer une partie ds la fonction d'asserv pour acc�der aux variables
				envoiTrameUart1 (TYPE_TRAME_CON_TEST_COM, (char*)(&globalTime), 1);
				//si commande STOP, continuer=0;
				//...
			}
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
		envoiTrameUart1 (TYPE_TRAME_CON_TEST_COM, (char*)(&globalTime), 1);
	}


while(1); //while 1 de fin de programme
}


