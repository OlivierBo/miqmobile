#include "include.h"
#include "asserv.h"
#include "brochage.h"


void boucleAsservissement(void)
{
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

