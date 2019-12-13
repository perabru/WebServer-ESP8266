/*
 * Curso - Controle dispositivos remotamente com ESP8266
 * Por: Bruno Michel Pera
 * 
 * Web Server
 * Cria web server com ESP8266 hospedando página HTML
 */

#include <ESP8266WiFi.h>

const byte BT = D2;
const byte LED = D1;

boolean statusLED = LOW;

char ssid [] = "BRUNO";
char senha[] = "11235813";

WiFiServer server(80);

void setup() {
  pinMode(BT, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  delay(10);
  conectaWiFi(ssid,senha);
  server.begin();
  Serial.println("Servidor inicializado");
}

void loop() {

  WiFiClient client = server.available();
  if(!client){
    return;
  }

  while(!client.available()){
    delay(1);
  }

  String req =  client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  if(req.indexOf("LEDon") != -1){
      digitalWrite(LED, HIGH);
      statusLED = HIGH;
    } else if(req.indexOf("LEDoff") != -1 ){
        digitalWrite(LED, LOW);
        statusLED = LOW;
      }
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<meta http-equiv='refresh' content='2'>");
  client.println("<h1>Curso controle dispositivos remotamente com ESP8266</h1>");
  client.println("<h2>Ola Makers!</h2>");


  if(digitalRead(BT) == LOW){
    client.println("<p>BOTAO PRESSIONADO</p>");
  } else {
    client.println("<p>BOTAO SOLTO</p>");
    }


    if(!statusLED ){
        client.println("<p>LED <a href =\"LEDon\">, <button>LIGAR</button></a></p>");
        
      }else{
        client.println("<p>LED <a href =\"LEDoff\">, <button>DESLIGAR</button></a></p>");
        }
  client.println("</html>"); 
}


void conectaWiFi(char SSID[],char SENHA[]){

  Serial.print("Conectando a rede ");
  Serial.println(SSID);

  WiFi.begin(SSID,SENHA);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
}
