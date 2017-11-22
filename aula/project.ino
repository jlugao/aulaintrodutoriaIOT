#include <SoftwareSerial.h>
#include <DHT.h>

#define DHTPIN 5

#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

#define rede "casa n"
#define senha "26071989"
#define server "192.168.0.106"
#define PORT 5000

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 7;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

SoftwareSerial esp8266(9, 10);

#define DEBUG true

void conectaresp(){
  String comando="AT+CWJAP=\"";
  comando+=rede;
  comando+="\",\"";
  comando+=senha;  
  comando+="\"\r\n";
  esp8266.println(comando);
  delay(5000);
}

void connectserver(){
  String comando = "AT+CIPSTART=\"TCP\",\"";
  comando += server;
  comando += "\",";
  comando += PORT;
  comando += "";
  esp8266.println(comando);
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
  String comando="POST /home HTTP/1.0\r\n";
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
  delay(500);
  esp8266.println(sendheader);
  delay(500);
  esp8266.println(comando);
  Serial.println(comando);
  delay(500);
  disconnectserver();
  delay(500);

}



void setup() {
  // initialize the LED pin as an output:
  Serial.begin(115200);
  delay(3000);
  esp8266.begin(115200);
  delay(3000);
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.println("Conectando");
  conectaresp();
}

void loop() {
  float u = dht.readHumidity(); //Le o valor da umidade
  float t = dht.readTemperature(); //Le o valor da temperatura]]

  senddata(u, t);

  if(esp8266.available()){
    Serial.write(esp8266.read());
  }
  
}