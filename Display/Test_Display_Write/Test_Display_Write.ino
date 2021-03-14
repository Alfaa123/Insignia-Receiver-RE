#include <SPI.h>

static int PIN_CS = 4;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.beginTransaction(SPISettings(125000, LSBFIRST, SPI_MODE2));
  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);
  delay (3000);

//For setting display mode
digitalWrite(PIN_CS, LOW);
SPI.transfer(8);
digitalWrite(PIN_CS, HIGH);

//For turning on display and setting dimming
digitalWrite(PIN_CS, LOW);
SPI.transfer(143);
digitalWrite(PIN_CS, HIGH);

//For turning on and off main relays
digitalWrite(PIN_CS, LOW);
SPI.transfer(65);
SPI.transfer(0);
digitalWrite(PIN_CS, HIGH);

//For switching back to display memory mode
digitalWrite(PIN_CS, LOW);
SPI.transfer(64);
digitalWrite(PIN_CS, HIGH);


for (int y = 192; y < 228; y++){
digitalWrite(PIN_CS, LOW);
SPI.transfer(y);
SPI.transfer(255);
digitalWrite(PIN_CS, HIGH);
}

for (int y = 192; y < 228; y++){
for (int x = 1; x < 256; x=x*2){
Serial.print(y-192);
Serial.print("   ");
Serial.println(x, BIN);
while(!Serial.available()){
delay(500);
digitalWrite(PIN_CS, LOW);
SPI.transfer(y);
SPI.transfer(x);
digitalWrite(PIN_CS, HIGH);
delay(500);
digitalWrite(PIN_CS, LOW);
SPI.transfer(y);
SPI.transfer(0);
digitalWrite(PIN_CS, HIGH);
}
Serial.read();
}
digitalWrite(PIN_CS, LOW);
SPI.transfer(y);
SPI.transfer(255);
digitalWrite(PIN_CS, HIGH);
}
}

// the loop function runs over and over again forever
void loop() {                   // wait for a second
}
