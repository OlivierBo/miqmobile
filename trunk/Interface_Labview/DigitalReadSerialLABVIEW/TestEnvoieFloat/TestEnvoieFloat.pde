

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  float t=25.63;
  
  char* pointer= (char*) &t;
  Serial.println((char)pointer[0], BIN);
  Serial.println((char)pointer[1], BIN);
  Serial.println((char)pointer[2], BIN);
  Serial.println((char)pointer[3], BIN);
  Serial.println();
  delay(2000);
}

