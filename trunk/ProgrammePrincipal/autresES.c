#include "include.h"
#include "asserv.h"
#include "brochage.h"
#include "tools.h"
#include "autresES.h"
#include "variablesGlobales.h"
#include "ultrason.h"



float guidonTrMin(short tGuidon)
{
	float guidonTraite = GUIDONMAX *(tGuidon - tGuidon0)/(float)tGuidonMax ;
	//positif = guidon a droite, sinon changer le signe
	return  guidonTraite; //possibilité de changer le signe...
}

char presenceUtilisateur(void)
{
	//bouton, us? a choisir...
	if(distanceUS()==0) return NON;
	if(distanceUS()<(short)LIMITE_DISTANCE_UTILISATEUR)
	return OUI;
	else
	return NON;
}


short calibrerGuidon(void)
{
	long i;
	tGuidon0 =0;  tGuidonMax =0;  

	//etape 1 : signaler qu'on est en mode calibrage
	LED_BAS = LED_ON; //bas = calib guidon
	LED_HAUT = LED_OFF;
	LED_GAUCHE = LED_OFF;
	LED_DROITE = LED_OFF;
	LED_CENTRE_VERTE = LED_OFF;
	LED_CENTRE_ORANGE = LED_OFF;
	pauseMs(2000);


	//etape 2 : avertir de la mesure du 0
	LED_HAUT = LED_ON;
	pauseMs(1500);

	//etape 3 : mesurer la verticale pendant 1s à une fréquence de 20Hz
	LED_CENTRE_VERTE = LED_ON;
	for(i=0;i<20;i++)
	{
		tGuidon0+=acquisition(CH_POTENTIOMETRE_GUIDON);
		pauseMs(50);
	}
	tGuidon0/=20;
	LED_CENTRE_VERTE=LED_OFF;


	//etape 2 : avertir de la mesure de la droite (ou du moins, dans le sens d'augmentation du voltage)
	LED_HAUT = LED_OFF;
	LED_DROITE = LED_ON;
	pauseMs(2500);

	//etape 3 : mesurer la verticale pendant 1s à une fréquence de 20Hz
	LED_CENTRE_VERTE = LED_ON;
	for(i=0;i<20;i++)
	{
		tGuidonMax+=acquisition(CH_POTENTIOMETRE_GUIDON);
		pauseMs(50);
	}
	tGuidonMax/=20;
	if(tGuidonMax>tGuidon0)	tGuidonMax-=tGuidon0;
	else tGuidonMax=tGuidon0-tGuidonMax; //si jamais le sens est mauvaise, autocorrige



	//etape 8 : demander si on veut conserver le calibrage
	LED_HAUT = LED_ON;
	Delay10TCYx (1); //il faut laisser le temps 
	LED_BAS = LED_ON;
	Delay10TCYx (1);
	LED_GAUCHE = LED_ON;
	LED_DROITE = LED_ON;
	LED_CENTRE_VERTE = LED_OFF;
	


	while(BOUTON_VERT==0)
	{
		if(BOUTON_ROUGE) 
		{
		   	LED_HAUT = LED_OFF;
			LED_BAS = LED_OFF;
			LED_GAUCHE = LED_OFF;
			LED_DROITE = LED_OFF;
			LED_CENTRE_VERTE = LED_ON;
			pauseMs(1500);
			LED_CENTRE_VERTE = LED_OFF;
			return ERREUR;
		}
	}


	//etape 9 : si on veut conserver les paramètres, on les enregistre
	enregistrerGuidon();

   	LED_HAUT = LED_OFF;
	LED_BAS = LED_OFF;
	LED_GAUCHE = LED_OFF;
	LED_DROITE = LED_OFF;
	LED_CENTRE_VERTE = LED_ON;
	pauseMs(1500);
	LED_CENTRE_VERTE = LED_OFF;


	return OK;

}