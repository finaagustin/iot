const int TRIGPIN = D1;
const int ECHOPIN = D0;
int led1 = D8;
long timer, jarak; //berapa lama menerima sinyal

void setup()
{
  Serial.begin(9600);
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  pinMode(led1, OUTPUT);
}

void loop()
{
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  
  timer = pulseIn(ECHOPIN, HIGH);
  jarak = (timer/2)/29;
  // delay(1000);
  
  if (jarak >= 1 && jarak <=10) {
    digitalWrite(led1, HIGH);
  } 
  else {
    digitalWrite(led1, LOW);
  }
  
  Serial.print("Jarak = ");
  Serial.print(jarak);
  Serial.print(" cm ");
  Serial.println();
}