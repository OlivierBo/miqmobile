/** \file 
Toutes les proc�dures traitant de l'angle de tangage : son calcul et sa calibration.
\author    Adrien Jaegy
 */
#ifndef TANGAGE_H
#define TANGAGE_H


///Structure contenant toutes les informations de tangage
struct Stangage
{
///angle de tangage en degr�s
	float teta; 
///vitesse angulaire de l'angle de tangage en �/s
	float vitesse; 
///vaut 1 si angle trop grand (et donc faux)
	char defautBorne;
};

/*!
Boucle d'asservissement globale du Segway. 
A chaque appel, elle s'occupe de lire les donnees capteurs, calculer les gains et envoyer les consignes aux moteurs.
\param[in] tAccX    sortie brute du CAN de l'acc�l�rom�tre en X
\param[in] tAccZ    sortie brute du CAN de l'acc�l�rom�tre en Z
\param[in] tGyro    sortie brute du CAN du gyroscope
\param[in] xpp      acc�l�ration lue par les codeurs, � donner en m/s�
\param[in] tetaPrec angle de tanage pr�c�dent en degr�s
\param[in] te   dur�e �coul�e depuis le dernier appel en ms
\return une structure tangage contenant l'angle et la vitesse angulaire de tangage
*/
struct Stangage angleTangage(short tAccX, short tAccZ, short tGyro, float xpp, float tetaPrec, float te);


/*!
D�marrer la proc�dure de calibrage de l'angle de tangage.
\return ERREUR si la calibration a �chou�e ou n'a pas �t� enregistr�e et OK si la nouvelle calibration a �t� enregistr�e.
*/short calibrageTangage(void);



#endif


