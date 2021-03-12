#include <SPI.h>

static int PIN_CS = 4;

void setup() {
  SPI.begin();
  SPI.beginTransaction(SPISettings(500000, LSBFIRST, SPI_MODE2));
  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);
  delay (1000);

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
//delay(1);
digitalWrite(PIN_CS, LOW);
//delay(1);
SPI.transfer(y);
//delay(1);
SPI.transfer(0);
//delay(1);
digitalWrite(PIN_CS, HIGH);
}

for (int y = 192; y < 228; y++){
for (int x = 0; x < 256; x++){
//delay(1);
digitalWrite(PIN_CS, LOW);
//delay(1);
SPI.transfer(y);
//delay(1);
SPI.transfer(x);
delay(1);
digitalWrite(PIN_CS, HIGH);
}
}
}

// the loop function runs over and over again forever
void loop() {                   // wait for a second
}
