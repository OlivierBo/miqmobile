#ifndef CODEUR_H
#define CODEUR_H

struct roues{
  long vitesseGauche; //mm/s
  long vitesseDroit; //mm/s
  long positionGauche; //mm
  long positionDroit; //mm
  long accGauche; //10g mm/s²
  long accDroit; //10g mm/s²
  long distanceMoyenneParcourue; //m
};

//fonctions publiques
void interruptionCodeurG(void);
void interruptionCodeurD(void);
void initCodeurs(short rayon);
void lancerCalculsCodeur(short deltaT, short coefFiltre);



//roue.vitesseGauche=4100;
//#define USE_AND_MASKS

#endif

