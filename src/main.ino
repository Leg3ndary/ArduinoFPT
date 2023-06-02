/*
This is code for a friend and I's arduino fpt, without the diagram it's kinda useless, so just don't copy ig!

Total Memory Available: 2048 bytes
*/

/*
The following are all constants, first group is pins, seconds is just other data that won't be changed.
*/
const int dataPins[4] = {13, 10, 7, 4};
const int latchPins[4] = {12, 9, 6, 3};
const int clockPins[4] = {11, 8, 5, 2};
const int startButton = 14;
const int interactButton = 15;
const int speakerPin = 19;

const int bits[8] = {128, 64, 32, 16, 8, 4, 2, 1};
const int speeds[9] = {660, 580, 480, 360, 320, 300, 280, 260, 245};

/*
The following are all things that might change throughout the program
*/
int state = 1;
bool clockwise = true;

int currentLed = 0;
int currentSpeed = speeds[0];
int currentTime = 0;

int startState = 0;
int lastStartState = 0;
int interactState = 0;
int lastInteractState = 0;

int gameRunLR = 0;

/*
Setting up all the pins to the correct mode.
*/
void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 4; i++) {
    pinMode(dataPins[i], OUTPUT);
    pinMode(latchPins[i], OUTPUT);
    pinMode(clockPins[i], OUTPUT);
  }
  pinMode(startButton, INPUT);
  pinMode(interactButton, INPUT);
  pinMode(speakerPin, OUTPUT);
}

void shiftOut(byte dataOut, int bitShifter) {
  // Shift out 8 bits LSB first, on rising edge of clock
  boolean pinState;
  // Clear shift register ready for sending data
  digitalWrite(dataPins[bitShifter], LOW);
  digitalWrite(clockPins[bitShifter], LOW);
  // For each bit in dataOut send out a bit
  for (int i = 0; i <= 7; i++) {
    // Set clockPin to LOW prior to sending bit
    digitalWrite(clockPins[bitShifter], LOW);
    // If the value of DataOut and (logical AND) a bitmask are true, set pinState to 1 (HIGH)
    if (dataOut & (1 << i)) {
      pinState = HIGH;
    } else {
      pinState = LOW;
    }
    // Sets dataPin to HIGH or LOW depending on pinState
    digitalWrite(dataPins[bitShifter], pinState);
    // Send bit out on rising edge of clock
    digitalWrite(clockPins[bitShifter], HIGH);
  }
  // Stop shifting out data
  digitalWrite(clockPins[bitShifter], LOW);
}

void clearLeds() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(latchPins[i], LOW);
    shiftOut(1, i);
    digitalWrite(latchPins[i], HIGH);
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
    digitalWrite(latchPins[bitShifter], LOW); 
    shiftOut(bits[bit], bitShifter);
    // Set latchPin to high to lock and send data
    digitalWrite(latchPins[bitShifter], HIGH);

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
  startState = digitalRead(startButton);
  interactState = digitalRead(interactButton);

  if (state == 0) {
    gameStart();
  } else if (state == 1)
  {
    if (!lastInteractState && interactState) {
      clockwise = !clockwise;
    }
    gameRun();
  } else if (state == 2) {
    gameOver();
  } else {
    state = 0;
  }

  lastStartState = startState;
  lastInteractState = interactState;
}
