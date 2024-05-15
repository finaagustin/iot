// C++ code
//
int potensioner = A0; // karna analog 0
int led = D1;

void setup()
{
  pinMode(potensioner, INPUT); 
  Serial.begin(9600); //mengatur kecepatan arduino ke serial monitor
  pinMode(led, OUTPUT);
}

void loop()
{
  int potensioner = analogRead(0);
  Serial.print(potensioner);
  if(potensioner>=600){
    digitalWrite(led, LOW); //nyala
  }else if (potensioner<=599) {
   digitalWrite(led, HIGH); //mati
  }
}