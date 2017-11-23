#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 5

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

#define rede "SSID"
#define senha "PASSWORD"
#define server "YOUR-IP"
#define PORT 80

SoftwareSerial esp8266(9, 10);

#define DEBUG true

void conectaresp(){

  while(esp8266.available()){
    Serial.write(esp8266.read());
  }
  String comando="AT+CWJAP=\"";
  comando+=rede;
  comando+="\",\"";
  comando+=senha;  
  comando+="\"\r\n";
  esp8266.println(comando);
  delay(8000);
  while(esp8266.available()){
    Serial.write(esp8266.read());
  }
}

void connectserver(){
  String comando = "AT+CIPSTART=\"TCP\",\"";
  comando += server;
  comando += "\",";
  comando += PORT;
  comando += "";
  esp8266.println(comando);
  delay(500);
}

void disconnectserver(){
  String comando = "AT+CIPCLOSE";
  esp8266.println(comando);
}


void senddata(float umid, float temp){

  // monta o payload
  String payload = "{\"temperatura\": \"";
  payload += temp;
  payload += "\", \"umidade\": \"";
  payload += umid;
  payload += "\"}\r\n\r\n";

  //monta o comando do post
  String comando="POST /arduino/ HTTP/1.0\r\n";
  comando += "Host: \"";
  comando += server;
  comando += "\"\r\n";
  comando += "Content-Type: application/json\r\n";
  comando += "Content-Length: ";
  comando += payload.length();
  comando += "\r\n\r\n";
  comando += payload;

  String sendheader = "AT+CIPSEND=";
  sendheader += comando.length();

  connectserver();
  delay(1000);
  esp8266.println(sendheader);
  delay(2000);
  esp8266.println(comando);
  Serial.println(comando);
  delay(1000);
  disconnectserver();
  delay(1000);

}


void setup() {
  // initialize the LED pin as an output:
  Serial.begin(115200);
  delay(3000);
  esp8266.begin(115200);
  delay(3000);
  esp8266.println("AT+RST");
  delay(3000);
  Serial.println("Conectando");
  conectaresp();
}

void loop() {
  float u = dht.readHumidity(); //Le o valor da umidade
  float t = dht.readTemperature(); //Le o valor da temperatura]]

  senddata(u, t);
  
}