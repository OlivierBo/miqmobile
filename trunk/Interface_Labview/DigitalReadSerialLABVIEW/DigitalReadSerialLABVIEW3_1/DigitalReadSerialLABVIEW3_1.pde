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

#define TYPE_TRAME_CON_TEST_COM 129
#define TYPE_TRAME_CON_DEPART 130
#define TYPE_TRAME_CON_STOP 131
#define TYPE_TRAME_INF_ETAT 1
#define TYPE_TRAME_INF_ETAT_BATTERIE 4
#define TYPE_TRAME_INF_ANGLE_HORS_INTERVALLE 5
#define TYPE_TRAME_INF_ANGLE_TANGAGE 6
#define TYPE_TRAME_INF_VITESSE_ANGULAIRE 7
#define TYPE_TRAME_INF_VERBOSE 8
#define TYPE_TRAME_CON_VERBOSE 136
#define TYPE_TRAME_INF_VITESSED 12
#define TYPE_TRAME_INF_VITESSEG 13
#define TYPE_TRAME_INF_DISTANCE_PARCOURUE 14
#define TYPE_TRAME_INF_ACCELERATION 15
#define TYPE_TRAME_CON_CHARGER_VITESSE 144
#define TYPE_TRAME_CON_ENREGISTRER_VITESSE 145
#define TYPE_TRAME_CON_CHARGER_ASSERVISSEMENT 146
#define TYPE_TRAME_CON_ENREGISTRER_ASSERVISSEMENT 147
#define TYPE_TRAME_CON_CHARGER_DEMARRAGE 148
#define TYPE_TRAME_CON_ENREGISTRER_DEMARRAGE 149
#define TYPE_TRAME_CON_PRINC_PID_K 150
#define TYPE_TRAME_CON_PRINC_PID_D 151
#define TYPE_TRAME_CON_PRINC_DIR 152
#define TYPE_TRAME_CON_COEF_KALMAN 153
#define TYPE_TRAME_CON_ACCELERATION_COEF_FILTRE 154
#define TYPE_TRAME_CON_GUIDONMAX 155
#define TYPE_TRAME_CON_LIMITE_DISTANCE_UTILISATEUR 156
#define TYPE_TRAME_CON_DEMARRAGE_TOL_ANGLE 157
#define TYPE_TRAME_CON_DEMARRAGE_TOL_GUIDON 158
#define TYPE_TRAME_CON_DEMARRAGE_DELAI_EQUILIBRE 159
#define TYPE_TRAME_CON_VITESSE_TROITTOIR_MAX 160
#define TYPE_TRAME_CON_POURCENT_SECURITE_MOTEUR 161
#define TYPE_TRAME_CON_COEF_HYSTERISIS_SECURITE 162
#define TYPE_TRAME_INF_PRINC_PID_K 22
#define TYPE_TRAME_INF_PRINC_PID_D 23
#define TYPE_TRAME_INF_PRINC_DIR 24
#define TYPE_TRAME_INF_COEF_KALMAN 25
#define TYPE_TRAME_INF_ACCELERATION_COEF_FILTRE 26
#define TYPE_TRAME_INF_GUIDONMAX 27
#define TYPE_TRAME_INF_LIMITE_DISTANCE_UTILISATEUR 28
#define TYPE_TRAME_INF_DEMARRAGE_TOL_ANGLE 29
#define TYPE_TRAME_INF_DEMARRAGE_TOL_GUIDON 30
#define TYPE_TRAME_INF_DEMARRAGE_DELAI_EQUILIBRE 31
#define TYPE_TRAME_INF_VITESSE_TROITTOIR_MAX 32
#define TYPE_TRAME_INF_POURCENT_SECURITE_MOTEUR 33
#define TYPE_TRAME_INF_COEF_HYSTERISIS_SECURITE 34
#define TYPE_TRAME_CON_COEF_COURANT_1 163
#define TYPE_TRAME_INF_COEF_COURANT_1 35
#define TYPE_TRAME_CON_COEF_COURANT_2 164
#define TYPE_TRAME_INF_COEF_COURANT_2 36
#define TYPE_TRAME_CON_COUPLED 178
#define TYPE_TRAME_INF_COUPLED 50
#define TYPE_TRAME_CON_COUPLEG 179
#define TYPE_TRAME_INF_COUPLEG 51
#define TYPE_TRAME_INF_ERREUR_CARTE_COURANT 52
#define TYPE_TRAME_INF_PRET 53
#define TYPE_TRAME_CON_DEMANDE_COEFFICIENTS 137

#define LG_TRAME_CON_TEST_COM 4
#define LG_TRAME_CON_DEPART 0
#define LG_TRAME_CON_STOP 0
#define LG_TRAME_INF_ETAT 1
#define LG_TRAME_INF_ETAT_BATTERIE 4
#define LG_TRAME_INF_ANGLE_HORS_INTERVALLE 1
#define LG_TRAME_INF_ANGLE_TANGAGE 4
#define LG_TRAME_INF_VITESSE_ANGULAIRE 4
#define LG_TRAME_INF_VERBOSE 2
#define LG_TRAME_CON_VERBOSE 2
#define LG_TRAME_INF_VITESSED 4
#define LG_TRAME_INF_VITESSEG 4
#define LG_TRAME_INF_DISTANCE_PARCOURUE 4
#define LG_TRAME_INF_ACCELERATION 4
#define LG_TRAME_CON_CHARGER_VITESSE 0
#define LG_TRAME_CON_ENREGISTRER_VITESSE 0
#define LG_TRAME_CON_CHARGER_ASSERVISSEMENT 0
#define LG_TRAME_CON_ENREGISTRER_ASSERVISSEMENT 0
#define LG_TRAME_CON_CHARGER_DEMARRAGE 0
#define LG_TRAME_CON_ENREGISTRER_DEMARRAGE 0
#define LG_TRAME_CON_PRINC_PID_K 4
#define LG_TRAME_CON_PRINC_PID_D 4
#define LG_TRAME_CON_PRINC_DIR 4
#define LG_TRAME_CON_COEF_KALMAN 4
#define LG_TRAME_CON_ACCELERATION_COEF_FILTRE 4
#define LG_TRAME_CON_GUIDONMAX 4
#define LG_TRAME_CON_LIMITE_DISTANCE_UTILISATEUR 4
#define LG_TRAME_CON_DEMARRAGE_TOL_ANGLE 4
#define LG_TRAME_CON_DEMARRAGE_TOL_GUIDON 4
#define LG_TRAME_CON_DEMARRAGE_DELAI_EQUILIBRE 4
#define LG_TRAME_CON_VITESSE_TROITTOIR_MAX 4
#define LG_TRAME_CON_POURCENT_SECURITE_MOTEUR 4
#define LG_TRAME_CON_COEF_HYSTERISIS_SECURITE 4
#define LG_TRAME_INF_PRINC_PID_K 4
#define LG_TRAME_INF_PRINC_PID_D 4
#define LG_TRAME_INF_PRINC_DIR 4
#define LG_TRAME_INF_COEF_KALMAN 4
#define LG_TRAME_INF_ACCELERATION_COEF_FILTRE 4
#define LG_TRAME_INF_GUIDONMAX 4
#define LG_TRAME_INF_LIMITE_DISTANCE_UTILISATEUR 4
#define LG_TRAME_INF_DEMARRAGE_TOL_ANGLE 4
#define LG_TRAME_INF_DEMARRAGE_TOL_GUIDON 4
#define LG_TRAME_INF_DEMARRAGE_DELAI_EQUILIBRE 4
#define LG_TRAME_INF_VITESSE_TROITTOIR_MAX 4
#define LG_TRAME_INF_POURCENT_SECURITE_MOTEUR 4
#define LG_TRAME_INF_COEF_HYSTERISIS_SECURITE 4
#define LG_TRAME_CON_COEF_COURANT_1 4
#define LG_TRAME_INF_COEF_COURANT_1 4
#define LG_TRAME_CON_COEF_COURANT_2 4
#define LG_TRAME_INF_COEF_COURANT_2 4
#define LG_TRAME_CON_COUPLED 4
#define LG_TRAME_INF_COUPLED 4
#define LG_TRAME_CON_COUPLEG 4
#define LG_TRAME_INF_COUPLEG 4
#define LG_TRAME_INF_ERREUR_CARTE_COURANT 1
#define LG_TRAME_INF_PRET 0
#define LG_TRAME_CON_DEMANDE_COEFFICIENTS 0


#define DEBUT_TRAME 114
#define TRAME_ERR_NOERR 0
#define TRAME_ERR_TYPE 1
#define TRAME_ERR_CHECK 2
#define TRAME_ERR_DEBUT 3


// Octet de START
#define DEBUT_TRAME B01110010


// Données à envoyer
float coupleg=(float)(random(400,500))*0.1;
float coupled=(float)(random(300,400))*0.1;
char erreurcourant;
float vitesseg=(float)(random(600,700))*0.1;
float vitessed=(float)(random(300,400))*0.1;
float pidK=0.8;
float pidI=1.5;
float pidD=2.0;
float coefDIR=15.3;
float angle=(float)(random(300,400))*0.1;
float vitesseangulaire=0.0;
float acceleration=0.5;
float coefKalman=2504.1;
float coefacc=0.0;
float distance=(float)(random(30,40))*0.1;
float batterie=(float)(random(200,240))*0.1;
char pret;
char etat;
int testcom;
int saturationvitesse;
char anglehorsintervalle;

byte bytereception0;
byte bytereception1;
byte bytereception2;




// Variables checksum
char checksum;

// Autres variables
int ti=0;
int d;
boolean floatn=false; // On demande une valeur de type float
float tempf;
// Declaration fonctions

void sendData(char typeData, float data);
char fchecksum(char char1, char char2);
float receiver();

   union u_tag {
    byte b[4];
    float fval;
  } u;

void setup() {
  Serial.begin(9600);
  ti=0;
  lcd.begin(16,2); // Initialise le LCD avec 20 colonnes x 4 lignes 
  delay(10); // pause rapide pour laisser temps initialisation
}



void loop() {
  
  // Temps boucle
  //delay(200);
  
  //Ecoute et decode si start
  /*
  if (Serial.available() > 0) { // si des données entrantes sont présentes
                lcd.setCursor(0, 0);
		// lit le 1er octet arrivé
		bytereception0 = Serial.read();

          if(bytereception0==DEBUT_TRAME){
            lcd.print("S1");
            bytereception1 = Serial.read(); //Octet de type
            lcd.setCursor(4, 0);
            switch (bytereception1){
              case TYPE_TRAME_CON_COUPLEG:
              lcd.print("CTORQUE G");
              break;
              
              case TYPE_TRAME_CON_COUPLED:
              lcd.print("CTORQUE D");
              break;
              
              case TYPE_TRAME_INF_PRINC_PID_K:
              tempf=receiver();
              sendData(TYPE_TRAME_INF_PRINC_PID_K, pidK);
              lcd.print("IPID K");
              break;
              
              case TYPE_TRAME_CON_PRINC_PID_K:
              pidK=receiver();
              lcd.print("CPID K");
              break;
              

 
              
              case TYPE_TRAME_INF_PRINC_PID_D:
              tempf=receiver();
              sendData(TYPE_TRAME_INF_PRINC_PID_D, pidD);
              lcd.print("IPID D");
              break;
              
              case TYPE_TRAME_CON_PRINC_PID_D:
              pidD=receiver();
              lcd.print("CPID D");
              break;
              
              case TYPE_TRAME_INF_PRINC_DIR:
              tempf=receiver();
              sendData(TYPE_TRAME_INF_PRINC_DIR, coefDIR);
              lcd.print("IP DIR");
              break;
              
              case TYPE_TRAME_CON_PRINC_DIR:
              coefDIR=receiver();
              lcd.print("CP DIR");
              break;
              
              case TYPE_TRAME_CON_ACCELERATION_COEF_FILTRE:
              coefacc=receiver();
              lcd.print("CACC COEF");
              break;
              
              case TYPE_TRAME_INF_COEF_KALMAN:
              tempf=receiver();
              sendData(TYPE_TRAME_INF_COEF_KALMAN, coefKalman);
              lcd.print("ICOEFKALMAN");
              break;
              
              case TYPE_TRAME_CON_COEF_KALMAN:
              coefKalman=receiver();
              lcd.print("CCOEFKALMAN");
              break;
            }
            
            
           
            // Reception checksum
            bytereception2=Serial.read();
            
            delay(10);
            
            
          }
          else{
            lcd.setCursor(4, 0);
            lcd.print("S0");
          }
          
            
  }*/
  
    // Boucle d'envois synchrones
    // Selection de la donnée à envoyer    
   switch(ti)
    {
    case 0:
    coupleg=coupleg + 2*((float)(random(1,9))-(float)(random(1,9)))/5.0;
    sendData(TYPE_TRAME_INF_COUPLEG, coupleg);
    break;
    
    case 1:
    coupled=coupled + 2*((float)(random(1,9))-(float)(random(1,9)))/5.0;
    sendData(TYPE_TRAME_INF_COUPLED ,coupled);
    break;
    
    
    case 2:
    vitesseg=vitesseg + 2*((float)(random(1,9))-(float)(random(1,9)))/5.0;
    sendData( TYPE_TRAME_INF_VITESSEG,vitesseg);
    break;
    
    
    case 3:
    vitessed=vitessed + 2*((float)(random(1,9))-(float)(random(1,9)))/5.0;
    sendData( TYPE_TRAME_INF_VITESSED,vitessed);
    break;
    
    
    case 4:
    angle=angle + 2*((float)(random(1,9))-(float)(random(1,9)))/5.0;
    sendData( TYPE_TRAME_INF_ANGLE_TANGAGE, angle);
    break;
    
    
    case 5:
    distance=distance + 2*((float)(random(1,9))-(float)(random(1,9)))/5.0;
    sendData( TYPE_TRAME_INF_DISTANCE_PARCOURUE,distance);
    break;
    
    
    case 6:
    batterie=batterie + 2*((float)(random(1,9))-(float)(random(1,9)))/5.0;
    sendData(TYPE_TRAME_INF_ETAT_BATTERIE ,batterie);
    break;
    
    
    }
    if(ti<6){ti++;}else{ti=0;}
    
  
}
  
  // Fonction d'envoi des données floats
  void sendData(char typeData, float data){
    u.fval=data;
    // Envoi byte start
    Serial.print((char)DEBUT_TRAME);
    checksum=DEBUT_TRAME;
    Serial.print(typeData);
    checksum=fchecksum(checksum,typeData);
    Serial.print((char) u.b[0]);
    checksum=fchecksum(checksum,u.b[0]);
    Serial.print((char) u.b[1]);
    checksum=fchecksum(checksum, u.b[1]);
    Serial.print((char) u.b[2]);
    checksum=fchecksum(checksum,u.b[2]);
    Serial.print((char) u.b[3]);
    checksum=fchecksum(checksum,u.b[3]);
    Serial.print((char) checksum);   
    //delay(5);
  }
  
  // Reception de float
  float receiver(){
    
            u.b[0]=(byte)Serial.read();
            u.b[1]=(byte)Serial.read();
            u.b[2]=(byte)Serial.read();
            u.b[3]=(byte)Serial.read();
            lcd.setCursor(0, 1);
            lcd.print("D=");
            lcd.setCursor(2, 1);
            lcd.print(u.fval, DEC);
            lcd.setCursor(4, 0);
            return u.fval;
    
  }
  
  /*
  //Renvoi des données
            Serial.print((char) DEBUT_TRAME);
            Serial.print((char) bytereception1);
            Serial.print((char) u.b[0]);
            Serial.print((char) u.b[1]);
            Serial.print((char) u.b[2]);
            Serial.print((char) u.b[3]);
            Serial.print((char) bytereception2);
  */
  
  /*
  // Envoie BYTE de start
  Serial.print(DEBUT_TRAME,BYTE);
  checksum=DEBUT_TRAME;
  
  // Envoie BYTE de type et données successivement
  switch(ti)
    {
    case 0:
    Serial.print(TYPE_TRAME_INF_COUPLEG,BYTE);
    checksum=fchecksum(checksum,TYPE_TRAME_INF_COUPLEG);
    coupleg=random(40,50);
    checksum=sendData(2, (char*) &coupleg ,checksum);
    break;
    
    case 1:
    Serial.print(TYPE_TRAME_INF_COUPLED,BYTE);
    checksum=fchecksum(checksum,TYPE_TRAME_INF_COUPLED);
    coupled=random(800,900);
    checksum=sendData(2, (char*) &coupled ,checksum);
    break;
    }
    
  // Envoie checksum
  Serial.print(checksum,BYTE);  
  
  
  ti++;
  if(ti>=2){ti=0;}
  delay(300);
  */
  
  


char fchecksum(char char1, char char2)
{
  return char1^char2;
}

/*
char sendData(int longueur, char * pointeur, char checksum)
{

  for (int i = 0; i < longueur; i++) {
  Serial.print((char) pointeur[i],BYTE);
  checksum=fchecksum(checksum,pointeur[i]);
  }

return checksum;
}
*/


