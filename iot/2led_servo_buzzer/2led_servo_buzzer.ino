#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>
Servo myservo;

const char* ssid = "vivo Y35";
const char* pass = "apawe123957";
const uint16_t port = 80;
const char* host = "192.168.190.108";
int serv = D3;
int led = D6;
int led1 = D7;
int buz = D2;

String BASE_URL = "http://" + String(host) + "/webiot/public/api";

void setup(){
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(buz, OUTPUT);
  Serial.begin(115200);
  myservo.attach(serv);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  delay(1000);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  myservo.write(HIGH);
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("Your IP Address : ");
  Serial.println(WiFi.localIP());
}

void loop(){
  WiFiClient client;
  HTTPClient http;

  if(!client.connect(host, port)){
    Serial.println("Connection to server FAILED !");
    Serial.println(client.connect(host, port));
    delay(1000);
  }

  String url = BASE_URL + "/led";
  http.begin(client, url);

  int httpResponse = http.GET();

  while(httpResponse == 200){
    String response = http.getString();
    Serial.println(httpResponse);
    Serial.println(response);

    if(response == "1"){
      myservo.write(90);
      digitalWrite(led, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(buz, HIGH);
      delay(300);
    }
    else{
      myservo.write(60);
      digitalWrite(led, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(buz, LOW);
      delay(300);
    }
    delay(1000);
    return;
  }

  Serial.println("Internal server error");
  delay(1000);
}