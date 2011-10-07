#ifndef CODEUR_H
#define CODEUR_H

struct Sroues{
  float vitesseGauche; //°/s
  float vitesseDroite; //°/s
  float positionGauche; //°  (entre -180 et +180)
  float positionDroit; //°  (entre -180 et +180)
  float accGauche; //m/s² -> utiliser le rayon
  float accDroite; //m/²	-> utiliser le rayon
  float vitesseMoyenne; //km/h -> utiliser le rayon
  float distanceMoyenneParcourue; //m
};

//fonctions publiques
void interruptionCodeurG(void);
void interruptionCodeurD(void);
void initCodeurs(float rayon);
struct Sroues lancerCalculsCodeur(float deltaT); //deltaT en ms

// le coefficient du filtre se nomme : float ACCELERATION_COEF_FILTRE

#endif

