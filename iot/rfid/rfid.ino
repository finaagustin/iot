#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h> 
#include <SPI.h> 
#include <MFRC522.h> 
 
constexpr uint8_t RST_PIN = D1; 
constexpr uint8_t SS_PIN = D2; 

byte readCard[4]; 
String MasterTag = "5740766C"; 
String tagID = ""; 
String username = "Kelompok 3"; 
 
const char* ssid = "Fina"; 
const char* pass = "1234567890"; 
const uint16_t port = 80; 
const char* host = "192.168.148.108"; 
 
String BASE_URL = "http://" + String(host) + "/webiot/public/rfid/update"; 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
 
void setup() { 
  Serial.begin(115200); 
  Serial.print(F("RFID test!")); 
  WiFi.begin(ssid, pass); 
  while (!Serial); 
  SPI.begin(); 
  mfrc522.PCD_Init(); 
} 
 
 
boolean getUID(){ 
  if(!mfrc522.PICC_IsNewCardPresent()){ 
    return false; 
  } 
 
  if(!mfrc522.PICC_ReadCardSerial()){ 
    return false; 
  } 
 
  tagID = ""; 
  for (uint8_t i = 0; i < 4; i++) { 
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); 
  } 
  tagID.toUpperCase(); 
  mfrc522.PICC_HaltA(); 
  return true; 
} 
 
 
void loop() { 
  WiFiClient client; 
  HTTPClient http; 
 
  String url; 
  while(getUID()) 
  { 
    if ( tagID == MasterTag ){ 
      Serial.print("tag ID : "); 
      Serial.println(username); 
      url = BASE_URL + "/" + String(username); 
      http.begin(client, url); 
      int httpResponse = http.GET(); 
      Serial.println(url); 
    } 
    else{ 
      Serial.print("tag ID : "); 
      Serial.println(tagID); 
      url = BASE_URL + "/" + String(tagID); 
      http.begin(client, url); 
      int httpResponse = http.GET(); 
      Serial.println(url); 
    } 
    delay(2000); 
  } 
}