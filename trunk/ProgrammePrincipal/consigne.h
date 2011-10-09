#ifndef CONSIGNE_H
#define CONSIGNE_H

struct Sconsigne
{
	float coupleT;
	float coupleG;
	float coupleD;
};

float coupleTotal(float consigne, float angle, float vitesseAngle);
struct Sconsigne partagerCouple(float couple, float vitesseG, float vitesseD, float guidon); //guidon + = aller + vite à gauche dc tourner a droite;
float consigneAngle(float utilisationMoteur, float hysterisisAngleVise, float tangage);

#endif