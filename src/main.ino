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
Refresh is how many milliseconds between each refresh of checking the Inputs
Speed is how fast it takes to get to the next LED
*/
int state = 1;
int currentLed = 0;
bool clockwise = true;

int refresh = 5;
const int speeds[9] = {660, 580, 480, 360, 320, 300, 280, 260, 245};
int currentSpeed = speeds[0];
int currentTime = 0;

int startState = 0;
int interactState = 0;
int lastInteractState = 0;

int gameRunLR = 0;

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

void clearLeds() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(latches[i], LOW);
    shiftOut(1, i);
    digitalWrite(latches[i], HIGH);
  }
}

void gameStart() {

}

void gameRun() {
  if (currentTime - gameRunLR >= currentSpeed) {
    int bitShifter = currentLed / 7;
    int bit = currentLed % 7;
    clearLeds();
    // Set latchPin low to allow data flow
    digitalWrite(latches[bitShifter], LOW); 
    shiftOut(bits[bit], bitShifter);
    // Set latchPin to high to lock and send data
    digitalWrite(latches[bitShifter], HIGH);

    if (clockwise) {
      currentLed++;
      if (currentLed == 28) {
        currentLed = 0;
      }
    } else {
      currentLed--;
      if (currentLed == -1) {
        currentLed = 27;
      }
    }

    gameRunLR = currentTime;
  }
}

void gameOver() {

}

void loop() {
  currentTime = millis();
  startState = digitalRead(start);
  interactState = digitalRead(interact);

  if (state == 0) {
    gameStart();
  } else if (state == 1)
  {
    if (!lastInteractState && interactState) {
      Serial.println(!clockwise);
      clockwise = !clockwise;
    }
    gameRun();
  } else if (state == 2) {
    gameOver();
  } else {
    state = 0;
  }

  lastInteractState = interactState;
}
