#include "include.h"
#include "initialisation.h"
#include "tangage.h"
#include "conversion.h"
#include "time.h"

	//-------------------initppal--------------------------------------------------
	//Initialisations des différents modules
void initppal(void)
{
	// Régler l'oscillateur pour 8 MHz
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
	// Configurer quelles seront les entrées analogiques avec les registres ansel

		// AN0 : RA0 : gyroscope
		// AN1 : RA1 : accéléromètre axe X
		// AN2 : RA2 : accéléromètre axe Z
		// AN4 : RA5 : accéléromètre axe ?
		// AN5 : RE0 : potentiomètre guidon
		// AN6 : RE1 : Etat de la batterie 
		// AN7 : RE2 :
		// ANSEL permet de définir si la broche sera en analogique ou en logique
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

		// Interface avec LED d'initialisation, broches en sorties et initialisées
	 	TRISAbits.RA4=0;
		TRISAbits.RA6=0;
		TRISAbits.RA7=0;
		TRISCbits.RC0=0;
		TRISDbits.RD0=0;
		TRISDbits.RD1=0;
		TRISDbits.RD2=0;
		LATAbits.LATA4=0;
		LATAbits.LATA6=0;
		LATAbits.LATA7=0;
		LATCbits.LATC0=0;
		LATDbits.LATD0=0;
		LATDbits.LATD1=0;
		// RA4: gyro haut ; RA7 : Led attente ; RA6 : led OK ; RC0 : guidon droit ; RD0 : gyro bas ; RD1 : guidon gauche


	

	// penser à désactiver les interruptions

		//Initialisation USART
	Open1USART(USART_TX_INT_OFF &
	              USART_RX_INT_ON &
	              USART_ASYNCH_MODE &
	              USART_EIGHT_BIT &
	              USART_CONT_RX , 51); //baud 38400
		IPR1bits.RC1IP=0;

pause_ms(50);
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

void testEEPROM(void)
{	int i=0;
	char *data0;
	char buffer[11];
	char data1[]="Ecrire un chiffre entre 0 et 9 \n";
	char data2[]="Ecrire un commentaire 10 caracteres max \n";
	char data3[]="Ecriture EEPROM OK \n";
	unsigned short Memoire=0x00;

	while(Busy1USART());		//Attente d'utilisation de la communication
	puts1USART((char*) data1);  // Ecriture de la chaine de caractères data1
	while (!DataRdy1USART());	// Attente d'une réponse
	buffer[0]=Read1USART();		// Lecture du caractère lu par le PC
	Write_b_eep(Memoire,*buffer);  // Ecriture en EEPROM
	Busy_eep();						// Attente de find'écriture
	Memoire++;						// On sélectionne l'octet suivant de la mémoire
	while (Busy1USART());
	puts1USART((char*) data3);
	while (Busy1USART());
	puts1USART((char*) data2);
	while (Busy1USART());
	
	for(i=0;i<10;i++)				// Boucle pour la lecture des 10 caractères
		{
		while (!DataRdy1USART());
		buffer[i]=Read1USART();
		}
	write_mess_eep(Memoire, buffer);  	// Ecriture du message lu au module USART dans l'EEPROM
	while (Busy1USART());
	puts1USART((char*) data2);
	Memoire=0;
	while (Busy1USART());
	*data0=Read_b_eep(Memoire);		// Lecture dans EEPROM
	puts1USART(data0);				//Affichage de la valeur lue
	puts1USART((char*)"\n");
	for(i=1;i<11;i++)				// Boucle lecture EEPROM et affichage du message
		{
		*data0=Read_b_eep(i);
		while (Busy1USART());
		puts1USART(data0);
		}
}



void write_mess_eep(unsigned short ad, unsigned char *p)
{
while(*p)
	{
	Write_b_eep(ad,*p);
	Busy_eep();
	ad++;
	*p++;
	}
}

