/*
This is code for a friend and I's arduino fpt, without the diagram it's kinda useless, so just don't copy ig!

Total Memory Available: 2048 bytes
*/

/*
Datas is pins connected to Pin 14 of 74HC595 (BLUE)
Latches is pins connected to Pin 12 of 74HC595 (GREEN)
Clocks is pins connected to Pin 11 of 74HC595 (YELLOW)

Total Memory used here = 3 * 3 * 2 = 18 bytes
*/
const int datas[3] = {13, 10, 7};
const int latches[3] = {12, 9, 6};
const int clocks[3] = {11, 8, 5};

const int bits[8] = {128, 64, 32, 16, 8, 4, 2, 1};

/* State is what state the game is in.
0: Home Screen
- LEDs will be flashing randomly maybe we add patterns
- Piezos will be playing some random music

1: In game
- LEDs will be moving around in until it hits the goal

2: Game over
- Has to push reset to be brought to home screen

Memory used: 2 bytes
*/
int state = 1; // should be 0 normally

// Setting up the pins, all the pins for the bit shifters are outputs.
void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(datas[i], OUTPUT);
    pinMode(latches[i], OUTPUT);
    pinMode(clocks[i], OUTPUT);
  }
}

void loop() {
  // for (int i = 0; i < 8; i++) {
  //   // Set latchPin low to allow data flow
  //   digitalWrite(latchPin, LOW); 
  //   shiftOut(bits[i]);
  //   // Set latchPin to high to lock and send data
  //   digitalWrite(latchPin, HIGH);
  //   delay(100);
  // }
  if (state == 0) {
    // pass for now
  } else if (state == 1)
  {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 8; j++) {
        // Set latchPin low to allow data flow
        digitalWrite(latches[i], LOW); 
        shiftOut(bits[j], i);
        // Set latchPin to high to lock and send data
        digitalWrite(latches[i], HIGH);
        delay(50);
      }
    }
  }
}


void shiftOut(byte dataOut, int bitShifter) {
  // Shift out 8 bits LSB first, on rising edge of clock
  boolean pinState;
  // Clear shift register ready for sending data
  digitalWrite(datas[bitShifter], LOW);
  digitalWrite(clocks[bitShifter], LOW);
  // For each bit in dataOut send out a bit
  for (int i = 0; i <= 7; i++) {
    // Set clockPin to LOW prior to sending bit
    digitalWrite(clocks[bitShifter], LOW);
    // If the value of DataOut and (logical AND) a bitmask are true, set pinState to 1 (HIGH)
    if (dataOut & (1 << i)) {
      pinState = HIGH;
    } else {
      pinState = LOW;
    }
    // Sets dataPin to HIGH or LOW depending on pinState
    digitalWrite(datas[bitShifter], pinState);
    // Send bit out on rising edge of clock
    digitalWrite(clocks[bitShifter], HIGH);
  }
  // Stop shifting out data
  digitalWrite(clocks[bitShifter], LOW);
}
