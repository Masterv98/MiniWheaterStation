/* Este eh o codigo para o ESP8266

by V.G.E.R.
*/


//----Inicializa o Serial e prepara o Json-----//
#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
#include <ArduinoJson.h>
//Inicializa Biblioteca para Thingspeak
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
//-------------------------------------------//



//----------- Defifinicao de Wi-Fi------------//
char ssid[] = "*X"; //SSID
char pass[] = "UJKNBK"; // Password
//-------------------------------------------//

WiFiClient  client;

//----------- Defifinicao de Canal------------//
unsigned long myChannelNumber = 345678; // Channel ID here
const char * myWriteAPIKey = "sedrtfgyuhjiok"; // Your Write API Key here
const int FieldTemp = 1;
const int FieldUmi = 2;
const int FieldSt = 3;
const int FieldPA = 4;
const int FieldPT = 5;
//-------------------------------------------//


 
void setup() {
  
  // Inicializa a porta Serial
  Serial.begin(115200);
  s.begin(115200);
  while (!Serial) continue;

}
 



void loop() {

  //--------Preparativos e definicoes Json---------//
  StaticJsonBuffer<15000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  //----------------------------------------------//
 
  if (root == JsonObject::invalid())  /* Caso n'ao receba dados, leia de novo*/
  {
    return;
  }

  //--------Recebe dados, guarda e mostra na serial-----//

  Serial.println("JSON recebeu");
  root.prettyPrintTo(Serial);
  Serial.println("");
  
  Serial.print("Temperature ");
  int data1 = root["temp"];
  Serial.println(data1);
  
  Serial.print("Umidade    ");
  int data2 = root["u"];
  Serial.println(data2);
  
  Serial.print("Sensacao Termica  ");
  int data3 = root["hi"];
  Serial.println(data3);
  
  Serial.print("Pressao Atm  ");
  int data4 = root["pa"];
  Serial.println(data4);
  
  Serial.print("Precipitacao  ");
  int data5 = root["pp"];
  Serial.println(data5);
  
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");
 Serial.println("");

   //-------------------------------------------------//

  //--------Envia dados para o ThingSpeak-----//

  ThingSpeak.writeField(myChannelNumber, FieldTemp, data1, myWriteAPIKey); //Envia os dados de Temperatura
  ThingSpeak.writeField(myChannelNumber, FieldUmi, data2, myWriteAPIKey); //Envia os dados de Umidade
  ThingSpeak.writeField(myChannelNumber, FieldSt, data3, myWriteAPIKey); //Envia os dados de Sensacao Termica
  ThingSpeak.writeField(myChannelNumber, FieldPA, data4, myWriteAPIKey); //Envia os dados de Pressao Atmosferica
  ThingSpeak.writeField(myChannelNumber, FieldPT, data5, myWriteAPIKey); //Envia os dados de Precipitacao

  //----------------------------------------//
}

