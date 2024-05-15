#include <ESP8266WiFi.h> 
#include <ESP8266HTTPClient.h> 
#include <WiFiClient.h> 
#include <SPI.h> 
#include <MFRC522.h>
#include <Servo.h>
Servo myservo; 
 
constexpr uint8_t RST_PIN = D1; 
constexpr uint8_t SS_PIN = D2; 
int serv = D3;
// const int TRIGPIN = D0;
// const int ECHOPIN = D4;
// int led1 = D8;
// long timer, jarak;

byte readCard[4]; 
String MasterTag = "F3FD6110"; 
String tagID = ""; 
String username = "Kelompok_3"; 
 
const char* ssid = "Fina"; 
const char* pass = "1234567890"; 
const uint16_t port = 80; 
const char* host = "192.168.33.108"; 
 
String BASE_URL = "http://" + String(host) + "/webiot/public/rfid/update"; 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
 
void setup() { 
  Serial.begin(115200);
  myservo.attach(serv); 
  Serial.print(F("RFID test!")); 
  WiFi.begin(ssid, pass); 
  while (!Serial); 
  SPI.begin(); 
  mfrc522.PCD_Init();
  myservo.write(HIGH);
  // pinMode(TRIGPIN, OUTPUT);
  // pinMode(ECHOPIN, INPUT);
  // pinMode(led1, OUTPUT); 
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
      url = BASE_URL + "/" + String(tagID); 
      http.begin(client, url); 
      int httpResponse = http.GET(); 
      Serial.println(url);
      Serial.println("PINTU TERBUKA"); 
      myservo.write(0);
      // digitalWrite(TRIGPIN, LOW); 
      // delayMicroseconds(2); 
      // digitalWrite(TRIGPIN, HIGH); 
      // delayMicroseconds(10); 
      // digitalWrite(TRIGPIN, LOW); 
       
      // timer = pulseIn(ECHOPIN, HIGH); 
      // jarak = (timer/2)/29; 
      // delay(1000); 
 
      // Serial.print("Jarak = "); 
      // Serial.print(jarak); 
      // Serial.print(" cm "); 
      // Serial.println(); 
       
      // if (jarak >= 1 && jarak <=10) { 
        // digitalWrite(led1, HIGH); //lampu nyala
      // } 
    } 
    else{ 
      Serial.print("tag ID : "); 
      Serial.println(tagID); 
      url = BASE_URL + "/" + String(tagID); 
      http.begin(client, url); 
      int httpResponse = http.GET(); 
      Serial.println(url);
      Serial.println("GAGAL TERBUKA"); 
      myservo.write(100);
      // digitalWrite(led1, LOW); //lampu mati
    } 
    // delay(500); 
  } 
}


