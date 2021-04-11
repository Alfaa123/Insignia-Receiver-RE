#include <SPI.h>

static int PIN_CS = 4;
//these are the two character map char arrays for the eight 14 segment displays
static char firstByteFourteenSegement[] = {144,0,0,0,68,68,144,0,
                          0,0,0,0,80,0,0,0,0,0,
                          0,0,0,0,0,144,0,144,0,0,
                          0,0,144,0,72,0,96,40,0,0,
                          8,8,32,144,0,68,12,108,112,68};
static char secondByteFourteenSegement[] = {3,0,3,1,0,252,0,219,
                          241,103,183,191,128,255,247,0,0,0,
                          0,0,0,0,239,241,156,240,159,142,
                          189,111,144,120,14,28,108,108,252,207,
                          252,207,177,128,124,12,108,0,0,144};
//This is the character map for the sub dispay with the 7 segment displays
static char subDisplaySevenSegment[] = {252,96,219,243,103,183,191,224,255,231};

//writes a single character to the main display
void writeChar(char i, char position){
char address = 222;
address = address - (3*position);
digitalWrite(PIN_CS, LOW);
SPI.transfer(address);
SPI.transfer(firstByteFourteenSegement[i-43]);
SPI.transfer(secondByteFourteenSegement[i-43]);
digitalWrite(PIN_CS, HIGH);
}

//writes a string up to 8 digits to the main display
void writeDisplay(String i = ""){
char charArray[9];
i.toCharArray(charArray,9);
for (int x = 0; x < i.length(); x++){
  writeChar(charArray[x],x);
}
}

//Writes a 2 digit numarical value to the sub display
void writeSubDisplay(int i){
  if (i < 100){
    digitalWrite(PIN_CS, LOW);
    SPI.transfer(196);
    SPI.transfer(subDisplaySevenSegment[(i / 10U) % 10]);
    digitalWrite(PIN_CS, HIGH);
    digitalWrite(PIN_CS, LOW);
    SPI.transfer(193);
    SPI.transfer(subDisplaySevenSegment[(i / 1U) % 10]);
    digitalWrite(PIN_CS, HIGH);
  }
}

//Clears the display. By default clears the entire display use the following numbers to only clear parts of the display:
//0: Clear entire display (default)
//1: Clear ONLY the 14 segment display characters
//2: Clear ONLY the sub display characters
void clearDisplay(int x = 0){
switch (x){
  case 0:
  for (int y = 192; y < 228; y++){
  digitalWrite(PIN_CS, LOW);
  SPI.transfer(y);
  SPI.transfer(0);
  digitalWrite(PIN_CS, HIGH);
  }
  break;
  case 1:
  for (int y = 0; y < 9; y++){
  char address = 222;  
  address = address - (3*y);  
  digitalWrite(PIN_CS, LOW);
  SPI.transfer(address);
  SPI.transfer(0);
  SPI.transfer(0);
  digitalWrite(PIN_CS, HIGH);
  }
  break;
  case 2:
  for (int y = 193; y < 197; y=y+3){
    digitalWrite(PIN_CS, LOW);
    SPI.transfer(y);
    SPI.transfer(0);
    digitalWrite(PIN_CS, HIGH);
  }
  break;
}


}

void displayBrightness(bool displayOn, char brightness){
if (brightness > 7){brightness = 7;}
digitalWrite(PIN_CS, LOW);
SPI.transfer(128 + (displayOn * 8) + brightness);
digitalWrite(PIN_CS, HIGH);
}

void powerRelay(char relayNumber, bool onOff){
if(relayNumber < 4){
char x = 0;
bitWrite(x,relayNumber,onOff);
digitalWrite(PIN_CS, LOW);
SPI.transfer(65);
SPI.transfer(x);
digitalWrite(PIN_CS, HIGH);
}
digitalWrite(PIN_CS, LOW);
SPI.transfer(64);
digitalWrite(PIN_CS, HIGH);
}


void setup() {
  //Serial.begin(115200);
  SPI.begin();
  SPI.beginTransaction(SPISettings(125000, LSBFIRST, SPI_MODE2));
  pinMode(PIN_CS, OUTPUT);
  digitalWrite(PIN_CS, HIGH);
  delay (300);

//For turning on display and setting dimming
displayBrightness(1,8);

//For turning on and off main relays
powerRelay(1,0);



writeSubDisplay(88);
writeDisplay("TEST");



}

// the loop function runs over and over again forever
void loop() {  
 delay(1000);}
