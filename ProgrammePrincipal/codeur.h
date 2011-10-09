#ifndef CODEUR_H
#define CODEUR_H


struct Sroues{
	float positionGauche; //°  (entre -180 et +180)
	float positionDroit; //°  (entre -180 et +180)
	float distanceMoyenneParcourue; //m

	float vitesseGauche; //°/s
	float vitesseDroite; //°/s
	float vitesseMoyenne; //km/h -> utiliser le rayon
	float utilisationMoteur; //entre 0 et 1, vaut 0,6 si en moyenne, les moteur tournent à 60% de leur vitesse maxi
	
	float accMoyenne; //m/s²	-> utiliser le rayon
};

//fonctions publiques
void interruptionCodeurG(void);
void interruptionCodeurD(void);
void initCodeurs(void);
struct Sroues lancerCalculsCodeur(float deltaT); //deltaT en ms

// le coefficient du filtre se nomme : ACCELERATION_COEF_FILTRE (en float)
//sont aussi disponible (dans le fichier variables globales.h) : GRANDEUR_RAYON_ROUE (en mm) et GRANDEUR_VITESSE_MAX (en tr/min )

#endif

