//
// A simple server implementation showing how to:
//  * serve static messages
//  * read GET and POST parameters
//  * handle missing pages / 404s
// 23.05.2023

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebSrv.h>


#include <ESP8266WiFiMulti.h>
#include <lm75.h>
//  3.05.2023 sensor temp saatmiseks T2



const char* ssid = "c055ec";
const char* password = "287460863";
 
const int serverPort = 80;
int counter = 0;
String text = "Magamistoas on andur T1 esp8266";

AsyncWebServer server(serverPort);

//const IPAddress serverIP(192, 168, 0, 10);  // ESP32 vastuvõtja staatiline IP-aadress



// Set your Static IP address
IPAddress local_IP(192, 168, 0, 41);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);   //85.253.176.1

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional





struct Message {
  int senderID;
  float temperature;
};

TempI2C_LM75 termo = TempI2C_LM75(0x48,TempI2C_LM75::nine_bits);
int t;

ESP8266WiFiMulti wifiMulti;
WiFiClient client;

void setup() {
  Serial.begin(115200);


 // Configures static IP address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  
  wifiMulti.addAP(ssid, password);
  wifiMulti.run();
  
  WiFi.mode(WIFI_STA);  // Seadista ESP8266 töörežiim klientina (station mode)
  WiFi.setSleepMode(WIFI_NONE_SLEEP);  // Lülita une režiim välja, et kanalit saaks muuta
  wifi_set_channel(3);  // Muuda WiFi-kanalit soovitud väärtusele
  
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Yhendame wifisse...");
  }
  
  Serial.println("KORRAS, olen WIFI-s");
  Serial.print("Minu IP Address on: ");
  Serial.println(WiFi.localIP());

//  SERVER  SETUP 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body>";
    html += "<h1>" + text + "</h1>";
    html += "<p>t=: " + String(t) + "</p>";// T3
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.begin();
  Serial.println("Server started");

 // SERVE END 
  
}


void temperatuur(){
    Serial.print("Temperature = ");
     String temps=String(termo.getTemp());
  
   Serial.print(temps);
 t=temps.toInt(); 
 // t=30;
    Serial.print("t=  ");
  Serial.println(t);
}

void loop() {
   
 delay(10000);
 temperatuur();
 Serial.print("t=");
 Serial.println(t);
}// LOOP
