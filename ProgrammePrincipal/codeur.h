/** \file 
Fonctions traitant des codeurs incr�mentaux. Calcul de la position, de la vitesse et de l'acc�l�ration moyenne selon l'axe du trajet (utilis� par les acc�l�rom�tres).
\author    Adrien Jaegy et Emilie CHHIM
 */

#ifndef CODEUR_H
#define CODEUR_H


struct Sroues{
///�  (entre -180 et +180)
	float positionGauche; 
///�  (entre -180 et +180)
	float positionDroite; 
///m
	float distanceMoyenneParcourue; 
///�/s
	float vitesseGauche; 
///�/s
	float vitesseDroite; 
///km/h -> prend en compte le rayon
	float vitesseMoyenne; 
///entre 0 et 1, vaut 0,6 si en moyenne, les moteur tournent � 60% de leur vitesse maxi
	float utilisationMoteur; 
///m/s�	-> utiliser le rayon
	float accMoyenne; 
///signe du codeur Gauche (donn� par la dascule D)
	char signeGauche;
///signe du codeur Gauche (donn� par la dascule D)
	char signeDroite;
};




//fonctions publiques

/*!
Fonction � appeler � chaque changement de signe de sens de rotation du codeur Gauche (d�tect� par les bascules D) et avant chaque boucle d'asservissement.(juste avant demande de calcul)\n
Elle vide le compteur de front et ajoute ces fronts au compteur courant.\n
\param[in] signe    Valeur du signe actuel (vaut la valeur de la sortie de la bascule D en principe).
*/
void interruptionCodeurG(char signe);

/*!
Fonction � appeler � chaque changement de signe de sens de rotation du codeur Gauche (d�tect� par les bascules D) et avant chaque boucle d'asservissement.(juste avant demande de calcul)\n
Elle vide le compteur de front et ajoute ces fronts au compteur courant.\n
\param[in] signe    Valeur du signe actuel (vaut la valeur de la sortie de la bascule D en principe).
*/
void interruptionCodeurD(char signe); 

/*!
Fonction � appeler au d�marrage du programme pour initialiser les variables internes du fichier codeur.\n
R�appeler la fonction pour faire un RAZ des vitesses, positions et acc�l�rations.
*/
void initCodeurs(void); //au d�but

/*!
Permet de calculer position, vitesse et acc�l�ration de la M2. A appeler � chaque boucle d'asservissement.
\param[in] deltaT   temps �coul� depuis le dernier appel (pour le calcul des vitesses) en ms.
\return une structure roue contenant toutes les informations des codeurs (avec les traitements).
*/
struct Sroues lancerCalculsCodeur(float deltaT);


#endif

