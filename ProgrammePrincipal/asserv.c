#include "include.h"
#include "asserv.h"
#include "brochage.h"
#include "tools.h"
#include "tangage.h"
#include "autresES.h"
#include "consigne.h"
#include "codeur.h"
#include "variablesGlobales.h"
#include "communication.h"

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
		//si non, initier la procédure d'arret
		 if(presenceUtilisateur()==NON) return FALSE; 
	
	// Lecture des entrées  analogiques
		//liste d'appel à acquisition(); du fichier tools.c
		tAccX=acquisition(CH_ACC_X);
		tAccZ=acquisition(CH_ACC_Z);
		tGyro=acquisition(CH_GYRO);
		tGuidon=acquisition(CH_POTENTIOMETRE_GUIDON);
		tBatterie=acquisition(CH_BATTERIE);
		tCentrifuge=acquisition(CH_ACC_CENTRIFUGE);

	// Calcul des vitesses de rotation + accélération
		//dans codeur.c
		roues = lancerCalculsCodeur(te);
	
	//Transforme les valeurs pour déterminer l'angle de tangage
		//utilisation de tangage.c pour calculer l'angle de tangage [en réalité, l'angle, sa dérivée, un indicateur de saturation]
		tangage = angleTangage(tAccX, tAccZ, tGyro, roues.accMoyenne, anglePrec, te);
		anglePrec = tangage.teta;

	// Calcul de la consigne de couple générale
		//consigne.c qui calcule le pid pour obtenir le couple moyen
		angleVise = consigneAngle(roues.utilisationMoteur, hysterisisAngleVise, tangage.teta);
		hysterisisAngleVise = angleVise;
		coupleT = coupleTotal(angleVise,  tangage.teta,  tangage.vitesse);

	// Prise en considération de l’inclinaison du guidon
		//consigne.c
		guidonTraite = guidonTrMin(tGuidon);
		couples = partagerCouple(coupleT, roues.vitesseGauche, roues.vitesseDroite, guidonTraite); //guidon + = aller + vite à gauche dc tourner a droite;


	// Envoi des consignes de couple moteur droit et gauche au microcontrôleur de commande moteur
		//rien de spécial, utiliser communication.c
		if(inf_demandeOnOff<4)
		{
			envoiTrameUart2(TYPE_TRAME_CON_COUPLED,(void*)(&couples.coupleD),LG_TRAME_CON_COUPLED);
			envoiTrameUart2(TYPE_TRAME_CON_COUPLEG,(void*)(&couples.coupleG),LG_TRAME_CON_COUPLEG);
		}

   //envoi des valeurs dynamiques
		//tout à zéro : ne rien envoyer
		if(getbit(verboseMode,1)) envoiTrameUart1(TYPE_TRAME_INF_ETAT,(void*)(&inf_demandeOnOff),LG_TRAME_INF_ETAT);
		if(getbit(verboseMode,2)) envoiTrameUart1(TYPE_TRAME_INF_ETAT_BATTERIE,(void*)(&tBatterie),LG_TRAME_INF_ETAT_BATTERIE);
		if(getbit(verboseMode,3)) envoiTrameUart1(TYPE_TRAME_INF_ANGLE_HORS_INTERVALLE,(void*)(&tangage.defautBorne),LG_TRAME_INF_ANGLE_HORS_INTERVALLE);
		if(getbit(verboseMode,4)) envoiTrameUart1(TYPE_TRAME_INF_ANGLE_TANGAGE,(void*)(&tangage.teta),LG_TRAME_INF_ANGLE_TANGAGE);
		if(getbit(verboseMode,5)) envoiTrameUart1(TYPE_TRAME_INF_VITESSE_ANGULAIRE,(void*)(&tangage.vitesse),LG_TRAME_INF_VITESSE_ANGULAIRE);
		if(getbit(verboseMode,6)) envoiTrameUart1(TYPE_TRAME_INF_VITESSED,(void*)(&roues.vitesseDroite),LG_TRAME_INF_VITESSED);
		if(getbit(verboseMode,7)) envoiTrameUart1(TYPE_TRAME_INF_VITESSEG,(void*)(&roues.vitesseGauche),LG_TRAME_INF_VITESSEG);
		if(getbit(verboseMode,8)) envoiTrameUart1(TYPE_TRAME_INF_DISTANCE_PARCOURUE,(void*)(&roues.distanceMoyenneParcourue),LG_TRAME_INF_DISTANCE_PARCOURUE);
		if(getbit(verboseMode,9)) envoiTrameUart1(TYPE_TRAME_INF_ACCELERATION,(void*)(&roues.accMoyenne),LG_TRAME_INF_ACCELERATION);
		if(getbit(verboseMode,10)) envoiTrameUart1(TYPE_TRAME_INF_COUPLED,(void*)(&inf_coupleD),LG_TRAME_INF_COUPLED);
		if(getbit(verboseMode,11)) envoiTrameUart1(TYPE_TRAME_INF_COUPLEG,(void*)(&inf_coupleG),LG_TRAME_INF_COUPLEG);


	return TRUE;
}





char testDemarrage(void)
{
	static unsigned short dateDebutDernierEquilibre=0;
	unsigned short delai;
	short tAccX,tAccZ, tGyro,tGuidon;
	struct Stangage tangage;
	float guidon, angle;

	//lecture des entrées
	tAccX=acquisition(CH_ACC_X);
	tAccZ=acquisition(CH_ACC_Z);
	tGuidon=acquisition(CH_POTENTIOMETRE_GUIDON);
	tangage = angleTangage(tAccX, tAccZ, tGyro, 0,0,0);
	angle = tangage.teta;
	guidon = guidonTrMin(tGuidon);

	//led des côtés
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

			if((delai>DEMARRAGE_DELAI_EQUILIBRE)&&(delai<2*DEMARRAGE_DELAI_EQUILIBRE)) //si on avait oublié de réinitialiser
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

