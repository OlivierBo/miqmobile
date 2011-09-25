#ifndef CODEUR_H
#define CODEUR_H

struct roues{
	short vitesseGauche;
	short vitesseDroit;
	short positionGauche;
	short positionDroit;
	short accGauche;
	short accDroit;
};

//fonctions publiques
void interruptionCodeur(void);

void initCodeurs(void);
unsigned long distanceMoyenneCodeur(void);
short vitesseCodeurDroit(short deltaT);
short vitesseCodeurGauche(short deltaT);
short accelerationCodeurDroit(short deltaT);
short accelerationCodeurGauche(short deltaT);



#endif

