/*
This is code for a friend and I's arduino fpt, without the diagram it's kinda useless, so just don't copy ig!

Total Memory Available: 2048 bytes
*/

/*
Datas is pins connected to Pin 14 of 74HC595 (BLUE)
Latches is pins connected to Pin 12 of 74HC595 (GREEN)
Clocks is pins connected to Pin 11 of 74HC595 (YELLOW)

start is the start button. (Start)
interact is the interaction button. (X)

Total Memory used here = 4 * 3 * 2 = 24 bytes
*/
const int datas[4] = {13, 10, 7, 4};
const int latches[4] = {12, 9, 6, 3};
const int clocks[4] = {11, 8, 5, 2};

const int start = 14;
const int interact = 15;
const int speaker1 = 18;
const int speaker2 = 19;
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
int state = 1;
int ledNum = 0;
volatile bool clockwise = true;
byte startState = HIGH;
byte interactState = HIGH;

/*
Refresh is how many milliseconds between each refresh of checking the Inputs
Speed is how fast it takes to get to the next LED
*/
int refresh = 4;
const int speeds[10] = {720, 660, 580, 480, 360, 320, 300, 280, 260, 248};

/*
Setting up all the pins.
Output pins are all the bitShifter pins, as well as the speakers.
INPUT_PULLUP uses the inbuilt resistors to allow us not to use resistors for start and interact.
*/
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(datas[i], OUTPUT);
    pinMode(latches[i], OUTPUT);
    pinMode(clocks[i], OUTPUT);
  }
  pinMode(start, INPUT);
  pinMode(interact, INPUT);
  pinMode(speaker1, OUTPUT);
  pinMode(speaker2, OUTPUT);
}

void startISR() {
  clockwise = !clockwise;
  Serial.println(clockwise);
}

void interactISR() {
  if (digitalRead(interact) == HIGH) {
    interactState = 1;
  } else {
    interactState = 0;
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

void loop() {
  // Clock delay
  delay(1);
  startState = digitalRead(start);
  interactState = digitalRead(interact);

  if (state == 0) {
    // pass for now
  } else if (state == 1)
  {
    int bitShifter = ledNum / 7;
    int bit = ledNum % 7;
    // Set latchPin low to allow data flow
    digitalWrite(latches[bitShifter], LOW); 
    shiftOut(bits[bit], bitShifter);
    // Set latchPin to high to lock and send data
    digitalWrite(latches[bitShifter], HIGH);

    delay(50);

    if (clockwise) {
      ledNum++;
      if (ledNum == 28) {
        ledNum = 0;
      }
      if (bit == 6) {
        // Set latchPin low to allow data flow
        digitalWrite(latches[bitShifter], LOW); 
        shiftOut(1, bitShifter);
        // Set latchPin to high to lock and send data
        digitalWrite(latches[bitShifter], HIGH);
      }
    } else {
      ledNum--;
      if (ledNum == -1) {
        ledNum = 27;
      }
      if (bit == 0) {
        // Set latchPin low to allow data flow
        digitalWrite(latches[bitShifter], LOW); 
        shiftOut(1, bitShifter);
        // Set latchPin to high to lock and send data
        digitalWrite(latches[bitShifter], HIGH);
      }
    }

    

  } else if (state == 2) {

  } else {
    state = 0;
  }
}
