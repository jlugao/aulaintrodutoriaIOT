#include <DHT.h>

#define DHTPIN 5

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600);

}

void loop() {
  float h = dht.readHumidity(); //Le o valor da umidade
  float t = dht.readTemperature(); //Le o valor da temperatura
  Serial.print("Temp: ");
  Serial.print(t);
  Serial.println(" Degrees C");
  Serial.print("Humid: ");
  Serial.print(h);
  Serial.println("");
  Serial.println("--------------------");
  delay(1000);
  

}