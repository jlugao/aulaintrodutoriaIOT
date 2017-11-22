#include <SoftwareSerial.h>

SoftwareSerial esp8266(9, 10); //Rx, Tx;

#define DEBUG true

void setup() {
  // initialize the LED pin as an output:
  Serial.begin(9600);
  delay(3000);

  esp8266.begin(115200); // uses \r \n as terminators
  delay(3000);
}

void loop() {

  if(esp8266.available()){
    Serial.write(esp8266.read());
  }
  
  if(Serial.available()){
    esp8266.write(Serial.read());
  }
  
}