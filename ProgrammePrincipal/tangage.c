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
//tetaPrec en decidegr�s
//xpp est l'acc�l�ration lue par les codeurs, � donner en 10g mm/s�
	
//calibrage (0 pour la valeur signifiant 0, 1 pour la valeur unit� 9.81m/s pour les acc�l�ro et �/cs  pour le gyro)
	signed short tAccX0 = 504, tAccX1 = 94, tAccZ0 = 504, tAccZ1 = 94, tGyro0 = 444, tGyro1 = 47;
	char a = 20; //[0;100] , a = 100 => 100% de confiance dans l'acc�l�rom�tre	

	signed short accX,accZ,gyro,tetaAcc,tetaGyro,teta;

	//conversion tension > vitesse en �/secondes, acc�l�ration en 10g.mm/s�
	accX = 100*(tAccX-tAccX0)/tAccX1;
	accZ = 100*(tAccZ-tAccZ0)/tAccZ1;
	gyro = -100*(tGyro-tGyro0)/tGyro1;

//calcul de l'angle donn� par les acc�l�rom�tres
	//mettre xpp en 10g mm/s�
	//gm/s� = 100 . (10g mm/s�)
	//rad->deg => *180/pi = 57.3
	//teta en decidegr�s
	//normalement : tetaAcc= 10*(57*((accX+accZ)-(xpp+100))/(100-xpp));
	tetaAcc = ((accX+accZ-xpp-100)*57)/((100-xpp)/10);

//calcul de l'angle donn� par le gyro en decidegr�s
	//�/s * ms  => m� On divise par 100 pour l'avoir en decidegr�s
	tetaGyro = gyro*te/100 + tetaPrec;

//barycentre - filtre de Kalman 
	//teta en decidegr�s
	//a entre 0 et 100 inclus
	teta = ( a * tetaAcc + (100-a) * tetaGyro ) / (100);

	return teta;
}


