#include <SPI.h> 
#include <MFRC522.h> 
 
constexpr uint8_t RST_PIN = D1; 
constexpr uint8_t SS_PIN = D2; 
 
 
byte readCard[4]; 
String MasterTag = "F3FD6110"; 
String tagID = ""; 
 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
 
void setup() { 
  Serial.begin(9600); 
  while (!Serial); 
  SPI.begin(); 
  mfrc522.PCD_Init(); 
} 
 
void loop() 
{ 
while (getUID()) 
{ 
  if (tagID == MasterTag) 
  { 
    Serial.println("Connected"); 
  } 
  else 
  { 
    Serial.println("Sorry card do'not Connected"); 
  } 
  delay(2000); 
} 
 
} 
 
boolean getUID() 
{ 
  if (! mfrc522.PICC_IsNewCardPresent()){ 
    return false; 
} 
if (! mfrc522.PICC_ReadCardSerial()){ 
    return false; 
} 
tagID=""; 
for (uint8_t i =0; i <4; i++){ 
  tagID.concat(String(mfrc522.uid.uidByte[i],HEX)); 
} 
tagID.toUpperCase(); 
mfrc522.PICC_HaltA(); 
return true; 
}