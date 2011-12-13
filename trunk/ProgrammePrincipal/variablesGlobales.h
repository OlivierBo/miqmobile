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
void chargerGuidon(void);
void enregistrerGuidon(void);

//pas encore enregistré ds l'eeprom

//DEMARRAGE
extern float LIMITE_DISTANCE_UTILISATEUR; //mm : 
extern float DEMARRAGE_TOL_ANGLE; //2 en °
extern float DEMARRAGE_TOL_GUIDON; //5 en tr/min sur soi meme
extern float DEMARRAGE_DELAI_EQUILIBRE; //2000 en ms
extern float GUIDONMAX; // tguidonmax : de combien, en valeur can, le guidon peut il bouger?//guidonMax : lorsque le guidon est au max, ca correspond a combien de tour/min
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
//inf_demandeOnOff
	//0=off
	//1=on_normal
	//2=on_forcé
	//4=on_test (sans envoi aux moteurs)
	//8=demande d'arret
//inf_etatCouple
	//0 : on ne sait pas encore (valeur au démarrage)
	//1 : c'est bon, tout va bien (valeur lorsque envoi trame carte moteur ok)
	//2 : pb gauche (ex : le moteur ne se met pas a tourner -> calbe alim débranché)
	//4 : pb droit
	//6 : pb gauche et droit
	//8 : a décidé de s'arreter (pourquoi pas...)
	//>=16: autre réponse / pb : peut envoyer ca au démarrage lorsqu'en mode debug par exemple
extern short verboseMode;
//verboseMode
	//chaque bit code pour l'activation d'un envoi en partuculier

#endif


