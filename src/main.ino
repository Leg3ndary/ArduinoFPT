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
const int seedPin = 18;
const int speakerPin = 19;

const int speeds[7] = {150, 120, 95, 75, 60, 50, 40};
const int difficultyLeds[7][4] = {
  {
    240, 0, 0, 0
  },
  {
    255, 128, 0, 0
  },
  {
    255, 248, 0, 0
  },
  {
    255, 255, 192, 0 
  },
  {
    255, 255, 252, 0
  },
  {
    255, 255, 255, 224
  },
  {
    255, 255, 255, 255
  }
};

/*
The following are all things that might change throughout the program
*/
long score = 0;
int state = 0;
int difficulty = 0;
bool clockwise = true;

int currentLed = 0;
int currentTime = 0;

int targetLed = random(8, 27);
int targetLedS = targetLed + 1;

int startState = 0;
int lastStartState = 0;
int interactState = 0;
int lastInteractState = 0;

int gameRunLR = 0;
int convertResult[4] = {0, 0, 0, 0};
int scoreResult[4] = {0, 0, 0, 0};

void resetGame() {
  score = 0;
  clockwise = true;

  currentLed = 0;

  targetLed = random(8, 27);
  targetLedS = targetLed + 1;
}

/*
Setting up all the pins to the correct mode.
*/
void setup() {
  Serial.begin(9600); // delete this after debugging
  for (int i = 0; i < 4; i++) {
    pinMode(dataPins[i], OUTPUT);
    pinMode(latchPins[i], OUTPUT);
    pinMode(clockPins[i], OUTPUT);
  }
  pinMode(startButton, INPUT);
  pinMode(interactButton, INPUT);
  pinMode(speakerPin, OUTPUT);

  renderDifficulty();
  randomSeed(analogRead(seedPin));
}

void generateTargets(int current) {
  targetLed = random(current + 5, current + 24) % 28;
  targetLedS = (targetLed + 1) % 28;
}

int customPower(int exponent) {
  int result = 2;
  for (int i = 0; i < exponent; i++) {
    result *= 2;
  }
  return result;
}

int* convert(int* leds) {
  int binary[4][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
  };

  for (int i = 0; i <= sizeof(leds) / sizeof(leds[0]) + 1; i++) {
    int bitShifter = leds[i] / 7;
    int bit = leds[i] % 7;
    binary[bitShifter][bit] = 1;
  }

  for (int i = 0; i < 4; i++) {
    int decimal = 255;
    for (int j = 0 ; j < 7 ; j++) {
      if (binary[i][j] == 0) {
        decimal -= customPower(6 - j);
      }
    }
    convertResult[i] = decimal;
  }
  
  return convertResult;
}

int* scoreConvert(long scoreTemp) {
  int binary[4][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
  };

  // max 128 per thing
  int arr[24];
  int counter = 0;

  while (scoreTemp != 0) {
		arr[counter] = scoreTemp % 2;
		counter++;
		scoreTemp /= 2;
	}

  for (int i = counter - 1; i >= 0; i--) {
    if (arr[i] == 1) {
      int bitShifter = i / 7;
      int bit = i % 7;
      binary[bitShifter][bit] = 1;
    }
  }

  for (int i = 0; i < 4; i++) {
    int decimal = 255;
    for (int j = 0 ; j < 7 ; j++) {
      if (binary[i][j] == 0) {
        decimal -= customPower(6 - j);
      }
    }
    scoreResult[i] = decimal;
  }
  
  return scoreResult;
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

// Clears all Led's of state (not really, explained later)
void clearLeds() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(latchPins[i], LOW);
    shiftOut(1, i);
    digitalWrite(latchPins[i], HIGH);
  }
}

// Specific rendering for difficulty at the start of the game.  
void renderDifficulty() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(latchPins[i], LOW); 
    shiftOut(difficultyLeds[difficulty][i], i);
    digitalWrite(latchPins[i], HIGH);
  }
}

void gameRun() {
  if (currentTime - gameRunLR >= speeds[difficulty] + score * 3) {
    int toConvert[] = {currentLed, targetLed, targetLedS};
    int* converted = convert(toConvert);

    for (int i = 0; i < 4; i++) {
      // Set latchPin low to allow data flow
      digitalWrite(latchPins[i], LOW);
      
      shiftOut(converted[i], i);
      // Set latchPin to high to lock and send data
      digitalWrite(latchPins[i], HIGH);
    }

    if (clockwise) {
      currentLed++;
    } else {
      currentLed--;
    }
    currentLed %= 28;

    gameRunLR = currentTime;
  }

  if (!lastInteractState && interactState) {
    if (currentLed == targetLed || currentLed == targetLedS) {
      score++;
      clockwise = !clockwise;
      generateTargets(currentLed);
    } else {
      state++;
      return;
    }
  }
}

void gameOver() {
  int* converted = scoreConvert(score);

  for (int i = 0; i < 4; i++) {
    // Set latchPin low to allow data flow
    digitalWrite(latchPins[i], LOW);

    shiftOut(converted[i], i);
    // Set latchPin to high to lock and send data
    digitalWrite(latchPins[i], HIGH);
  }
}

void loop() {
  currentTime = millis();
  startState = digitalRead(startButton);
  interactState = digitalRead(interactButton);

  if (state == 0) {
    if (!lastInteractState && interactState) {
      difficulty++;
      if (difficulty > 6) {
        difficulty = 0;
      }
      renderDifficulty();
    }
    if(!lastStartState && startState) {
      state++;
    }
  } else if (state == 1)
  {
    gameRun();
  } else if (state == 2) {
    gameOver();
    if (!lastInteractState && interactState) {
      state++;
      renderDifficulty();
      resetGame();
    }
  } else {
    state = 0;
  }

  lastStartState = startState;
  lastInteractState = interactState;
}
