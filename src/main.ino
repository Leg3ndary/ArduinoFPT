// Pin connected to Pin 12 of 74HC595 (Latch)
int latchPin = 8;
// Pin connected to Pin 11 of 74HC595 (Clock)
int clockPin = 12;
// Pin connected to Pin 14 of 74HC595 (Data)
int dataPin = 11;

const int bits[8] = {1, 2, 4, 8, 16, 32, 64, 128};

void setup() {
  // Set pins to output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}


void loop() {
  for (int i = 0; i < 8; i++) {
    // Set latchPin low to allow data flow
    digitalWrite(latchPin, LOW);
    shiftOut(bits[i]);
    // Set latchPin to high to lock and send data
    digitalWrite(latchPin, HIGH);
    delay(100);
  }
}


void shiftOut(byte dataOut) {
  // Shift out 8 bits LSB first, on rising edge of clock
  boolean pinState;
  // Clear shift register ready for sending data
  digitalWrite(dataPin, LOW);
  digitalWrite(clockPin, LOW);
  // For each bit in dataOut send out a bit
  for (int i = 0; i <= 7; i++) {
    // Set clockPin to LOW prior to sending bit
    digitalWrite(clockPin, LOW);
    // If the value of DataOut and (logical AND) a bitmask are true, set pinState to 1 (HIGH)
    if (dataOut & (1 << i)) {
      pinState = HIGH;
    } else {
      pinState = LOW;
    }
    // Sets dataPin to HIGH or LOW depending on pinState
    digitalWrite(dataPin, pinState);
    // Send bit out on rising edge of clock
    digitalWrite(clockPin, HIGH);
  }
  // Stop shifting out data
  digitalWrite(clockPin, LOW);
}