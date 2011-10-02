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

const char start=B11010;
const char data1=B001;
const char data2=B010;
const char data3=B011;
const char ordre=B1;
const char info=B0;
const char angle=19;
const char vitesse_angulaire=30;
const char acceleration=20;
short ti=0;
char debut;
char octettype;
char donnee0;
char donnee1;

char rs;

char checksum(char char1, char char2);

void setup() {
  Serial.begin(9600);
  ti=0;
  lcd.begin(16,2); // Initialise le LCD avec 20 colonnes x 4 lignes 
  delay(10); // pause rapide pour laisser temps initialisation
}

void loop() {
  switch(ti)
    {
    case 0:
    debut= start << 3;
    debut= debut | data2;
    octettype= angle;
    donnee0=random(0,128);
    donnee1=random(0,256);
    Serial.print(debut);
    Serial.print(octettype);
    Serial.print(donnee0);
    Serial.print(donnee1);
    Serial.print(checksum(octettype, checksum(donnee0,donnee1)));
    break;
    
    case 1:
    debut= start << 3;
    debut= debut | data2;
    octettype= vitesse_angulaire;
    donnee0=random(0,256);
    donnee1=random(0,256);
    Serial.print(debut);
    Serial.print(octettype);
    Serial.print(donnee0);
    Serial.print(donnee1);
    Serial.print(checksum(octettype, checksum(donnee0,donnee1)));
    break;
    
    case 2:
    debut= start << 3;
    debut= debut | data2;
    octettype= acceleration;
    donnee0=0;
    donnee1=random(0,128);
    Serial.print(debut);
    Serial.print(octettype);
    Serial.print(donnee0);
    Serial.print(donnee1);
    Serial.print(checksum(octettype, checksum(donnee0,donnee1)));
    break;
    }
  ti++;
  if(ti>=3){ti=0;}
  
  if (Serial.available() > 0)
{ 
  rs=Serial.read();
  {
    lcd.setCursor(0,1);
    lcd.print(rs,HEX);
  }
  delay(300);
}

}

char checksum(char char1, char char2)
{
  return char1^char2;
}



