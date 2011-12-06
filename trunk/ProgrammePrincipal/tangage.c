#include "include.h"
#include "tangage.h"
#include "tools.h"
#include "brochage.h"
#include "variablesGlobales.h"


const far rom char printf_tangage_1[]="/r/n%d";


//degrés, degrés/s


short calibrageTangage(void)
{
	long temp=0;

	long i;
	tAccX0=0; tAccX1=0; tAccZ0=0; tAccZ1=0; tGyro0=0; tGyro1=0;

	
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
		temp-=tGyro0;
		pauseMs(1);
	}
	

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
			chargerTangage();
			return ERREUR;
		}
	}


	//etape 9 : si on veut conserver les paramètres, on les enregistre
	enregistrerTangage();

	LED_CENTRE_VERTE = LED_ON;
	pauseMs(500);
	LED_HAUT = LED_OFF;
	LED_BAS = LED_OFF;
	LED_GAUCHE = LED_OFF;
	LED_DROITE = LED_OFF;
	LED_CENTRE_VERTE = LED_OFF;



	return OK;

}





struct Stangage angleTangage(short tAccX, short tAccZ, short tGyro, float xpp, float tetaPrec, float te)
{
//tAccX, tAccZ, tGyro
	//sortie brute du CAN entre 0 et 1024
//te en ms
//tetaPrec en decidegrés
//xpp est l'accélération lue par les codeurs, à donner en m/s²
	

	float accX,accZ,gyro,tetaAcc,tetaGyro,teta; //redimensionnés et à l'chelle
	struct Stangage angle;


	//conversion tension > vitesse en °/secondes, accélération en m/s²
	accX = 9.81*(float)(tAccX-tAccX0)/(float)tAccX1;
	accZ = -9.81*(float)(tAccZ-tAccZ0)/(float)tAccZ1;
	gyro = -100.*(float)(tGyro-tGyro0)/(float)tGyro1;

//calcul de l'angle donné par les accéléromètres
	//rad->deg => *180/pi = 57.3
	tetaAcc = ((accX+accZ-xpp-9.81)*57.3)/(9.81-xpp);
//	if(tetaAcc>15.) {tetaAcc=15.;  angle.defautBorne=1;}
//	if(tetaAcc<-15.){tetaAcc=-15.; angle.defautBorne=1;}

//calcul de l'angle donné par le gyro en decidegrés
	//°/s * ms  => m° On divise par 1000 pour l'avoir en degrés
	tetaGyro = gyro*te/1000. + tetaPrec;

//barycentre - filtre de Kalman 
	//teta en degrés
	angle.teta = COEF_KALMAN * tetaAcc + (1.-COEF_KALMAN) * tetaGyro ; //a entre 0 et 1

	//vitesse en °/s
	angle.vitesse = gyro; 

	return angle;
}

