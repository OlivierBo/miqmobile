
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
{
   u.fval = myVelocity;
  
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
  
   Serial.println();
  
  
  delay(2000); // allow some time for the Serial data to be sent
}

