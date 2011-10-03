#include "include.h"
#include "communication.h"
#include <usart.h>

/* Déclaration des variables globales définies dans xbee_comm.h */
volatile unsigned char CON_DEPART;



//! Fonction générique d'envoi de trame (sans buffer !)
void envoiTrameUart1 (char type, void * data, char data_length) {
	unsigned char checksum, i;
	
	//Envoi de l'octet de début
	while(Busy1USART());
	Write1USART(DEBUT_TRAME);
	checksum = DEBUT_TRAME;
	//Envoi de l'octet de type
	while(Busy1USART());
	Write1USART(type);
	checksum += type;
	//Envoi des données
	for (i = 0; i < data_length; i++) {
		while(Busy1USART());
		Write1USART(((char*)(data))[i]);
		checksum += ((char*)(data))[i];
	}
	//Envoi de l'octet de checksum
	while(Busy1USART());
	Write1USART(checksum);
}



void interruptionRx1(unsigned char rxByte) {
// Tampon réception de caractère
    unsigned char resetTrame = FALSE;					// Flag de reset des compteurs de trame (en cas de fin de trame ou d'erreur)
    //Ces variables sont en statique car leur valeur ne change pas entre 2 appels MAIS on n'en a pas besoin ailleurs
    static unsigned char rxCount = 0;					//Nombre d'octets réceptionnés
    static unsigned char checkSum = 0;					//Somme de contrôle courante
    static unsigned char trameErr = TRAME_ERR_NOERR;	//Indique si une erreur est survenue
    static unsigned char trameBuf [10];	//Buffer de réception trame
    static unsigned char curTrameType = 0;				//Le XBee peut recevoir plusieurs types de trames 
    static unsigned char curTrameLength = 0;			//Ces deux variables contiennent le type et la longueur de la trame actuelle

	
	//Teste s'il y a dépassement de capacité du tampon de réception
	if (U1STAbits.OERR) {
		rxCount = 0;	//On recommence à 0
		checkSum = 0;
		trameErr = TRAME_ERR_NOERR;
	} U1STAbits.OERR = 0;
	
    trameBuf[rxCount] = rxByte;		//Enregistre l'octet reçu dans le buffer de réception

    //Premier octet de la trame : on attend l'octet de départ (@)
    if (rxCount == 0) {
	    trameErr += TRAME_ERR_DEBUT * (rxByte != DEBUT_TRAME);
	}  
	//Deuxième octet : indique le type de trame. On enregistre le type et la longueur de trame attendue
	else if (rxCount == 1) {
		curTrameType = rxByte;
		switch (curTrameType) {
			case TYPE_TRAME_CON_COUPLEG: curTrameLength= LG_TRAME_CON_COUPLEG ; break;
			case TYPE_TRAME_CON_COUPLED: curTrameLength= LG_TRAME_CON_COUPLED ; break;
			case TYPE_TRAME_INF_COUPLEG: curTrameLength= LG_TRAME_INF_COUPLEG ; break;
			case TYPE_TRAME_INF_COUPLED: curTrameLength= LG_TRAME_INF_COUPLED ; break;
			case TYPE_TRAME_INF_ERREUR_CARTE_COURANT: curTrameLength= LG_TRAME_INF_ERREUR_CARTE_COURANT ; break;
			case TYPE_TRAME_INF_VITESSEG: curTrameLength= LG_TRAME_INF_VITESSEG ; break;
			case TYPE_TRAME_INF_VITESSED: curTrameLength= LG_TRAME_INF_VITESSED ; break;
			case TYPE_TRAME_INF_PRINC_PID_K: curTrameLength= LG_TRAME_INF_PRINC_PID_K ; break;
			case TYPE_TRAME_CON_PRINC_PID_K: curTrameLength= LG_TRAME_CON_PRINC_PID_K ; break;
			case TYPE_TRAME_INF_PRINC_PID_I: curTrameLength= LG_TRAME_INF_PRINC_PID_I ; break;
			case TYPE_TRAME_CON_PRINC_PID_I: curTrameLength= LG_TRAME_CON_PRINC_PID_I ; break;
			case TYPE_TRAME_INF_PRINC_PID_D: curTrameLength= LG_TRAME_INF_PRINC_PID_D ; break;
			case TYPE_TRAME_CON_PRINC_PID_D: curTrameLength= LG_TRAME_CON_PRINC_PID_D ; break;
			case TYPE_TRAME_INF_PRINC_DIR: curTrameLength= LG_TRAME_INF_PRINC_DIR ; break;
			case TYPE_TRAME_CON_PRINC_DIR: curTrameLength= LG_TRAME_CON_PRINC_DIR ; break;
			case TYPE_TRAME_INF_ANGLE: curTrameLength= LG_TRAME_INF_ANGLE ; break;
			case TYPE_TRAME_INF_VITESSE_ANGULAIRE: curTrameLength= LG_TRAME_INF_VITESSE_ANGULAIRE ; break;
			case TYPE_TRAME_INF_ACCELERATION: curTrameLength= LG_TRAME_INF_ACCELERATION ; break;
			case TYPE_TRAME_CON_ACCELERATION_COEF_FILTRE: curTrameLength= LG_TRAME_CON_ACCELERATION_COEF_FILTRE ; break;
			case TYPE_TRAME_INF_COEF_KALMAN: curTrameLength= LG_TRAME_INF_COEF_KALMAN ; break;
			case TYPE_TRAME_CON_COEF_KALMAN: curTrameLength= LG_TRAME_CON_COEF_KALMAN ; break;
			case TYPE_TRAME_CON_SAUVEGARDER_COEF: curTrameLength= LG_TRAME_CON_SAUVEGARDER_COEF ; break;
			case TYPE_TRAME_INF_DISTANCE_PARCOURUE: curTrameLength= LG_TRAME_INF_DISTANCE_PARCOURUE ; break;
			case TYPE_TRAME_INF_ETAT_BATTERIE: curTrameLength= LG_TRAME_INF_ETAT_BATTERIE ; break;
			case TYPE_TRAME_CON_STOP: curTrameLength= LG_TRAME_CON_STOP ; break;
			case TYPE_TRAME_CON_DEPART: curTrameLength= LG_TRAME_CON_DEPART ; break;
			case TYPE_TRAME_INF_PRET: curTrameLength= LG_TRAME_INF_PRET ; break;
			case TYPE_TRAME_INF_ETAT: curTrameLength= LG_TRAME_INF_ETAT ; break;
			case TYPE_TRAME_CON_TEST_COM: curTrameLength= LG_TRAME_CON_TEST_COM ; break;
			case TYPE_TRAME_INF_SATURATION_VITESSE: curTrameLength= LG_TRAME_INF_SATURATION_VITESSE ; break;
			case TYPE_TRAME_CON_SATURATION_VITESSE: curTrameLength= LG_TRAME_CON_SATURATION_VITESSE ; break;
			case TYPE_TRAME_INF_ANGLE_HORS_INTERVALLE: curTrameLength= LG_TRAME_INF_ANGLE_HORS_INTERVALLE ; break;
			case TYPE_TRAME_CON_RECHARGER_COEF: curTrameLength= LG_TRAME_CON_RECHARGER_COEF ; break;

			default: trameErr += TRAME_ERR_TYPE;
		}	
	}
	//Octets suivants : données de la trame
	//Dernier octet : checksum
	else if (rxCount == curTrameLength - 1) {
		trameErr += TRAME_ERR_CHECK * (rxByte != checkSum);
		if (trameErr == 0) {
			switch (curTrameType) {
				
				case TYPE_TRAME_CON_DEPART:
					CON_DEPART = trameBuf[3];
					break;				
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
		checkSum += rxByte;
		rxCount++;	
	}
}

