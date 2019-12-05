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

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

//-------------BMP280----------------//
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)

//Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
//------------------------------------//
 
void setup() {

  s.begin(115200);    /* Comunicacao Serial entre plataformas*/
  pinMode(A0,INPUT);  /* Pino para o DHT*/
  dht.begin();        /* Inicio de comunicacao com o DHT*/


/* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  
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

  //Le o sensor de chuva resistivo
  float pa = bmp.readPressure();

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
  root["pa"]= pa; //pressao
  root["pp"]= pp; //precipitacao
  
 
if(s.available()>0)
{
 root.printTo(s);
}

delay(15000);
}
