 
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "c055ec";
const char* password = "287460863";
const int serverPort = 80;

int counter = 0;
String text = "Questa è il mio Server!";

AsyncWebServer server(serverPort);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
//  SERVER  SETUP 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body>";
    html += "<h1>" + text + "</h1>";
    html += "<p>Counter: " + String(counter) + "</p>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  server.begin();
  Serial.println("Server started");

 // SERVE END 
}

void loop() {
  counter++;
  delay(1000);
}
