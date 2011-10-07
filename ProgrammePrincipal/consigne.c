#include "include.h"
#include "codeur.h"
#include "consigne.h"
#include "variablesGlobales.h"


float coupleTotal(float consigne, float angle, float vitesseAngle) //en degré et degré/s 
{
	//calcul de l'erreur
	float erreur = consigne - angle;
	float sortie; 
	
	//calcul de la dérivée de l'erreur
	// Derreur = Dconsigne - Dangle, avec consigne = cte ->
	// Derreur = - Dangle = - vitesseAngle;


	sortie = erreur * PRINC_PID_K - vitesseAngle * PRINC_PID_D; //en N


	return sortie;

//le couple total des deux moteurs (limité par le pont en H) avant le reducteur
//max 255


}



struct Sconsigne partagerCouple(float couple, float vitesseG, float vitesseD, float guidon) //guidon + = aller + vite à gauche dc tourner a droite
{
	float dvN = vitesseG-vitesseD;
	float dvG = guidon / 5;
	float cons = (dvN - dvG) * PRINC_DIR;
	struct Sconsigne lescouples;
	lescouples.coupleG = couple/2 - cons;
	lescouples.coupleD = couple/2 + cons;
	lescouples.coupleT=couple;

	//60.dv/(2.pi.distance roue a roue) = nb de tours sur soi meme/min
	//dif de vit lin = guidon.pi.e(m)/30
	//dif de vit de rot. = dif de vit lin / rayon de la roue
	//dv+ = guidon.pi.e(mm)/[30.r(mm)] = guidon.e/10.r = guidon/5
}