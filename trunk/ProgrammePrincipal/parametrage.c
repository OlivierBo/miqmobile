#include "include.h"
#include "parametrage.h"
#include "time.h"
#include "conversion.h"
#include <EEP.h>


#define LedHaut PORTAbits.RA4
#define LedBas PORTDbits.RD0
#define LedGauche PORTDbits.RD1
#define LedDroite PORTCbits.RC0
#define LedMilieu PORTAbits.RA7

#define boutonValidation PORTCbits.RC2
#define boutonAnnulation PORTCbits.RC3

#define OK 1
#define ERREUR 0
#define ON 1
#define OFF 0

#define MEMOIRE_CAPTEUR 0x00



//a placer dans tangage.c**********************************************************

short calibrageTangage(void)
{
	


	long temp=0;
	short tAccX0 = 0, tAccX1 = 0, tAccZ0 = 0, tAccZ1 = 0, tGyro0 = 0, tGyro1 = 0;
	long i;

	//etape 1 : signaler qu'on est en mode calibrage
	LedHaut = ON;
	LedBas = OFF;
	LedGauche = OFF;
	LedDroite = OFF;
	LedMilieu = OFF;
	pause_ms(2000);

	//etape 2 : avertir de la mesure de la verticale
	LedGauche = ON;
	pause_ms(1500);

	//etape 3 : mesurer la verticale pendant 1s à une fréquence de 20Hz
	LedMilieu = ON;
	for(i=0;i<20;i++)
	{
		tAccX0+=acquisitionX();
		tAccZ1+=acquisitionZ();
		tGyro0+=acquisitionG();
		pause_ms(50);
	}
	tAccX0/=20;
	tAccZ1/=20;
	tGyro0/=20;

	//etape 4 : avertir de la mesure de la rotation de 90°

	LedGauche = OFF;
	LedMilieu = OFF;
	LedBas = ON;
	pause_ms(1500);

	//etape 5 : mesurer la rotation pendant 3s à 1kHz
	LedMilieu = ON;
	for(i=0;i<3000;i++)
	{
		temp+=acquisitionG();
		pause_ms(1);
	}
	temp-=tGyro0;

	temp/=900;
	//val_moy*100/30 <-> 1°/cs
	//val_moy = val_brute/3000
	// 1°/cs <-> val_brute*100 / (30*3000) = val_brute / 900

	tGyro1 = temp;

	//etape 6 : avertir de la mesure de l'horizontale
	LedBas = OFF;
	LedDroite = ON;
	LedMilieu = OFF;
	pause_ms(1500);

	//etape 7 : mesurer l'horizontale (20 points de mesure)
	LedMilieu = ON;
	for(i=0;i<20;i++)
	{
		tAccX1+=acquisitionX();
		tAccZ0+=acquisitionZ();
		pause_ms(50);
	}
	tAccX1/=20;
	tAccZ0/=20;

	//etape 8 : demander si on veut conserver le calibrage
	LedHaut = ON;
	Delay10TCYx (1); //il faut laisser le temps 
	LedBas = ON;
	Delay10TCYx (1);
	LedGauche = ON;
	LedDroite = ON;
	LedMilieu = OFF;
	


	while(boutonValidation==0)
	{
		if(boutonAnnulation) 
		{
		   	LedHaut = OFF;
			LedBas = OFF;
			LedGauche = OFF;
			LedDroite = OFF;
			LedMilieu = ON;
			pause_ms(500);
			LedMilieu = OFF;
			return ERREUR;
		}
	}


	//etape 9 : si on veut conserver les paramètres, on les enregistre
	i=MEMOIRE_CAPTEUR;
	Write_b_eep (i, tAccX0); Busy_eep (); i++;
	Write_b_eep (i, tAccX1); Busy_eep (); i++;
	Write_b_eep (i, tAccZ0); Busy_eep (); i++;
	Write_b_eep (i, tAccZ1); Busy_eep (); i++;
	Write_b_eep (i, tGyro0); Busy_eep (); i++;
	Write_b_eep (i, tGyro1); Busy_eep (); i++;

	LedMilieu = ON;
	pause_ms(500);
	LedHaut = OFF;
	LedBas = OFF;
	LedGauche = OFF;
	LedDroite = OFF;
	LedMilieu = OFF;

printf("\r\nA%d",tAccX0);
printf("\r\nA%d",tAccX1);
printf("\r\nA%d",tAccZ0);
printf("\r\nA%d",tAccZ1);
printf("\r\nA%d",tGyro0);
printf("\r\nA%d",tGyro1);
	

	return OK;

}

