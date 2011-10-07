
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
#include "tangage.h"
#include "tools.h"
#include "communication.h"
#include "consigne.h"
#include "variablesGlobales.h"
#include "config.h"




//liste des phrases des diff�rents printf
const far rom char printf_main_angle[]="\r\n%ddD";


//d�claration de la fonction main (il n'y a pas de main.h, donc on la d�clare ici)
void main (void);



//=============================================================================
//Programme principal
//=============================================================================
void main (void)
{
	//struct analogMesures anMes0;
 short i;
unsigned short blabla=9;
float b;
short a;

a=10;
b=9.81;
b*=a;
a=b;


	initppal();		//Initialisation g�n�rale

	//chargerTousLesCoef();
	genererCoefParDefaut();
	chargerValeurDeCalibration();
	

//=============================================================================
//Test des valeurs converties
//=============================================================================
LED_TEMOIN=LED_ON;
pauseMs(1000);



writeEeprom(&blabla, 5,  2);
readEeprom(&blabla, 5,  2);


while(1)
{
angleTangage(acquisition(CH_ACC_X), acquisition(CH_ACC_Z), acquisition(CH_GYRO), 0, i, 10);
pauseMs(100);
printf(printf_main_angle,i);

	if(PORTCbits.RC2) calibrageTangage();
}



/*


i=0x00;

printf("\r\n");
for(i=0;i<10;i++)
{
	Busy_eep (); printf("%d(%d) ",Read_b_eep(i),i);
}


*/



/*
while(1)
{
	appui bouton cali?
		si oui, entrer en mode calibration
	proc�dure de d�marrage ok? (cad, inclinaison dans les bornes et utilisateur pr�sent)
		si oui 
		do{
			
			Tout le code de marche normale (voir plus bas)

		}while(utilisateur pr�sent);
}

*/

	while(1)
	{
	//	if(demandeDeCalibration())
		{
		//	calibration()
		}

		//if(procedureDeDemarrage())
		{
		//	do
			{

				// Lecture des entr�es  analogiques
					//liste d'appel � acquisition(); du fichier tools.c
			
				// Calcul des vitesses de rotation + acc�l�ration
					//dans codeur.c
				
				//Transforme les valeurs pour d�terminer l'angle de tangage
					//utilisation de tangage.c pour calculer l'angle de tangage [en r�alit�, l'angle, sa d�riv�e, un indicateur de saturation]
			
				// Calcul de la consigne de couple g�n�rale
					//consigne.c qui calcule le pid pour obtenir le couple moyen
			
				// Prise en consid�ration de l�inclinaison du guidon
					//consigne.c
			
				// Envoi des consignes de couple moteur droit et gauche au microcontr�leur de commande moteur
					//rien de sp�cial, utiliser communication.c
			
				// Communication s�rie avec PC
					//envoyer quelques donn�es
					//traiter les demandes de labview ou des boutons du panneau de controle

			}// while(presenceUtilisateur());
		}
	}

while(1); //while 1 de fin de programme
}






//-------------------Test_init--------------------------------------------------

/*

#define minGyro 100
#define maxGyro 500
#define minGuidon 100
#define maxGuidon 500
#define nombreDeMesuresOk 10

void testInit(void)
{	struct analogMesures anMes1;
	unsigned char stabiliteSysteme=0;	
	unsigned char stabiliteGuidon=0;
	int compteurStabilite=0;
	short tetaP=0;
	unsigned short tinter=0;
	short angle=0;
	unsigned short old=ReadTimer0();
while(ledOK==0)
	{	
	anMes1=lectureAN();		//acquisition des entr�es analogiques
	printf("%d;%d\n\r",anMes1.anGuidon,anMes1.anBatterie);
	tinter=(ReadTimer0() - old)*100/3125; //Calcul du temps en chaque �chantillon de mesures en ms
	old=ReadTimer0();	//Valeur du compteur plac�e dans old pour le calcul du prochain tinter


	//angle=angleTangage(anAccX,anAccZ,anGyro, 0 , tetaP, tinter);	// Calcul de l'angle de tangage
	angle=anMes1.anBatterie;

		if(angle<=minGyro)				// Test et affichage pour savoir si le syst�me est droit
			{ledGyroBas=1;
			ledGyroHaut=0;
			stabiliteSysteme=0;					
			}
		else{if(angle>=maxGyro)
				{ledGyroHaut=1;
				ledGyroBas=0;
				stabiliteSysteme=0;
				}
			else{stabiliteSysteme=1;
				ledGyroHaut=0;
				ledGyroBas=0;
				}
			}	

		if(anMes1.anGuidon<=minGuidon)			// Test et affichage pour savoir si le guidon est droit
		{
			ledGuidonGauche=1;
			ledGuidonDroit=0;
			stabiliteGuidon=0;
		}
		else if(anMes1.anGuidon>=maxGuidon)
		{
			ledGuidonDroit=1;
			ledGuidonGauche=0;
			stabiliteGuidon=0;	
		}
		else
		{
			stabiliteGuidon=1;
			ledGuidonDroit=0;
			ledGuidonGauche=0;
		}

		if(stabiliteSysteme==1 && stabiliteGuidon==1)
		{ledAttente=1;				// Si tout est stable, on incr�mente et la led jaune est allum�e
		compteurStabilite++;
		}
		else{ledAttente=0;
			compteurStabilite=0;
			}
		if(compteurStabilite==nombreDeMesuresOk)
		{ledOK=1;				// Le compteur atteint, on peut sortir de la boucle
		ledAttente=0;
		}
		else{Delay10KTCYx (80); // delay de 10000 x 80 x 4/32000000 = 100 ms
			tetaP=angle;
			}
	}

CloseTimer0();
			
}
*/

