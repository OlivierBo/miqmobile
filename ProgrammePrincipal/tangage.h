/** \file 
Toutes les procédures traitant de l'angle de tangage : son calcul et sa calibration.
\author    Adrien Jaegy
 */
#ifndef TANGAGE_H
#define TANGAGE_H


///Structure contenant toutes les informations de tangage
struct Stangage
{
///angle de tangage en degrés
	float teta; 
///vitesse angulaire de l'angle de tangage en °/s
	float vitesse; 
///vaut 1 si angle trop grand (et donc faux)
	char defautBorne;
};

/*!
Boucle d'asservissement globale du Segway. 
A chaque appel, elle s'occupe de lire les donnees capteurs, calculer les gains et envoyer les consignes aux moteurs.
\param[in] tAccX    sortie brute du CAN de l'accéléromètre en X
\param[in] tAccZ    sortie brute du CAN de l'accéléromètre en Z
\param[in] tGyro    sortie brute du CAN du gyroscope
\param[in] xpp      accélération lue par les codeurs, à donner en m/s²
\param[in] tetaPrec angle de tanage précédent en degrés
\param[in] te   durée écoulée depuis le dernier appel en ms
\return une structure tangage contenant l'angle et la vitesse angulaire de tangage
*/
struct Stangage angleTangage(short tAccX, short tAccZ, short tGyro, float xpp, float tetaPrec, float te);


/*!
Démarrer la procédure de calibrage de l'angle de tangage.
\return ERREUR si la calibration a échouée ou n'a pas été enregistrée et OK si la nouvelle calibration a été enregistrée.
*/short calibrageTangage(void);



#endif


