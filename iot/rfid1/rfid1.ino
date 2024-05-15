#include <SPI.h> 
#include <MFRC522.h> 
 
constexpr uint8_t RST_PIN = D1; 
constexpr uint8_t SS_PIN = D2; 
 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
 
void setup() { 
  Serial.begin(9600); 
  while (!Serial); 
  SPI.begin(); 
  mfrc522.PCD_Init(); 
} 
 
void loop() { 
  if ( ! mfrc522.PICC_IsNewCardPresent()) { 
    return; 
  } 
 
  if ( ! mfrc522.PICC_ReadCardSerial()) { 
    return; 
  } 
 
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid)); 
}