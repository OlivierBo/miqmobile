/** \file 
Fonctions traitant des codeurs incrémentaux. Calcul de la position, de la vitesse et de l'accélération moyenne selon l'axe du trajet (utilisé par les accéléromètres).
\author    Adrien Jaegy et Emilie CHHIM
 */

#ifndef CODEUR_H
#define CODEUR_H


struct Sroues{
///°  (entre -180 et +180)
	float positionGauche; 
///°  (entre -180 et +180)
	float positionDroite; 
///m
	float distanceMoyenneParcourue; 
///°/s
	float vitesseGauche; 
///°/s
	float vitesseDroite; 
///km/h -> prend en compte le rayon
	float vitesseMoyenne; 
///entre 0 et 1, vaut 0,6 si en moyenne, les moteur tournent à 60% de leur vitesse maxi
	float utilisationMoteur; 
///m/s²	-> utiliser le rayon
	float accMoyenne; 
///signe du codeur Gauche (donné par la dascule D)
	char signeGauche;
///signe du codeur Gauche (donné par la dascule D)
	char signeDroite;
};




//fonctions publiques

/*!
Fonction à appeler à chaque changement de signe de sens de rotation du codeur Gauche (détecté par les bascules D) et avant chaque boucle d'asservissement.(juste avant demande de calcul)\n
Elle vide le compteur de front et ajoute ces fronts au compteur courant.\n
\param[in] signe    Valeur du signe actuel (vaut la valeur de la sortie de la bascule D en principe).
*/
void interruptionCodeurG(char signe);

/*!
Fonction à appeler à chaque changement de signe de sens de rotation du codeur Gauche (détecté par les bascules D) et avant chaque boucle d'asservissement.(juste avant demande de calcul)\n
Elle vide le compteur de front et ajoute ces fronts au compteur courant.\n
\param[in] signe    Valeur du signe actuel (vaut la valeur de la sortie de la bascule D en principe).
*/
void interruptionCodeurD(char signe); 

/*!
Fonction à appeler au démarrage du programme pour initialiser les variables internes du fichier codeur.\n
Réappeler la fonction pour faire un RAZ des vitesses, positions et accélérations.
*/
void initCodeurs(void); //au début

/*!
Permet de calculer position, vitesse et accélération de la M2. A appeler à chaque boucle d'asservissement.
\param[in] deltaT   temps écoulé depuis le dernier appel (pour le calcul des vitesses) en ms.
\return une structure roue contenant toutes les informations des codeurs (avec les traitements).
*/
struct Sroues lancerCalculsCodeur(float deltaT);


#endif

