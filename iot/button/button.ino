int redLedPin = D1;
int yellowLedPin = D2; 
int buttonPin = D3;

void setup() {
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) {
    digitalWrite(redLedPin, HIGH);
    delay(1000); 

    digitalWrite(redLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
    delay(1000); 

    digitalWrite(yellowLedPin, LOW);
  }
}