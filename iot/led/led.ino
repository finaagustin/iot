// Kode untuk mengendalikan dua LED menggunakan NodeMCU (ESP8266)

// Menentukan pin yang terhubung ke LED
const int ledPin1 = D1; // Anda dapat mengganti pin sesuai dengan kon eksi hardware Anda
const int ledPin2 = D2;

void setup() {
  // Mengatur pin sebagai OUTPUT
  pinMode(ledPin1, OUTPUT);  
  pinMode(ledPin2, OUTPUT);
}

void loop() {
  // Menyalakan LED pertama
  digitalWrite(ledPin1, HIGH);
  delay(1000); // Tunggu selama 1 detik

  // Mematikan LED pertama
  digitalWrite(ledPin1, LOW);

  // Menyalakan LED kedua
  digitalWrite(ledPin2, HIGH);
  delay(1000); // Tunggu selama 1 detik

  // Mematikan LED kedua
  digitalWrite(ledPin2, LOW);
  delay(1000); // Tunggu selama 1 detik lagi sebelum mengulang
}