/** \file 
Contient:\n
-la définition de constantes (rayon des roues, empatement...)\n
-les variables globales (pour etre accessibles de l'usart et par les interruptions)\n
-des buffer d'ordres recus (par la carte couple ou xbee)
\author    Adrien Jaegy
 */
#ifndef GLOBAL_H
#define GLOBAL_H



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
extern short tGuidon0;
///de combien, en valeur can, le guidon peut il bouger?
extern short tGuidonMax;
void chargerGuidon(void);
void enregistrerGuidon(void);

//pas encore enregistré ds l'eeprom

//DEMARRAGE
///en mm
extern float LIMITE_DISTANCE_UTILISATEUR;
///en ° (vaut 2 approximativement)
extern float DEMARRAGE_TOL_ANGLE;
///en tr/min sur soi meme
extern float DEMARRAGE_TOL_GUIDON; 
///en ms
extern float DEMARRAGE_DELAI_EQUILIBRE; 
///lorsque le guidon est au max, ca correspond a combien de tour/min?
extern float GUIDONMAX; 
void enregistrerDemarrage(void);
void chargerDemarrage(void);

//VITESSE
///km/h
extern float VITESSE_TROITTOIR_MAX; 
///a partir de quand activer le freinage de sécurité
extern float POURCENT_SECURITE_MOTEUR; 
///la variable de réglage de l'hystérisis de consigne d'angle
extern float COEF_HYSTERISIS_SECURITE; 
void enregistrerVitesse(void);
void chargerVitesse(void);



//variables mises à jour par l'uart : valent 0 par défaut

/*!
Valeur réelle du couple (envoyé par la carte couple).
*/
extern float inf_coupleG;

/*!
Valeur réelle du couple (envoyé par la carte couple).
*/
extern float inf_coupleD;

/*!
Etat de la carte asservissement en couple : \n
0 : on ne sait pas encore (valeur au démarrage)\n
1 : c'est bon, tout va bien (valeur lorsque envoi trame carte moteur ok)\n
2 : pb gauche (ex : le moteur ne se met pas a tourner -> calbe alim débranché)\n
4 : pb droit\n
6 : pb gauche et droit\n
8 : a décidé de s'arreter (pourquoi pas...)\n
>=16: autre réponse / pb : peut envoyer ca au démarrage lorsqu'en mode debug par exemple\n
*/
extern char inf_etatCouple;

/*!
Demande de marche ou d'arret de la M2 provenant soit de l'interface HM, soit de l'usart.\n
0=off \n
1=on_normal \n
2=on_forcé \n
4=on_test (sans envoi aux moteurs) \n
8=demande d'arret \n
*/
extern char inf_demandeOnOff;

/*!
Chaque bit code pour l'activation d'un envoi en particulier\n
Extrait du code source utilisant cette variables : \n	
if(getbit(verboseMode,1)) envoiTrameUart1(TYPE_TRAME_INF_ETAT,(void*)(&inf_demandeOnOff),LG_TRAME_INF_ETAT);\n
if(getbit(verboseMode,2)) envoiTrameUart1(TYPE_TRAME_INF_ETAT_BATTERIE,(void*)(&tBatterie),LG_TRAME_INF_ETAT_BATTERIE);\n
if(getbit(verboseMode,3)) envoiTrameUart1(TYPE_TRAME_INF_ANGLE_HORS_INTERVALLE,(void*)(&tangage.defautBorne),LG_TRAME_INF_ANGLE_HORS_INTERVALLE);\n
if(getbit(verboseMode,4)) envoiTrameUart1(TYPE_TRAME_INF_ANGLE_TANGAGE,(void*)(&tangage.teta),LG_TRAME_INF_ANGLE_TANGAGE);\n
if(getbit(verboseMode,5)) envoiTrameUart1(TYPE_TRAME_INF_VITESSE_ANGULAIRE,(void*)(&tangage.vitesse),LG_TRAME_INF_VITESSE_ANGULAIRE);\n
if(getbit(verboseMode,6)) envoiTrameUart1(TYPE_TRAME_INF_VITESSED,(void*)(&roues.vitesseDroite),LG_TRAME_INF_VITESSED);\n
if(getbit(verboseMode,7)) envoiTrameUart1(TYPE_TRAME_INF_VITESSEG,(void*)(&roues.vitesseGauche),LG_TRAME_INF_VITESSEG);\n
if(getbit(verboseMode,8)) envoiTrameUart1(TYPE_TRAME_INF_DISTANCE_PARCOURUE,(void*)(&roues.distanceMoyenneParcourue),LG_TRAME_INF_DISTANCE_PARCOURUE);\n
if(getbit(verboseMode,9)) envoiTrameUart1(TYPE_TRAME_INF_ACCELERATION,(void*)(&roues.accMoyenne),LG_TRAME_INF_ACCELERATION);\n
if(getbit(verboseMode,10)) envoiTrameUart1(TYPE_TRAME_INF_COUPLED,(void*)(&inf_coupleD),LG_TRAME_INF_COUPLED);\n
if(getbit(verboseMode,11)) envoiTrameUart1(TYPE_TRAME_INF_COUPLEG,(void*)(&inf_coupleG),LG_TRAME_INF_COUPLEG);\n
*/
extern short verboseMode;


#endif


