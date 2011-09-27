#include "include.h"
#include "brochage.h"
#include "tangage.h"
#include "convertisseurAN.h"

	//-------------------initppal--------------------------------------------------
	//Initialisations des diff�rents modules
void initppal(void)
{
	// R�gler l'oscillateur pour 8 MHz
	OSCCONbits.IRCF0=0;
	OSCCONbits.IRCF1=1;
	OSCCONbits.IRCF2=1;
	
	//choisir la primary clock
	OSCCONbits.SCS1=0;
	OSCCONbits.SCS0=0;
	
	//utiliser la pll
	OSCTUNEbits.PLLEN=1;
	
	//attendre la stabilisation de l'oscillateur
	while(!OSCCONbits.HFIOFS);
	
	// Initialisation du port analogique
	// Configurer quelles seront les entr�es analogiques avec les registres ansel

		// AN0 : RA0 : gyroscope
		// AN1 : RA1 : acc�l�rom�tre axe X
		// AN2 : RA2 : acc�l�rom�tre axe Z
		// AN4 : RA5 : acc�l�rom�tre axe ?
		// AN5 : RE0 : potentiom�tre guidon
		// AN6 : RE1 : Etat de la batterie 
		// AN7 : RE2 :
		// ANSEL permet de d�finir si la broche sera en analogique ou en logique
		ANSELEbits.ANSE0=1;
		ANSELEbits.ANSE1=1;
		ANSELEbits.ANSE2=1;
		ANSELD=0b00000000;		//PORT B, C et D en logique
		ANSELCbits.ANSC2=0;
		ANSELCbits.ANSC3=0;
		ANSELCbits.ANSC4=0;
		ANSELCbits.ANSC5=0;
		ANSELCbits.ANSC6=0;
		ANSELCbits.ANSC7=0;
		ANSELBbits.ANSB0=0;
		ANSELBbits.ANSB1=0;
		ANSELBbits.ANSB2=0;
		ANSELBbits.ANSB3=0;
		ANSELBbits.ANSB4=0;
		ANSELBbits.ANSB5=0;
		ANSELAbits.ANSA0=1;
		ANSELAbits.ANSA1=1;
		ANSELAbits.ANSA2=1;
		ANSELAbits.ANSA5=1;

		// Interface avec LED d'initialisation, broches en sorties et initialis�es
	 	TRISAbits.RA4=0;
		TRISAbits.RA6=0;
		TRISAbits.RA7=0;
		TRISCbits.RC0=0;
		TRISDbits.RD0=0;
		TRISDbits.RD1=0;
		LATAbits.LATA4=0;
		LATAbits.LATA6=0;
		LATAbits.LATA7=0;
		LATCbits.LATC0=0;
		LATDbits.LATD0=0;
		LATDbits.LATD1=0;
		// RA4: gyro haut ; RA7 : Led attente ; RA6 : led OK ; RC0 : guidon droit ; RD0 : gyro bas ; RD1 : guidon gauche

	//rajout adrien (pas sur que ces pattes soient libres)
		TRISCbits.RC2=1;
		TRISCbits.RC3=1;


	

	// penser � d�sactiver les interruptions

}



//-------------------Test_init--------------------------------------------------
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


