#include "include.h"
#include "asserv.h"
#include "brochage.h"
#include "tools.h"


void boucleAsservissement(void)
{
	static unsigned short tempsPrec = 0;
	unsigned short duree = tempsEcouleDepuisMs(tempsPrec);
	tempsPrec=globalTime;
	if(duree>1000) duree=0;	//ca fait plus d'une seconde que l'asserv n'a pas été appelé
	

	//verifier si l'utilisateur est encore
		//si non, initier la procédure d'arret
	
	// Lecture des entrées  analogiques
		//liste d'appel à acquisition(); du fichier tools.c
		//récupération de la valeur du gyro réceptionnée par interruption

	// Calcul des vitesses de rotation + accélération
		//dans codeur.c
	
	//Transforme les valeurs pour déterminer l'angle de tangage
		//utilisation de tangage.c pour calculer l'angle de tangage [en réalité, l'angle, sa dérivée, un indicateur de saturation]

	// Calcul de la consigne de couple générale
		//consigne.c qui calcule le pid pour obtenir le couple moyen

	// Prise en considération de l’inclinaison du guidon
		//consigne.c

	// Envoi des consignes de couple moteur droit et gauche au microcontrôleur de commande moteur
		//rien de spécial, utiliser communication.c

}

