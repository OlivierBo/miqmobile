#include "include.h"
#include "variablesGlobales.h"
#include "brochage.h"
#include "tools.h"

//ASSERVISSEMENT
float PRINC_PID_K=20;
float PRINC_PID_D=10;
float PRINC_DIR=30;
float COEF_KALMAN=0.2;
float ACCELERATION_COEF_FILTRE=0.5;

//TANGAGE
//calibrage (0 pour la valeur signifiant 0, 1 pour la valeur unité 9.81m/s pour les accéléro et °/cs  pour le gyro)
short tAccX0 , tAccX1, tAccZ0, tAccZ1, tGyro0, tGyro1;

//DEMARRAGE
float LIMITE_DISTANCE_UTILISATEUR=1000; //mm : 
float DEMARRAGE_TOL_ANGLE=2; //2 en °
float DEMARRAGE_TOL_GUIDON=5; //5 en tr/min sur soi meme
float DEMARRAGE_DELAI_EQUILIBRE=2000; //2000 en ms

//GUIDON
short tGuidon0 , tGuidonMax;
float GUIDONMAX=20;

//VITESSE
float VITESSE_TROITTOIR_MAX;
float POURCENT_SECURITE_MOTEUR; //a partir de quand activer le freinage de sécurité
float COEF_HYSTERISIS_SECURITE; //la variable de réglage de l'hystérisis


//variables renseignées par l'uart
float inf_coupleG=0, inf_coupleD=0;
char inf_etatCouple=0, inf_demandeOnOff=0;
short verboseMode;


void chargerAsservissement(void)
{
	unsigned short i=EEPROM_ASSERVISSEMENT;
	unsigned char longueur=4;
	readEeprom(&PRINC_PID_K, i, longueur); i+=longueur;
	readEeprom(&PRINC_PID_D, i, longueur); i+=longueur;
	readEeprom(&PRINC_DIR, i, longueur); i+=longueur;
	readEeprom(&COEF_KALMAN, i, longueur); i+=longueur;
	readEeprom(&ACCELERATION_COEF_FILTRE, i, longueur); i+=longueur;
}

void enregistrerAsservissement(void)
{
	unsigned short i=EEPROM_ASSERVISSEMENT;
	unsigned char longueur = 4; 
	writeEeprom(&PRINC_PID_K, i, longueur); i+=longueur;
	writeEeprom(&PRINC_PID_D, i, longueur); i+=longueur;
	writeEeprom(&PRINC_DIR, i, longueur); i+=longueur;
	writeEeprom(&COEF_KALMAN, i, longueur); i+=longueur;
	writeEeprom(&ACCELERATION_COEF_FILTRE, i, longueur); i+=longueur;
}


void chargerTangage()
{
	unsigned short i=EEPROM_TANGAGE;
	unsigned char longueur = 2;

	readEeprom(&tAccX0, i, longueur); i+=longueur;
	readEeprom(&tAccX1, i, longueur); i+=longueur;
	readEeprom(&tAccZ0, i, longueur); i+=longueur;
	readEeprom(&tAccZ1, i, longueur); i+=longueur;
	readEeprom(&tGyro0, i, longueur); i+=longueur;
	readEeprom(&tGyro1, i, longueur); i+=longueur;
}

void enregistrerTangage()
{
	unsigned short i=EEPROM_TANGAGE;
	unsigned char longueur = 2;

	writeEeprom(&tAccX0, i, longueur); i+=longueur;
	writeEeprom(&tAccX1, i, longueur); i+=longueur;
	writeEeprom(&tAccZ0, i, longueur); i+=longueur;
	writeEeprom(&tAccZ1, i, longueur); i+=longueur;
	writeEeprom(&tGyro0, i, longueur); i+=longueur;
	writeEeprom(&tGyro1, i, longueur); i+=longueur;

}


void chargerGuidon(void)
{
	unsigned short i=EEPROM_GUIDON;
	unsigned char longueur = 4;

	readEeprom(&GUIDONMAX, i, longueur); i+=longueur;

	longueur = 2;
	readEeprom(&tGuidon0, i, longueur);   i+=longueur;
	readEeprom(&tGuidonMax, i, longueur);  i+=longueur;

}

void enregistrerGuidon(void)
{
	unsigned short i=EEPROM_GUIDON;
	unsigned char longueur = 4;

	writeEeprom(&GUIDONMAX, i, longueur); i+=longueur;

	longueur=2;
	writeEeprom(&tGuidon0, i, longueur);   i+=longueur;
	writeEeprom(&tGuidonMax, i, longueur);  i+=longueur;
}



void chargerDemarrage(void)
{
	unsigned short i=EEPROM_DEMARRAGE;
	unsigned char longueur = 4;

	readEeprom(&LIMITE_DISTANCE_UTILISATEUR, i, longueur); i+=longueur;
	readEeprom(&DEMARRAGE_TOL_ANGLE, i, longueur);   i+=longueur;
	readEeprom(&DEMARRAGE_TOL_GUIDON, i, longueur);  i+=longueur;
	readEeprom(&DEMARRAGE_DELAI_EQUILIBRE, i, longueur);  i+=longueur;
}

void enregistrerDemarrage(void)
{
	unsigned short i=EEPROM_DEMARRAGE;
	unsigned char longueur = 4;

	writeEeprom(&LIMITE_DISTANCE_UTILISATEUR, i, longueur); i+=longueur;
	writeEeprom(&DEMARRAGE_TOL_ANGLE, i, longueur);   i+=longueur;
	writeEeprom(&DEMARRAGE_TOL_GUIDON, i, longueur);  i+=longueur;
	writeEeprom(&DEMARRAGE_DELAI_EQUILIBRE, i, longueur);  i+=longueur;
}

void chargerVitesse(void)
{
	unsigned short i=EEPROM_VITESSE;
	unsigned char longueur = 4;

	readEeprom(&VITESSE_TROITTOIR_MAX, i, longueur); i+=longueur;
	readEeprom(&POURCENT_SECURITE_MOTEUR, i, longueur);   i+=longueur;
	readEeprom(&COEF_HYSTERISIS_SECURITE, i, longueur);  i+=longueur;
}

void enregistrerVitesse(void)
{
	unsigned short i=EEPROM_VITESSE;
	unsigned char longueur = 4;

	writeEeprom(&VITESSE_TROITTOIR_MAX, i, longueur); i+=longueur;
	writeEeprom(&POURCENT_SECURITE_MOTEUR, i, longueur);  i+=longueur;
	writeEeprom(&COEF_HYSTERISIS_SECURITE, i, longueur);  i+=longueur;
}