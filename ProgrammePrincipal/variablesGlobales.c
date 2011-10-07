#include "include.h"
#include "variablesGlobales.h"
#include "brochage.h"
#include "tools.h"

float PRINC_PID_K;
float PRINC_PID_D;
float PRINC_DIR;
float COEF_KALMAN;
float ACCELERATION_COEF_FILTRE;
short tAccX0 , tAccX1, tAccZ0, tAccZ1, tGyro0, tGyro1;

void genererCoefParDefaut()
{
	PRINC_PID_K=20;
	PRINC_PID_D=10;
	PRINC_DIR=30;
	COEF_KALMAN=0.2;
	ACCELERATION_COEF_FILTRE=0.5;
}

void chargerTousLesCoef(void)
{
	unsigned short i=EEPROM_COEF;
	unsigned char longueur=4;
	readEeprom(&PRINC_PID_K, i, longueur); i+=longueur;
	readEeprom(&PRINC_PID_D, i, longueur); i+=longueur;
	readEeprom(&PRINC_DIR, i, longueur); i+=longueur;
	readEeprom(&COEF_KALMAN, i, longueur); i+=longueur;
	readEeprom(&ACCELERATION_COEF_FILTRE, i, longueur); i+=longueur;
}

void enregistrerTousLesCoef(void)
{
	unsigned short i=EEPROM_COEF;
	unsigned char longueur = 4; 
	writeEeprom(&PRINC_PID_K, i, longueur); i+=longueur;
	writeEeprom(&PRINC_PID_D, i, longueur); i+=longueur;
	writeEeprom(&PRINC_DIR, i, longueur); i+=longueur;
	writeEeprom(&COEF_KALMAN, i, longueur); i+=longueur;
	writeEeprom(&ACCELERATION_COEF_FILTRE, i, longueur); i+=longueur;
}


void chargerValeurDeCalibration()
{
	unsigned short i=EEPROM_CALIBRATION;
	unsigned char longueur = 2;

	readEeprom(&tAccX0, i, longueur); i+=longueur;
	readEeprom(&tAccX1, i, longueur); i+=longueur;
	readEeprom(&tAccZ0, i, longueur); i+=longueur;
	readEeprom(&tAccZ1, i, longueur); i+=longueur;
	readEeprom(&tGyro0, i, longueur); i+=longueur;
	readEeprom(&tGyro1, i, longueur); i+=longueur;
}

void enregistrerValeurDeCalibration()
{
	unsigned short i=EEPROM_CALIBRATION;
	unsigned char longueur = 2;

	writeEeprom(&tAccX0, i, longueur); i+=longueur;
	writeEeprom(&tAccX1, i, longueur); i+=longueur;
	writeEeprom(&tAccZ0, i, longueur); i+=longueur;
	writeEeprom(&tAccZ1, i, longueur); i+=longueur;
	writeEeprom(&tGyro0, i, longueur); i+=longueur;
	writeEeprom(&tGyro1, i, longueur); i+=longueur;
}
