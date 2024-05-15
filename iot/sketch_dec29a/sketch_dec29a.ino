#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


const char* ssid = "7";
const char* pass = "123456789";
const uint16_t port = 80; //di xampp
const char* host = "192.168.43.44"; //ip perangkat
int ledCon = D4;
int ledHost = D2;
String BASE_URL = "http://" + String(host) + "/webiot/public/api"; //host di convert settingan dari github
void setup() {
  Serial.begin(115200);
  pinMode(ledCon, OUTPUT);
  pinMode(ledHost, OUTPUT);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass); //wifi untuk memulai pake ssid dan pass
  delay(1000);


  while (WiFi.status() != WL_CONNECTED) {
    // digitalWrite(ledCon, LOW);
    delay(500);
    Serial.print(".");
  }


  digitalWrite(ledCon, HIGH);
  Serial.println("");
  Serial.println("wifi Connected");
  Serial.print("Your IP Address : ");
  Serial.println(WiFi.localIP());
}


void loop() {
  // put your main code here, to run repeatedly:


  WiFiClient client;
  HTTPClient http;


  if (!client.connect(host, port)) {
    Serial.println("Connection to server FAILED !");
    Serial.println(client.connect(host, port));
    delay(1000);
    return;
  }


  String url = BASE_URL + "/led";
  http.begin(client, url); //http melakukan koneksi ke server


  int httpResponse = http.GET();


  while (httpResponse == 200) {
    String response = http.getString();
    Serial.println(httpResponse);
    Serial.println(response);


    if (response == "1") {
      digitalWrite(ledCon, HIGH);
    } else {
      digitalWrite(ledCon, LOW);
    }


    delay(1000);
    return;
  }


  Serial.println("Internal server error");
  delay(1000);
}