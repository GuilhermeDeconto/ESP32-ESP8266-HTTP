#ifdef ESP32
#include<WiFi.h>
#include<WebServer.h>
// #include<HTTPClient.h>
// #include<Update.h>
WebServer server(80);
//HTTPClient client;
#elif ESP8266
#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
ESP8266WebServer server(80);
//ESP8266HTTPClient client;
#endif

#include"WiFiCredentials.h"
#include <DHT.h>
#include <ArduinoJson.h>

#define DHTPIN 4 // Pin G4 (GPIO4)
#define DHTTYPE DHT11 // Sensor type DHT11

DHT dht(DHTPIN, DHTTYPE);

float temperature;
float humidity;

void setup() {  
  Serial.begin(115200);
  delay(50);
  dht.begin();

  Serial.println("Connecting to wifi: ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Checking connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Ready");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); // Show ESP IP

  server.on("/", handleOnConnect);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server has initialized");
}

void loop() {
  server.handleClient();
}

void handleOnConnect() {
  StaticJsonDocument<256> doc;
  float temperature = dht.readTemperature(false, true);
  float humidity = dht.readHumidity();
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" ºC");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
  Serial.print("Heat index");
  Serial.print(heatIndex);

  char json_string[256];
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["heatIndex"] = heatIndex;

  serializeJson(doc, json_string);
  server.send(200, "application/json", json_string);
}

void handleNotFound() { 
  server.send(404, "text/plain", "Not Found");
}