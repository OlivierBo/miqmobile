#include "include.h"
#include "asserv.h"
#include "brochage.h"


void boucleAsservissement(void)
{
	//verifier si l'utilisateur est encore
		//si non, initier la proc�dure d'arret
	
	// Lecture des entr�es  analogiques
		//liste d'appel � acquisition(); du fichier tools.c
		//r�cup�ration de la valeur du gyro r�ceptionn�e par interruption

	// Calcul des vitesses de rotation + acc�l�ration
		//dans codeur.c
	
	//Transforme les valeurs pour d�terminer l'angle de tangage
		//utilisation de tangage.c pour calculer l'angle de tangage [en r�alit�, l'angle, sa d�riv�e, un indicateur de saturation]

	// Calcul de la consigne de couple g�n�rale
		//consigne.c qui calcule le pid pour obtenir le couple moyen

	// Prise en consid�ration de l�inclinaison du guidon
		//consigne.c

	// Envoi des consignes de couple moteur droit et gauche au microcontr�leur de commande moteur
		//rien de sp�cial, utiliser communication.c

}

