#ifndef GLOBAL_H
#define GLOBAL_H


//eeprom -> memoire : CHARGER
//readEeprom(void* data, unsigned short adress,  unsigned char longueur);
//memoire -> eeprom : ENREGISTRER
//writeEeprom(void* data, unsigned short adress,  unsigned char longueur);
//usart -> memoire  : MODIFIER
//memoire -> usart  : CONSULTER

#define GRANDEUR_RAYON_ROUE 30. //en mm
#define GRANDEUR_EMPATEMENT 50. //en mm
#define GRANDEUR_VITESSE_MAX 324.86 //en tr/min 
#define PI_ 3.14159265



//TANGAGE
extern short tAccX0 , tAccX1, tAccZ0, tAccZ1, tGyro0, tGyro1;
void enregistrerTangage(void);
void chargerTangage(void);

//ASSERVISSEMENT
extern float PRINC_PID_K;
extern float PRINC_PID_D;
extern float PRINC_DIR;
extern float COEF_KALMAN; 
extern float ACCELERATION_COEF_FILTRE;
void chargerAsservissement(void);
void enregistrerAsservissement(void);

//GUIDON
extern short tGuidon0 , tGuidonMax;
extern float GUIDONMAX; // tguidonmax : de combien, en valeur can, le guidon peut il bouger?//guidonMax : lorsque le guidon est au max, ca correspond a combien de tour/min
void chargerGuidon(void);
void enregistrerGuidon(void);

//pas encore enregistré ds l'eeprom

//DEMARRAGE
extern float LIMITE_DISTANCE_UTILISATEUR; //mm : 
extern float DEMARRAGE_TOL_ANGLE; //2 en °
extern float DEMARRAGE_TOL_GUIDON; //5 en tr/min sur soi meme
extern float DEMARRAGE_DELAI_EQUILIBRE; //2000 en ms
void enregistrerDemarrage(void);
void chargerDemarrage(void);

//VITESSE
extern float VITESSE_TROITTOIR_MAX; //km/h
extern float POURCENT_SECURITE_MOTEUR; //a partir de quand activer le freinage de sécurité
extern float COEF_HYSTERISIS_SECURITE; //la variable de réglage de l'hystérisis
void enregistrerVitesse(void);
void chargerVitesse(void);

//variables mises à jour par l'uart : valent 0 par défaut
extern float inf_coupleG, inf_coupleD;
extern char inf_etatCouple, inf_demandeOnOff;
extern char verboseMode;


#endif


