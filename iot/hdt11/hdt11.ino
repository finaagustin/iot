#include "DHT.h" 
#define DHTPIN D4 
#define DHTTYPE DHT11 
#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h> 
 
const char* ssid = "notfound"; 
const char* pass = "porquefi"; 
const uint16_t port = 80; 
const char* host = "192.168.1.3"; 
 
String BASE_URL = "http://" + String(host) + "/webiot/public/Dht11/uploaddata"; 
DHT dht(DHTPIN, DHTTYPE); 
 
void setup(){ 
  Serial.begin(115200); 
  Serial.println(F("DHTxx test!")); 
  WiFi.begin(ssid, pass); 
  dht.begin(); 
} 
void loop(){ 
  WiFiClient client; 
  HTTPClient http; 
  String url; 
  float h = dht.readHumidity(); 
  float t = dht.readTemperature(); 
  float f = dht.readTemperature(true); 
  url = BASE_URL + "/" + String(t) + "/" + String(h); 
  http.begin(client, url); 
  int httpResponse = http.GET(); 
  Serial.println(t); 
  Serial.println(h); 
  Serial.println(url); 
  delay(1000); 
}