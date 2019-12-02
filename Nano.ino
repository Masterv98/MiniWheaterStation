/* Este eh o programa do Arduino Nano
by V.G.E.R. */


//---Bibliotecas para comunicacao entre Nano e ESP32---// 
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
//----------------------------------------------------//

//--------Bibliotecas para DHT---------//
#include "DHT.h"
//------------------------------------//

//----------Definicao do DHT-----------//
#define DHTPIN 2     
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//------------------------------------//


 
void setup() {
  s.begin(115200);    /* Comunicacao Serial entre plataformas*/
  pinMode(A0,INPUT);  /* Pino para o DHT*/
  dht.begin();        /* Inicio de comunicacao com o DHT*/
  
}

//--------Preparativos para o JSON---------//
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
//----------------------------------------//



void loop() {
  
  //Le a umidade
  float u = dht.readHumidity();
  
  // Le a temperatura em Celsius
  float t = dht.readTemperature();

 
  // Calcula Sensasao termica
  float hic = dht.computeHeatIndex(t, u, false);
  //bmp.readAltitude(1013.25)); 

  //Le o sensor de chuva resistivo
  float pp = analogRead(A0);

/*
if (isnan(h) || isnan(t) || isnan(pa) || isnan(pp)) {       /* Caso algo estaja conectado errado, nenhum dado sera transmitido
    return;
  }
*/

  root["temp"] = t; //Temperadura
  root["u"] = u;   //Umidade
  root["hi"] = hic; //Sensacao termica

  root["pp"]= pp; //precipitacao
  
 
if(s.available()>0)
{
 root.printTo(s);
}

delay(15000);
}
