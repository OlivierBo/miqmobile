#include "include.h"
#include "tangage.h"
#include "tools.h"
#include "brochage.h"


const far rom char printf_tangage_1[]="/r/n%d";

//calibration
short tAccX0 = 0, tAccX1 = 0, tAccZ0 = 0, tAccZ1 = 0, tGyro0 = 0, tGyro1 = 0;

//valeurs courantes (pour ne pas devoir les recalculer)
short tetaAngle=0, tetaVitesse=0;
char defautBorne=0;


void recupererValeurDeCalibration()
{
	unsigned short i=EEPROM_CALIBRATION;
	unsigned char longueur = 2;

	readEeprom(&tAccX0, i, longueur); i+=longueur;
	readEeprom(&tAccX1, i, longueur); i+=longueur;
	readEeprom(&tAccZ0, i, longueur); i+=longueur;
	readEeprom(&tAccZ1, i, longueur); i+=longueur;
	readEeprom(&tGyro0, i, longueur); i+=longueur;
	readEeprom(&tGyro1, i, longueur); i+=longueur;
}

void enregistrerValeurDeCalibration()
{
	unsigned short i=EEPROM_CALIBRATION;
	unsigned char longueur = 2;

	writeEeprom(&tAccX0, i, longueur); i+=longueur;
	writeEeprom(&tAccX1, i, longueur); i+=longueur;
	writeEeprom(&tAccZ0, i, longueur); i+=longueur;
	writeEeprom(&tAccZ1, i, longueur); i+=longueur;
	writeEeprom(&tGyro0, i, longueur); i+=longueur;
	writeEeprom(&tGyro1, i, longueur); i+=longueur;
}





short calibrageTangage(void)
{
	long temp=0;
	
	long i;
	//etape 1 : signaler qu'on est en mode calibrage
	LED_HAUT = LED_ON;
	LED_BAS = LED_OFF;
	LED_GAUCHE = LED_OFF;
	LED_DROITE = LED_OFF;
	LED_CENTRE_VERTE = LED_OFF;
	pauseMs(2000);


	//etape 2 : avertir de la mesure de la verticale
	LED_GAUCHE = LED_ON;
	pauseMs(1500);

	//etape 3 : mesurer la verticale pendant 1s à une fréquence de 20Hz
	LED_CENTRE_VERTE = LED_ON;
	for(i=0;i<20;i++)
	{
		tAccX0+=acquisition(CH_ACC_X);
		tAccZ1+=acquisition(CH_ACC_Z);
		tGyro0+=acquisition(CH_GYRO);
		pauseMs(50);
	}
	tAccX0/=20;
	tAccZ1/=20;
	tGyro0/=20;

	//etape 4 : avertir de la mesure de la rotation de 90°

	LED_GAUCHE = LED_OFF;
	LED_CENTRE_VERTE = LED_OFF;
	LED_BAS = LED_ON;
	pauseMs(1500);

	//etape 5 : mesurer la rotation pendant 3s à 1kHz
	LED_CENTRE_VERTE = LED_ON;
	for(i=0;i<3000;i++)
	{
		temp+=acquisition(CH_GYRO);
		pauseMs(1);
	}
	temp-=tGyro0;

	temp/=900;
	//val_moy*100/30 <-> 1°/cs
	//val_moy = val_brute/3000
	// 1°/cs <-> val_brute*100 / (30*3000) = val_brute / 900

	tGyro1 = temp;

	//etape 6 : avertir de la mesure de l'horizontale
	LED_BAS = LED_OFF;
	LED_DROITE = LED_ON;
	LED_CENTRE_VERTE = LED_OFF;
	pauseMs(1500);

	//etape 7 : mesurer l'horizontale (20 points de mesure)
	LED_CENTRE_VERTE = LED_ON;
	for(i=0;i<20;i++)
	{
		tAccX1+=acquisition(CH_ACC_X);
		tAccZ0+=acquisition(CH_ACC_Z);
		pauseMs(50);
	}
	tAccX1/=20;
	tAccZ0/=20;

	//etape 8 : demander si on veut conserver le calibrage
	LED_HAUT = LED_ON;
	Delay10TCYx (1); //il faut laisser le temps 
	LED_BAS = LED_ON;
	Delay10TCYx (1);
	LED_GAUCHE = LED_ON;
	LED_DROITE = LED_ON;
	LED_CENTRE_VERTE = LED_OFF;
	


	while(BOUTON_VERT==0)
	{
		if(BOUTON_ROUGE) 
		{
		   	LED_HAUT = LED_OFF;
			LED_BAS = LED_OFF;
			LED_GAUCHE = LED_OFF;
			LED_DROITE = LED_OFF;
			LED_CENTRE_VERTE = LED_ON;
			pauseMs(500);
			LED_CENTRE_VERTE = LED_OFF;
			return ERREUR;
		}
	}


	//etape 9 : si on veut conserver les paramètres, on les enregistre
	enregistrerValeurDeCalibration();

	LED_CENTRE_VERTE = LED_ON;
	pauseMs(500);
	LED_HAUT = LED_OFF;
	LED_BAS = LED_OFF;
	LED_GAUCHE = LED_OFF;
	LED_DROITE = LED_OFF;
	LED_CENTRE_VERTE = LED_OFF;



	return OK;

}





void angleTangage(short tAccX, short tAccZ, short tGyro, short xpp, short tetaPrec, short te)
{
//tAccX, tAccZ, tGyro
	//sortie brute du CAN entre 0 et 1024
//te en ms
//tetaPrec en decidegrés
//xpp est l'accélération lue par les codeurs, à donner en 10g mm/s²
	
//calibrage (0 pour la valeur signifiant 0, 1 pour la valeur unité 9.81m/s pour les accéléro et °/cs  pour le gyro)
	signed short tAccX0 = 608, tAccX1 = 136, tAccZ0 = 618, tAccZ1 = 99, tGyro0 = 301, tGyro1 = 971;
	long a = 15; //[0;1000] , a = 1000 => 100% de confiance dans l'accéléromètre	

	signed long accX,accZ,gyro,tetaAcc,tetaGyro,teta;


	//conversion tension > vitesse en °/secondes, accélération en 10g.mm/s²
	accX = 100*(tAccX-tAccX0)/tAccX1;
	accZ = 100*(tAccZ-tAccZ0)/tAccZ1;
	gyro = -100*(tGyro-tGyro0)/tGyro1;

//calcul de l'angle donné par les accéléromètres
	//mettre xpp en 10g mm/s²
	//gm/s² = 100 . (10g mm/s²)
	//rad->deg => *180/pi = 57.3
	//teta en decidegrés
	//normalement : tetaAcc= 10*(57*((accX+accZ)-(xpp+100))/(100-xpp));
	tetaAcc = ((accX+accZ-xpp-100)*57)/((100-xpp)/10);
	if(tetaAcc>150) {tetaAcc=150;  defautBorne=1;}
	if(tetaAcc<-150){tetaAcc=-150; defautBorne=1;}

//calcul de l'angle donné par le gyro en decidegrés
	//°/s * ms  => m° On divise par 100 pour l'avoir en decidegrés
	tetaGyro = gyro*te/100 + tetaPrec;

//barycentre - filtre de Kalman 
	//teta en decidegrés
	tetaAngle = ( a * tetaAcc + (1000-a) * tetaGyro ) / (1000); //a entre 0 et 1000 inclus

	//vitesse en °/s
	tetaVitesse = gyro; 
}



//emuler une classe c++
short valeurTetaAngle(void)
{
	return tetaAngle;
}
short valeurtetaVitesse(void)
{
	return tetaVitesse;
}
char presenceDefautBorne(void)
{
	return defautBorne;
}