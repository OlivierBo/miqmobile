#ifndef GLOBAL_H
#define GLOBAL_H


//eeprom -> memoire : CHARGER
//readEeprom(void* data, unsigned short adress,  unsigned char longueur);
//memoire -> eeprom : ENREGISTRER
//writeEeprom(void* data, unsigned short adress,  unsigned char longueur);
//usart -> memoire  : MODIFIER
//memoire -> usart  : CONSULTER

#define DEMARRAGE_TOL_ANGLE 2 //en °
#define DEMARRAGE_TOL_GUIDON 5 //en tr/min sur soi meme
#define DEMARRAGE_DELAI_EQUILIBRE 2000 //en ms

#define GRANDEUR_RAYON_ROUE 30. //en mm
#define GRANDEUR_EMPATEMENT 50. //en mm
#define GRANDEUR_VITESSE_MAX 2000. //en tr/min 
#define PI_ 3.14159265

//calibrage tangage
void enregistrerValeurDeCalibration(void);
void chargerValeurDeCalibration(void);

//coef pd,a, dir
void chargerTousLesCoef(void);
void enregistrerTousLesCoef(void);
void genererCoefParDefaut(void);

//juste le guidon (pour l'instant)
void chargerGuidon(void);
void enregistrerGuidon(void);


extern float PRINC_PID_K;
extern float PRINC_PID_D;
extern float PRINC_DIR;
extern float COEF_KALMAN; 
extern float ACCELERATION_COEF_FILTRE;

extern short tAccX0 , tAccX1, tAccZ0, tAccZ1, tGyro0, tGyro1;
extern short tGuidon0 , tGuidonMax, guidonMax; 
// tguidonmax : de combien, en valeur can, le guidon peut il bouger?
//guidonMax : lorsque le guidon est au max, ca correspond a combien de tour/min

#endif


