
#include <LiquidCrystal.h>

const int RS=2; //declaration constante de broche 
const int E=3; //declaration constante de broche 

const int D4=4; //declaration constante de broche 
const int D5=5; //declaration constante de broche 
const int D6=6; //declaration constante de broche 
const int D7=7; //declaration constante de broche


// --- Initialisation des fonctionnalités utilisées ---
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);// initialisation LCD en mode 4 bits 

/*
void setup() {
  Serial.begin(9600);
  
}

void loop() {
  float t=25.63;
 // void* pointervoid=(void*) &t;
  char* pointer= NULL;
 // memcpy(pointer, &t,4);
  Serial.println((char)pointer[0], BIN);
  Serial.println((char)pointer[1], BIN);
  Serial.println((char)pointer[2], BIN);
  Serial.println((char)pointer[3], BIN);
  Serial.println();
  delay(2000);
}
*/
void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2); // Initialise le LCD avec 20 colonnes x 4 lignes 
  delay(10); // pause rapide pour laisser temps initialisation
  // prints title with ending line break
  Serial.println("Decomposition de 25.634");

  // wait for the long string to be sent
  delay(100);
}
  
    float myVelocity = 25.634;

  union u_tag {
    byte b[4];
    float fval;
  } u;


void loop()
{ if(Serial.available()>0){
  // u.fval = myVelocity;

    u.b[0]=111;
    u.b[1]=18;
    u.b[2]=-51; 
    u.b[3]=65;
  
  
   Serial.print("Byte 1: ");
   Serial.println(u.b[0] );
   Serial.println(u.b[0],BIN );

   Serial.print("Byte 2: ");
   Serial.println(u.b[1] );
   Serial.println(u.b[1],BIN );
  
   Serial.print("Byte 3: ");
   Serial.println(u.b[2]);
   Serial.println(u.b[2],BIN );
  
   Serial.print("Byte 4: ");
   Serial.println(u.b[3] );
   Serial.println(u.b[3],BIN );
   
   Serial.print("Float: ");
   Serial.println(u.fval);
   lcd.print(u.fval, DEC);
   Serial.println();
}
  
  delay(2000); // allow some time for the Serial data to be sent
}

