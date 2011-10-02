/*
Envoie et réception de trame série projet M2
 */

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

char checksum(char char1, char char2);

void setup() {
  Serial.begin(9600);
  ti=0;
}

void loop() {
  switch(ti)
    {
    case 0:
      debut= start << 3;
      debut= debut | data2;
      octettype= info << 7;
      octettype= octettype | B1000000;
      octettype= octettype | angle;
//        debut=B11010010;
//        octettype=B01010011;
        donnee0=5;
        donnee1=8;
    Serial.print(debut);
    Serial.print(octettype);
    Serial.print(donnee0);
    Serial.print(donnee1);
    Serial.print(checksum(octettype, checksum(donnee0,donnee1)));
    break;
    
    case 1:
    break;
    
    case 2:
    break;
    }
  ti++;
  if(ti>=3){ti=0;}
  delay(300);
}

char checksum(char char1, char char2)
{
  return char1^char2;
}



