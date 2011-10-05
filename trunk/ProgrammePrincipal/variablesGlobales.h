#ifndef GLOBAL_H
#define GLOBAL_H


//eeprom -> memoire : CHARGER
//readEeprom(void* data, unsigned short adress,  unsigned char longueur);
//memoire -> eeprom : ENREGISTRER
//writeEeprom(void* data, unsigned short adress,  unsigned char longueur);
//usart -> memoire  : MODIFIER
//memoire -> usart  : CONSULTER



//calibrage tangage
void enregistrerValeurDeCalibration(void);
void chargerValeurDeCalibration(void);

//coef pd,a, dir
void chargerTousLesCoef(void);
void enregistrerTousLesCoef(void);
void genererCoefParDefaut();

extern short PRINC_PID_K10;
extern short PRINC_PID_D10;
extern short PRINC_DIR10;
extern short COEF_KALMAN10; // = 1000 => 100% de confiance dans l'accéléromètre	
extern short ACCELERATION_COEF_FILTRE;
extern short tAccX0 , tAccX1, tAccZ0, tAccZ1, tGyro0, tGyro1;

#endif


