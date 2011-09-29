
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

#include "config.h"




//liste des phrases des différents printf
const far rom char printf_main_angle[]="\r\n%ddD";


//déclaration de la fonction main (il n'y a pas de main.h, donc on la déclare ici)
void main (void);



//=============================================================================
//Programme principal
//=============================================================================
void main (void)
{
	//struct analogMesures anMes0;
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
LED_TEMOIN=LED_ON;
pause_ms(1000);


while(1)
{
i=angleTangage(acquisition(CH_ACC_X), acquisition(CH_ACC_Z), acquisition(CH_GYRO), 0, i, 10);
pause_ms(100);
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
	procédure de démarrage ok? (cad, inclinaison dans les bornes et utilisateur présent)
		si oui 
		do{
			
			Tout le code de marche normale (voir plus bas)

		}while(utilisateur présent);
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

				// Lecture des entrées  analogiques
					//liste d'appel à acquisition(); du fichier tools.c
			
				// Calcul des vitesses de rotation + accélération
					//dans codeur.c
				
				//Transforme les valeurs pour déterminer l'angle de tangage
					//utilisation de tangage.c pour calculer l'angle de tangage [en réalité, l'angle, sa dérivée, un indicateur de saturation]
			
				// Calcul de la consigne de couple générale
					//consigne.c qui calcule le pid pour obtenir le couple moyen
			
				// Prise en considération de l’inclinaison du guidon
					//consigne.c
			
				// Envoi des consignes de couple moteur droit et gauche au microcontrôleur de commande moteur
					//rien de spécial, utiliser communication.c
			
				// Communication série avec PC
					//envoyer quelques données
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
	anMes1=lectureAN();		//acquisition des entrées analogiques
	printf("%d;%d\n\r",anMes1.anGuidon,anMes1.anBatterie);
	tinter=(ReadTimer0() - old)*100/3125; //Calcul du temps en chaque échantillon de mesures en ms
	old=ReadTimer0();	//Valeur du compteur placée dans old pour le calcul du prochain tinter


	//angle=angleTangage(anAccX,anAccZ,anGyro, 0 , tetaP, tinter);	// Calcul de l'angle de tangage
	angle=anMes1.anBatterie;

		if(angle<=minGyro)				// Test et affichage pour savoir si le système est droit
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
		{ledAttente=1;				// Si tout est stable, on incrémente et la led jaune est allumée
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


