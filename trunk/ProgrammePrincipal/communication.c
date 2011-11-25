#include "include.h"
#include "communication.h"
#include "brochage.h"
#include "variablesGlobales.h"

/* Déclaration des variables globales définies dans xbee_comm.h */
volatile unsigned char CON_DEPART;



//! Fonction générique d'envoi de trame (sans buffer !)
void envoiTrameUart1 (char type, void * data, char data_length) {
	char checksum, i;
	
	//Envoi de l'octet de début
	while(Busy1USART());
	Write1USART(DEBUT_TRAME);
	checksum = DEBUT_TRAME;
	//Envoi de l'octet de type
	while(Busy1USART());
	Write1USART(type);
	checksum ^= type;
	//Envoi des données
	for (i = 0; i < data_length; i++) {
		while(Busy1USART());
		Write1USART(((char*)(data))[i]);
		checksum ^= ((char*)(data))[i];
	}
	//Envoi de l'octet de checksum
	while(Busy1USART());
	Write1USART(checksum);
}



void interruptionRxTrame(unsigned char rxByte) {
// Tampon réception de caractère
    unsigned char resetTrame = FALSE;					// Flag de reset des compteurs de trame (en cas de fin de trame ou d'erreur)
    //Ces variables sont en statique car leur valeur ne change pas entre 2 appels MAIS on n'en a pas besoin ailleurs
    static unsigned char rxCount = 0;					//Nombre d'octets réceptionnés
    static char checkSum = 0;					//Somme de contrôle courante
    static unsigned char trameErr = TRAME_ERR_NOERR;	//Indique si une erreur est survenue
    static unsigned char trameBuf [10];	//Buffer de réception trame
    static unsigned char curTrameType = 0;				//Le XBee peut recevoir plusieurs types de trames 
    static unsigned char curTrameLength = 0;			//Ces deux variables contiennent le type et la longueur de la trame actuelle

	
	//Teste s'il y a dépassement de capacité du tampon de réception
	if (RCSTA1bits.OERR) {
		rxCount = 0;	//On recommence à 0
		checkSum = 0;
		trameErr = TRAME_ERR_NOERR;
	} RCSTA1bits.OERR = 0;
	
    trameBuf[rxCount] = rxByte;		//Enregistre l'octet reçu dans le buffer de réception

    //Premier octet de la trame : on attend l'octet de départ (@)
    if (rxCount == 0) {
	    trameErr += TRAME_ERR_DEBUT * (rxByte != DEBUT_TRAME);
	}  
	//Deuxième octet : indique le type de trame. On enregistre le type et la longueur de trame attendue
	else if (rxCount == 1) {
		curTrameType = rxByte;
		switch (curTrameType) {
			case TYPE_TRAME_CON_TEST_COM: curTrameLength= LG_TRAME_CON_TEST_COM ; break;
			case TYPE_TRAME_CON_DEPART: curTrameLength= LG_TRAME_CON_DEPART ; break;
			case TYPE_TRAME_CON_STOP: curTrameLength= LG_TRAME_CON_STOP ; break;
			case TYPE_TRAME_INF_ETAT: curTrameLength= LG_TRAME_INF_ETAT ; break;
			case TYPE_TRAME_INF_ETAT_BATTERIE: curTrameLength= LG_TRAME_INF_ETAT_BATTERIE ; break;
			case TYPE_TRAME_INF_ANGLE_HORS_INTERVALLE: curTrameLength= LG_TRAME_INF_ANGLE_HORS_INTERVALLE ; break;
			case TYPE_TRAME_INF_ANGLE_TANGAGE: curTrameLength= LG_TRAME_INF_ANGLE_TANGAGE ; break;
			case TYPE_TRAME_INF_VITESSE_ANGULAIRE: curTrameLength= LG_TRAME_INF_VITESSE_ANGULAIRE ; break;
			case TYPE_TRAME_CON_COUPLED: curTrameLength= LG_TRAME_CON_COUPLED ; break;
			case TYPE_TRAME_INF_COUPLED: curTrameLength= LG_TRAME_INF_COUPLED ; break;
			case TYPE_TRAME_CON_COUPLEG: curTrameLength= LG_TRAME_CON_COUPLEG ; break;
			case TYPE_TRAME_INF_COUPLEG: curTrameLength= LG_TRAME_INF_COUPLEG ; break;
			case TYPE_TRAME_INF_ERREUR_CARTE_COURANT: curTrameLength= LG_TRAME_INF_ERREUR_CARTE_COURANT ; break;
			case TYPE_TRAME_INF_PRET: curTrameLength= LG_TRAME_INF_PRET ; break;
			case TYPE_TRAME_INF_VITESSED: curTrameLength= LG_TRAME_INF_VITESSED ; break;
			case TYPE_TRAME_INF_VITESSEG: curTrameLength= LG_TRAME_INF_VITESSEG ; break;
			case TYPE_TRAME_INF_DISTANCE_PARCOURUE: curTrameLength= LG_TRAME_INF_DISTANCE_PARCOURUE ; break;
			case TYPE_TRAME_INF_ACCELERATION: curTrameLength= LG_TRAME_INF_ACCELERATION ; break;
			case TYPE_TRAME_CON_CHARGER_VITESSE: curTrameLength= LG_TRAME_CON_CHARGER_VITESSE ; break;
			case TYPE_TRAME_CON_ENREGISTRER_VITESSE: curTrameLength= LG_TRAME_CON_ENREGISTRER_VITESSE ; break;
			case TYPE_TRAME_CON_CHARGER_ASSERVISSEMENT: curTrameLength= LG_TRAME_CON_CHARGER_ASSERVISSEMENT ; break;
			case TYPE_TRAME_CON_ENREGISTRER_ASSERVISSEMENT: curTrameLength= LG_TRAME_CON_ENREGISTRER_ASSERVISSEMENT ; break;
			case TYPE_TRAME_CON_CHARGER_DEMARRAGE: curTrameLength= LG_TRAME_CON_CHARGER_DEMARRAGE ; break;
			case TYPE_TRAME_CON_ENREGISTRER_DEMARRAGE: curTrameLength= LG_TRAME_CON_ENREGISTRER_DEMARRAGE ; break;
			case TYPE_TRAME_CON_PRINC_PID_K: curTrameLength= LG_TRAME_CON_PRINC_PID_K ; break;
			case TYPE_TRAME_CON_PRINC_PID_D: curTrameLength= LG_TRAME_CON_PRINC_PID_D ; break;
			case TYPE_TRAME_CON_PRINC_DIR: curTrameLength= LG_TRAME_CON_PRINC_DIR ; break;
			case TYPE_TRAME_CON_COEF_KALMAN: curTrameLength= LG_TRAME_CON_COEF_KALMAN ; break;
			case TYPE_TRAME_CON_ACCELERATION_COEF_FILTRE: curTrameLength= LG_TRAME_CON_ACCELERATION_COEF_FILTRE ; break;
			case TYPE_TRAME_CON_GUIDONMAX: curTrameLength= LG_TRAME_CON_GUIDONMAX ; break;
			case TYPE_TRAME_CON_LIMITE_DISTANCE_UTILISATEUR: curTrameLength= LG_TRAME_CON_LIMITE_DISTANCE_UTILISATEUR ; break;
			case TYPE_TRAME_CON_DEMARRAGE_TOL_ANGLE: curTrameLength= LG_TRAME_CON_DEMARRAGE_TOL_ANGLE ; break;
			case TYPE_TRAME_CON_DEMARRAGE_TOL_GUIDON: curTrameLength= LG_TRAME_CON_DEMARRAGE_TOL_GUIDON ; break;
			case TYPE_TRAME_CON_DEMARRAGE_DELAI_EQUILIBRE: curTrameLength= LG_TRAME_CON_DEMARRAGE_DELAI_EQUILIBRE ; break;
			case TYPE_TRAME_CON_VITESSE_TROITTOIR_MAX: curTrameLength= LG_TRAME_CON_VITESSE_TROITTOIR_MAX ; break;
			case TYPE_TRAME_CON_POURCENT_SECURITE_MOTEUR: curTrameLength= LG_TRAME_CON_POURCENT_SECURITE_MOTEUR ; break;
			case TYPE_TRAME_CON_COEF_HYSTERISIS_SECURITE: curTrameLength= LG_TRAME_CON_COEF_HYSTERISIS_SECURITE ; break;
			case TYPE_TRAME_INF_PRINC_PID_K: curTrameLength= LG_TRAME_INF_PRINC_PID_K ; break;
			case TYPE_TRAME_INF_PRINC_PID_D: curTrameLength= LG_TRAME_INF_PRINC_PID_D ; break;
			case TYPE_TRAME_INF_PRINC_DIR: curTrameLength= LG_TRAME_INF_PRINC_DIR ; break;
			case TYPE_TRAME_INF_COEF_KALMAN: curTrameLength= LG_TRAME_INF_COEF_KALMAN ; break;
			case TYPE_TRAME_INF_ACCELERATION_COEF_FILTRE: curTrameLength= LG_TRAME_INF_ACCELERATION_COEF_FILTRE ; break;
			case TYPE_TRAME_INF_GUIDONMAX: curTrameLength= LG_TRAME_INF_GUIDONMAX ; break;
			case TYPE_TRAME_INF_LIMITE_DISTANCE_UTILISATEUR: curTrameLength= LG_TRAME_INF_LIMITE_DISTANCE_UTILISATEUR ; break;
			case TYPE_TRAME_INF_DEMARRAGE_TOL_ANGLE: curTrameLength= LG_TRAME_INF_DEMARRAGE_TOL_ANGLE ; break;
			case TYPE_TRAME_INF_DEMARRAGE_TOL_GUIDON: curTrameLength= LG_TRAME_INF_DEMARRAGE_TOL_GUIDON ; break;
			case TYPE_TRAME_INF_DEMARRAGE_DELAI_EQUILIBRE: curTrameLength= LG_TRAME_INF_DEMARRAGE_DELAI_EQUILIBRE ; break;
			case TYPE_TRAME_INF_VITESSE_TROITTOIR_MAX: curTrameLength= LG_TRAME_INF_VITESSE_TROITTOIR_MAX ; break;
			case TYPE_TRAME_INF_POURCENT_SECURITE_MOTEUR: curTrameLength= LG_TRAME_INF_POURCENT_SECURITE_MOTEUR ; break;
			case TYPE_TRAME_INF_COEF_HYSTERISIS_SECURITE: curTrameLength= LG_TRAME_INF_COEF_HYSTERISIS_SECURITE ; break;
			case TYPE_TRAME_CON_COEF_COURANT_1: curTrameLength= LG_TRAME_CON_COEF_COURANT_1 ; break;
			case TYPE_TRAME_INF_COEF_COURANT_1: curTrameLength= LG_TRAME_INF_COEF_COURANT_1 ; break;
			case TYPE_TRAME_CON_COEF_COURANT_2: curTrameLength= LG_TRAME_CON_COEF_COURANT_2 ; break;
			case TYPE_TRAME_INF_COEF_COURANT_2: curTrameLength= LG_TRAME_INF_COEF_COURANT_2 ; break;
			case TYPE_TRAME_INF_VERBOSE: curTrameLength= LG_TRAME_INF_VERBOSE ; break;
			case TYPE_TRAME_CON_VERBOSE: curTrameLength= LG_TRAME_CON_VERBOSE ; break;
			case TYPE_TRAME_CON_DEMANDE_COEFFICIENTS: curTrameLength= LG_TRAME_CON_DEMANDE_COEFFICIENTS ; break;


			default: trameErr += TRAME_ERR_TYPE;
		}	
	}
	//Octets suivants : données de la trame
	//Dernier octet : checksum
	else if (rxCount == curTrameLength - 1) {
		trameErr += TRAME_ERR_CHECK * (rxByte != checkSum);
		if (trameErr == 0) {
			switch (curTrameType) {
				//EXEMPLES
				//case TYPE_TRAME_INF_COUPLED:  memcpy((void*)&inf_coupleD, (void*)(trameBuf), 4) ; break;
				//case TYPE_TRAME_INF_ERREUR_CARTE_COURANT: inf_etatCouple=trameBuf[0]; break;
				
				case TYPE_TRAME_CON_TEST_COM:   ; break;
				case TYPE_TRAME_CON_DEPART:   ; break;
				case TYPE_TRAME_CON_STOP:   ; break;
				case TYPE_TRAME_INF_ETAT:   ; break;
				case TYPE_TRAME_INF_ETAT_BATTERIE:   ; break;
				case TYPE_TRAME_CON_DEMANDE_COEFFICIENTS:   ; break;
				case TYPE_TRAME_INF_ANGLE_HORS_INTERVALLE:   ; break;
				case TYPE_TRAME_INF_ANGLE_TANGAGE:   ; break;
				case TYPE_TRAME_INF_VITESSE_ANGULAIRE:   ; break;
				case TYPE_TRAME_CON_COUPLED:   ; break;
				case TYPE_TRAME_INF_COUPLED:   ; break;
				case TYPE_TRAME_CON_COUPLEG:   ; break;
				case TYPE_TRAME_INF_COUPLEG:   ; break;
				case TYPE_TRAME_INF_ERREUR_CARTE_COURANT:   ; break;
				case TYPE_TRAME_INF_PRET:   ; break;
				case TYPE_TRAME_INF_VITESSED:   ; break;
				case TYPE_TRAME_INF_VITESSEG:   ; break;
				case TYPE_TRAME_INF_DISTANCE_PARCOURUE:   ; break;
				case TYPE_TRAME_INF_ACCELERATION:   ; break;
				case TYPE_TRAME_CON_CHARGER_VITESSE:   ; break;
				case TYPE_TRAME_CON_ENREGISTRER_VITESSE:   ; break;
				case TYPE_TRAME_CON_CHARGER_ASSERVISSEMENT:   ; break;
				case TYPE_TRAME_CON_ENREGISTRER_ASSERVISSEMENT:   ; break;
				case TYPE_TRAME_CON_CHARGER_DEMARRAGE:   ; break;
				case TYPE_TRAME_CON_ENREGISTRER_DEMARRAGE:   ; break;
				case TYPE_TRAME_CON_PRINC_PID_K:   ; break;
				case TYPE_TRAME_CON_PRINC_PID_D:   ; break;
				case TYPE_TRAME_CON_PRINC_DIR:   ; break;
				case TYPE_TRAME_CON_COEF_KALMAN:   ; break;
				case TYPE_TRAME_CON_ACCELERATION_COEF_FILTRE:   ; break;
				case TYPE_TRAME_CON_GUIDONMAX:   ; break;
				case TYPE_TRAME_CON_LIMITE_DISTANCE_UTILISATEUR:   ; break;
				case TYPE_TRAME_CON_DEMARRAGE_TOL_ANGLE:   ; break;
				case TYPE_TRAME_CON_DEMARRAGE_TOL_GUIDON:   ; break;
				case TYPE_TRAME_CON_DEMARRAGE_DELAI_EQUILIBRE:   ; break;
				case TYPE_TRAME_CON_VITESSE_TROITTOIR_MAX:   ; break;
				case TYPE_TRAME_CON_POURCENT_SECURITE_MOTEUR:   ; break;
				case TYPE_TRAME_CON_COEF_HYSTERISIS_SECURITE:   ; break;
				case TYPE_TRAME_INF_PRINC_PID_K:   ; break;
				case TYPE_TRAME_INF_PRINC_PID_D:   ; break;
				case TYPE_TRAME_INF_PRINC_DIR:   ; break;
				case TYPE_TRAME_INF_COEF_KALMAN:   ; break;
				case TYPE_TRAME_INF_ACCELERATION_COEF_FILTRE:   ; break;
				case TYPE_TRAME_INF_GUIDONMAX:   ; break;
				case TYPE_TRAME_INF_LIMITE_DISTANCE_UTILISATEUR:   ; break;
				case TYPE_TRAME_INF_DEMARRAGE_TOL_ANGLE:   ; break;
				case TYPE_TRAME_INF_DEMARRAGE_TOL_GUIDON:   ; break;
				case TYPE_TRAME_INF_DEMARRAGE_DELAI_EQUILIBRE:   ; break;
				case TYPE_TRAME_INF_VITESSE_TROITTOIR_MAX:   ; break;
				case TYPE_TRAME_INF_POURCENT_SECURITE_MOTEUR:   ; break;
				case TYPE_TRAME_INF_COEF_HYSTERISIS_SECURITE:   ; break;
				case TYPE_TRAME_CON_COEF_COURANT_1:   ; break;
				case TYPE_TRAME_INF_COEF_COURANT_1:   ; break;
				case TYPE_TRAME_CON_COEF_COURANT_2:   ; break;
				case TYPE_TRAME_INF_COEF_COURANT_2:   ; break;
				case TYPE_TRAME_INF_VERBOSE:   ; break;
				case TYPE_TRAME_CON_VERBOSE:   ; break;

				default: break;
				
			} 
			resetTrame = TRUE;
		} 
	}
		
	//Si fin de trame ou erreur
	//Remet le compteur de trame, la somme de controle et l'erreur à zéro
	if (resetTrame || trameErr != TRAME_ERR_NOERR) {		
		rxCount = 0;	//On recommence à 0
		checkSum = 0;
		trameErr = TRAME_ERR_NOERR;
	} 
	//Met à jour la somme de contrôle avec l'octer reçu et passe à l'octet suivant pour le prochain appel
	else {	
		if (rxCount == 0) 	checkSum = rxByte;
		else checkSum ^= rxByte;
		rxCount++;	
	}
}
//*********************************************************************************************************************************

//! Fonction générique d'envoi de trame (sans buffer !)
void envoiTrameUart2 (char type, void * data, char data_length) {
	char checksum, i;
	
	//Envoi de l'octet de début
	while(Busy2USART());
	Write2USART(DEBUT_TRAME);
	checksum = DEBUT_TRAME;
	//Envoi de l'octet de type
	while(Busy2USART());
	Write2USART(type);
	checksum ^= type;
	//Envoi des données
	for (i = 0; i < data_length; i++) {
		while(Busy2USART());
		Write2USART(((char*)(data))[i]);
		checksum ^= ((char*)(data))[i];
	}
	//Envoi de l'octet de checksum
	while(Busy2USART());
	Write2USART(checksum);
}



void interruptionRxOctet(unsigned char rxByte) {
	switch(rxByte)
	{
		case 't': LED_ERREUR=!LED_ERREUR; break;
		default: break;
	}
}

