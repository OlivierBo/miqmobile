#include "include.h"
#include "codeur.h"
#include "consigne.h"
#include "variablesGlobales.h"


short coupleMoyen(short consigne, short angle, short vitesseAngle) //en degré et degré/s (à redim)
{
	//calcul de l'erreur
	short erreur = consigne - angle;
	short sortie10; //vaut 10 fois la consigne de couple réel (voulu)
	
	//calcul de la dérivée de l'erreur
	// Derreur = Dconsigne - Dangle, avec consigne = cte ->
	// Derreur = - Dangle = - vitesseAngle;


	sortie10 = erreur * PRINC_PID_K10 - vitesseAngle * PRINC_PID_D10; //en N



	return sortie10;

//le couple total des deux moteurs (limité par le pont en H) avant le reducteur
//max 255


}



void partagerCouple(short* coupleG, short* coupleD, short couple, short vitesseG, short vitesseD, short guidon) //guidon + = aller + vite à gauche dc tourner a droite
{
	short dvN = vitesseG-vitesseD;
	short dvG = guidon / 5;
	short cons = (dvN - dvG) * PRINC_DIR10;
	*coupleG = couple/2 - cons;
	*coupleD = couple/2 + cons;

	//60.dv/(2.pi.distance roue a roue) = nb de tours sur soi meme/min
	//dif de vit lin = guidon.pi.e(m)/30
	//dif de vit de rot. = dif de vit lin / rayon de la roue
	//dv+ = guidon.pi.e(mm)/[30.r(mm)] = guidon.e/10.r = guidon/5
}