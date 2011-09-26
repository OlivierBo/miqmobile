#include "include.h"
#include "tangage.h"

short tAccX, tAccZ, tGyro, xpp, tetaPrec, te;

struct ang{
	short angle;
	short vAngulaire;
};


short angleTangage(short tAccX, short tAccZ, short tGyro, short xpp, short tetaPrec, short te)
{
//tAccX, tAccZ, tGyro
	//sortie brute du CAN entre 0 et 1024
//te en ms
//tetaPrec en decidegrés
//xpp est l'accélération lue par les codeurs, à donner en 10g mm/s²
	
//calibrage (0 pour la valeur signifiant 0, 1 pour la valeur unité 9.81m/s pour les accéléro et °/cs  pour le gyro)
	signed short tAccX0 = 608, tAccX1 = 136, tAccZ0 = 618, tAccZ1 = 99, tGyro0 = 301, tGyro1 = 971;
	long a = 15; //[0;100] , a = 100 => 100% de confiance dans l'accéléromètre	

	signed short accX,accZ,gyro,tetaAcc,tetaGyro,teta;
long temp;

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

//calcul de l'angle donné par le gyro en decidegrés
	//°/s * ms  => m° On divise par 100 pour l'avoir en decidegrés
	tetaGyro = gyro*te/100 + tetaPrec;

//barycentre - filtre de Kalman 
	//teta en decidegrés
	//a entre 0 et 100 inclus
	
temp = ( a * tetaAcc + (100-a) * tetaGyro ) / (100);
teta=temp;
	return teta;
}


