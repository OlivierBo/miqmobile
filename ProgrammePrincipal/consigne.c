#include "include.h"
#include "codeur.h"
#include "consigne.h"


short pid_K=1, pid_D=1;

short coupleMoyen(short consigne, short angle, short vitesseAngle)
{
	//calcul de l'erreur
	short erreur = consigne - angle;
	short sortie;
	
	//calcul de la dérivée de l'erreur
	// Derreur = Dconsigne - Dangle, avec consigne = cte ->
	// Derreur = - Dangle = - vitesseAngle;


	sortie = erreur * pid_K - vitesseAngle * pid_D; //en N

	//redim pour changer l'unité et s'adapter à l'échelle (32 000 = couple max du moteur)

	return sortie;
}



short coef_guidon=30;

void partagerCouple(short* coupleG, short* coupleD, short couple, short vitesseG, short vitesseD, short guidon) //guidon + = aller + vite à gauche dc tourner a droite
{
	short dvN = vitesseG-vitesseD;
	short dvG = guidon / 5;
	short cons = (dvN - dvG) * coef_guidon;
	*coupleG = couple/2 - cons;
	*coupleD = couple/2 + cons;

	//60.dv/(2.pi.distance roue a roue) = nb de tours sur soi meme/min
	//dif de vit lin = guidon.pi.e(m)/30
	//dif de vit de rot. = dif de vit lin / rayon de la roue
	//dv+ = guidon.pi.e(mm)/[30.r(mm)] = guidon.e/10.r = guidon/5
}