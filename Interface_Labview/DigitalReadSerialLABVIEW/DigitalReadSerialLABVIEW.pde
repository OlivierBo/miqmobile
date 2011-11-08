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

const char start=B1110010;
const char coupleg=10;
const char coupled=11;
const char vitesseg=13;
const char concoupleg=138;
const char concoupled=139;
short ti=0;
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
    donnee0=random(0,128);
    Serial.print(start);
    Serial.print(coupleg);
    Serial.print(donnee0);
    Serial.print(donnee0);
    Serial.print(checksum(start, checksum(coupleg,checksum(donnee0,donnee0))));
    break;
    
    case 1:
    donnee0=random(0,256);
    Serial.print(start);
    Serial.print(coupled);
    Serial.print(donnee0);
    Serial.print(donnee0);
    Serial.print(checksum(start, checksum(coupled,checksum(donnee0,donnee0))));
    break;
    
    }
  ti++;
  if(ti>=2){ti=0;}
  delay(300);
  
  if (Serial.available() > 0)
{ 
  rs=Serial.read();
  {
    if(rs=start)
      {
     // typeRecu=Serial.read();
    /*  switch(typeRecu)
        case coupleg :
        break;
        
        case coupled :
        break;
        */
      }
    lcd.setCursor(0,1);
    lcd.print(rs,HEX);
  }
}

}

char checksum(char char1, char char2)
{
  return char1^char2;
}



