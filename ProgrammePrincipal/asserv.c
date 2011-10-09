#include "include.h"
#include "asserv.h"
#include "brochage.h"
#include "tools.h"
#include "tangage.h"
#include "autresES.h"
#include "consigne.h"
#include "codeur.h"
#include "variablesGlobales.h"

char boucleAsservissement(char reinit) //renvoie false si erreur ou utilisateur "perdu"
{
	
	short tAccX,tAccZ, tGyro,tGuidon, tBatterie,tCentrifuge;
	struct Sroues roues;
	struct Stangage tangage;
	float angleVise,coupleT, guidonTraite, te;
	struct Sconsigne couples;
	unsigned short duree;
	static float anglePrec=0., hysterisisAngleVise=0.;
	static unsigned short tempsPrec = 0;

	//gestion du reinit
	if(reinit)
	{
		anglePrec=0.;
		hysterisisAngleVise=0.;
		tempsPrec = 0;
		initCodeurs();
		return TRUE;
	}

	//gestion du temps ATTENTION AU PAS FLOATTTTTT
		duree= tempsEcouleDepuisMs(tempsPrec);
		tempsPrec=globalTime;	
		te=duree;

	//verifier si l'utilisateur est encore
		//si non, initier la proc�dure d'arret
		 if(presenceUtilisateur()==NON) return FALSE; 
	
	// Lecture des entr�es  analogiques
		//liste d'appel � acquisition(); du fichier tools.c
		tAccX=acquisition(CH_ACC_X);
		tAccZ=acquisition(CH_ACC_Z);
		tGyro=acquisition(CH_GYRO);
		tGuidon=acquisition(CH_POTENTIOMETRE_GUIDON);
		tBatterie=acquisition(CH_BATTERIE);
		tCentrifuge=acquisition(CH_ACC_CENTRIFUGE);

	// Calcul des vitesses de rotation + acc�l�ration
		//dans codeur.c
		roues = lancerCalculsCodeur(te);
	
	//Transforme les valeurs pour d�terminer l'angle de tangage
		//utilisation de tangage.c pour calculer l'angle de tangage [en r�alit�, l'angle, sa d�riv�e, un indicateur de saturation]
		tangage = angleTangage(tAccX, tAccZ, tGyro, roues.accMoyenne, anglePrec, te);
		anglePrec = tangage.teta;

	// Calcul de la consigne de couple g�n�rale
		//consigne.c qui calcule le pid pour obtenir le couple moyen
		angleVise = consigneAngle(roues.utilisationMoteur, hysterisisAngleVise, tangage.teta);
		hysterisisAngleVise = angleVise;
		coupleT = coupleTotal(angleVise,  tangage.teta,  tangage.vitesse);

	// Prise en consid�ration de l�inclinaison du guidon
		//consigne.c
		guidonTraite = guidonTrMin(tGuidon);
		couples = partagerCouple(coupleT, roues.vitesseGauche, roues.vitesseDroite, guidonTraite); //guidon + = aller + vite � gauche dc tourner a droite;


	// Envoi des consignes de couple moteur droit et gauche au microcontr�leur de commande moteur
		//rien de sp�cial, utiliser communication.c
		envoyerConsigneDeCouple(couples.coupleG, couples.coupleD);

	return TRUE;
}





char testDemarrage(void)
{
	static unsigned short dateDebutDernierEquilibre=0;
	unsigned short delai;
	short tAccX,tAccZ, tGyro,tGuidon;
	struct Stangage tangage;
	float guidon, angle;

	//lecture des entr�es
	tAccX=acquisition(CH_ACC_X);
	tAccZ=acquisition(CH_ACC_Z);
	tGuidon=acquisition(CH_POTENTIOMETRE_GUIDON);
	tangage = angleTangage(tAccX, tAccZ, tGyro, 0,0,0);
	angle = tangage.teta;
	guidon = guidonTrMin(tGuidon);

	//led des c�t�s
	LED_GAUCHE	= (guidon < -DEMARRAGE_TOL_GUIDON);
	LED_DROITE	= (guidon > DEMARRAGE_TOL_GUIDON);
	LED_HAUT	= (angle >  DEMARRAGE_TOL_ANGLE);
	LED_BAS		= (angle <  -DEMARRAGE_TOL_ANGLE);
	//le du centre : un seul des 4 = pas bon
	LED_CENTRE_ORANGE = !(LED_GAUCHE|LED_DROITE|LED_HAUT|LED_BAS);

	if(LED_CENTRE_ORANGE)
	{
		if(presenceUtilisateur())
		{
			delai = tempsEcouleDepuisMs(dateDebutDernierEquilibre);

			if((delai>DEMARRAGE_DELAI_EQUILIBRE)&&(delai<2*DEMARRAGE_DELAI_EQUILIBRE)) //si on avait oubli� de r�initialiser
			{
				LED_CENTRE_ORANGE = LED_OFF;
				LED_CENTRE_VERTE = LED_ON;
				return OK;
			}
			return ERREUR;
		}

		else //si on est droit pas qu'il n'y a pas d'utilisateur 
		{
			LED_GAUCHE	= LED_ON;
			LED_DROITE	= LED_ON;
			LED_HAUT	= LED_ON;
			LED_BAS		= LED_ON;
		}
	}

	dateDebutDernierEquilibre=globalTime;
	return ERREUR;
}

