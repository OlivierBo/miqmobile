/*
Envoie et réception de trame série projet M2
 */


// Connexion du LCD sur les broches de la carte Arduino 
// Connecter broche RS du LCD sur la broche 2
// Connecter broche E du LCD sur la broche 3
// Connecter broche D4 du LCD sur la broche 4
// Connecter broche D5 du LCD sur la broche 5
// Connecter broche D6 du LCD sur la broche 6
// Connecter broche D7 du LCD sur la broche 7

// --- Inclusion des librairies utilisées ---
#include <LiquidCrystal.h> // Inclusion de la librairie pour afficheur LCD

// --- constantes des broches ---

const int RS=2; //declaration constante de broche 
const int E=3; //declaration constante de broche 

const int D4=4; //declaration constante de broche 
const int D5=5; //declaration constante de broche 
const int D6=6; //declaration constante de broche 
const int D7=7; //declaration constante de broche


// --- Initialisation des fonctionnalités utilisées ---
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);// initialisation LCD en mode 4 bits 



// Octet de type
#define LG_TRAME_CON_COUPLEG 2
#define LG_TRAME_CON_COUPLED 2
#define LG_TRAME_INF_COUPLEG 2
#define LG_TRAME_INF_COUPLED 2
#define LG_TRAME_INF_ERREUR_CARTE_COURANT 1

#define LG_TRAME_INF_VITESSEG 4
#define LG_TRAME_INF_VITESSED 4
#define LG_TRAME_INF_PRINC_PID_K 4
#define LG_TRAME_CON_PRINC_PID_K 4
#define LG_TRAME_INF_PRINC_PID_I 4
#define LG_TRAME_CON_PRINC_PID_I 4
#define LG_TRAME_INF_PRINC_PID_D 4
#define LG_TRAME_CON_PRINC_PID_D 4
#define LG_TRAME_INF_PRINC_DIR 4
#define LG_TRAME_CON_PRINC_DIR 4
#define LG_TRAME_INF_ANGLE 4
#define LG_TRAME_INF_VITESSE_ANGULAIRE 4
#define LG_TRAME_INF_ACCELERATION 4
#define LG_TRAME_CON_ACCELERATION_COEF_FILTRE 4
#define LG_TRAME_INF_COEF_KALMAN 4
#define LG_TRAME_CON_COEF_KALMAN 4
#define LG_TRAME_CON_SAUVEGARDER_COEF 4
#define LG_TRAME_INF_DISTANCE_PARCOURUE 4
#define LG_TRAME_INF_ETAT_BATTERIE 4

#define LG_TRAME_CON_STOP 0
#define LG_TRAME_CON_DEPART 0
#define LG_TRAME_INF_PRET 1
#define LG_TRAME_INF_ETAT 1
#define LG_TRAME_CON_TEST_COM 2
#define LG_TRAME_INF_SATURATION_VITESSE 2
#define LG_TRAME_CON_SATURATION_VITESSE 2
#define LG_TRAME_INF_ANGLE_HORS_INTERVALLE 1
#define LG_TRAME_CON_RECHARGER_COEF 1


#define TYPE_TRAME_CON_COUPLEG 138
#define TYPE_TRAME_CON_COUPLED 139
#define TYPE_TRAME_INF_COUPLEG 10
#define TYPE_TRAME_INF_COUPLED 11
#define TYPE_TRAME_INF_ERREUR_CARTE_COURANT 12

#define TYPE_TRAME_INF_VITESSEG 13
#define TYPE_TRAME_INF_VITESSED 14
#define TYPE_TRAME_INF_PRINC_PID_K 15
#define TYPE_TRAME_CON_PRINC_PID_K 143
#define TYPE_TRAME_INF_PRINC_PID_I 16
#define TYPE_TRAME_CON_PRINC_PID_I 144
#define TYPE_TRAME_INF_PRINC_PID_D 17
#define TYPE_TRAME_CON_PRINC_PID_D 145
#define TYPE_TRAME_INF_PRINC_DIR 18
#define TYPE_TRAME_CON_PRINC_DIR 146
#define TYPE_TRAME_INF_ANGLE 19
#define TYPE_TRAME_INF_VITESSE_ANGULAIRE 30
#define TYPE_TRAME_INF_ACCELERATION 20
#define TYPE_TRAME_CON_ACCELERATION_COEF_FILTRE 148
#define TYPE_TRAME_INF_COEF_KALMAN 21
#define TYPE_TRAME_CON_COEF_KALMAN 149
#define TYPE_TRAME_CON_SAUVEGARDER_COEF 150
#define TYPE_TRAME_INF_DISTANCE_PARCOURUE 23
#define TYPE_TRAME_INF_ETAT_BATTERIE 24

#define TYPE_TRAME_CON_STOP 153
#define TYPE_TRAME_CON_DEPART 154
#define TYPE_TRAME_INF_PRET 25
#define TYPE_TRAME_INF_ETAT 26
#define TYPE_TRAME_CON_TEST_COM 155
#define TYPE_TRAME_INF_SATURATION_VITESSE 28
#define TYPE_TRAME_CON_SATURATION_VITESSE 156
#define TYPE_TRAME_INF_ANGLE_HORS_INTERVALLE 29
#define TYPE_TRAME_CON_RECHARGER_COEF 159

// Octet de START
#define DEBUT_TRAME B01110010


// Données à envoyer
int coupleg;
int coupled;
char erreurcourant;
float vitesseg=0.0;
float vitessed=0.0;
float pidK=0.0;
float pidI=0.0;
float pidD=0.0;
float coefDIR=0.0;
float angle=0.0;
float vitesseangulaire=0.0;
float acceleration=0.0;
float coefKalman=0.0;
float distance=0.0;
float batterie=0.0;
char pret;
char etat;
int testcom;
int saturationvitesse;
char anglehorsintervalle;


// Variables pointeur


// Variables checksum
char checksum;

// Autres variables
int ti=0;

// Declaration fonctions
char fchecksum(char char1, char char2);

void setup() {
  Serial.begin(9600);
  ti=0;
  lcd.begin(16,2); // Initialise le LCD avec 20 colonnes x 4 lignes 
  delay(10); // pause rapide pour laisser temps initialisation
}

void loop() {
  
  // Envoie BIN de start
  Serial.println(DEBUT_TRAME, BIN);
  checksum=DEBUT_TRAME;
  
  // Envoie BIN de type et données successivement
  switch(ti)
    {
    case 0:
    Serial.println(TYPE_TRAME_INF_COUPLEG, BIN);
    checksum=fchecksum(checksum,TYPE_TRAME_INF_COUPLEG);
    coupleg=50;
    checksum=sendData(2, (char*) &coupleg ,checksum);
    break;
    
    case 1:
    Serial.println(TYPE_TRAME_INF_COUPLED, BIN);
    checksum=fchecksum(checksum,TYPE_TRAME_INF_COUPLED);
    coupled=850;
    checksum=sendData(2, (char*) &coupled ,checksum);
    break;
    
    case 2:
    Serial.println(TYPE_TRAME_INF_VITESSEG, BIN);
    checksum=fchecksum(checksum,TYPE_TRAME_INF_VITESSEG);
    vitesseg=25.63;
    char* po = (char*) &vitesseg;
    for (int i = 0; i < 4; i++) {
    Serial.println(po[i], BIN);
    }
    checksum=sendData(4, (char*) &vitesseg ,checksum);
    break;
    
    
    }
    
  // Envoie checksum
  Serial.println(checksum,BIN);  
  
  
  ti++;
  if(ti>=3){ti=0;}
  delay(1000);
  
}

char fchecksum(char char1, char char2)
{
  return char1^char2;
}

char sendData(int longueur, char * pointeur, char checksum)
{

  for (int i = 0; i < longueur; i++) {
  Serial.println((char) pointeur[i], BIN);
  checksum=fchecksum(checksum,pointeur[i]);
  }

return checksum;
}


