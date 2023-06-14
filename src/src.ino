/*
Pop the lock gamebox code, Copyright Leg3ndary 2023.
*/

// Macros
#define D3  147
#define E3  165
#define FS3 185
#define G3  196
#define A3  220
#define AS3 233
#define B3  247
#define C4  262
#define CS4 277
#define D4  294
#define DS4 311
#define E4  330
#define F4  349
#define FS4 370
#define G4  392
#define GS4 415
#define A4  440
#define AS4 466
#define B4  494
#define C5  523
#define CS5 554
#define D5  587
#define DS5 622
#define E5  659
#define F5  698
#define FS5 740
#define G5  784
#define GS5 831
#define A5  880
#define AS5 932
#define B5  988
#define C6  1047
#define CS6 1109
#define DS6 1245
#define F6  1397
#define REST 0

// Constants
const int dataPins[4] = {13, 10, 7, 4};
const int latchPins[4] = {12, 9, 6, 3};
const int clockPins[4] = {11, 8, 5, 2};
const int startPin = 14;
const int interactPin = 15;
const int seedPin = 18;
const int speakerPin = 19;

const int speeds[7] = {150, 120, 95, 75, 60, 50, 40};

// Melodies are all from https://github.com/robsoncouto/arduino-songs/blob/master/harrypotter/harrypotter.ino
const PROGMEM int tetrisMelody[] = {
  E5, 4,  B4,8,  C5,8,  D5,4,  C5,8,  B4,8,
  A4, 4,  A4,8,  C5,8,  E5,4,  D5,8,  C5,8,
  B4, -4,  C5,8,  D5,4,  E5,4,
  C5, 4,  A4,4,  A4,8,  A4,4,  B4,8,  C5,8,

  D5, -4,  F5,8,  A5,4,  G5,8,  F5,8,
  E5, -4,  C5,8,  E5,4,  D5,8,  C5,8,
  B4, 4,  B4,8,  C5,8,  D5,4,  E5,4,
  C5, 4,  A4,4,  A4,4, REST, 4,

  E5, 4,  B4,8,  C5,8,  D5,4,  C5,8,  B4,8,
  A4, 4,  A4,8,  C5,8,  E5,4,  D5,8,  C5,8,
  B4, -4,  C5,8,  D5,4,  E5,4,
  C5, 4,  A4,4,  A4,8,  A4,4,  B4,8,  C5,8,

  D5, -4,  F5,8,  A5,4,  G5,8,  F5,8,
  E5, -4,  C5,8,  E5,4,  D5,8,  C5,8,
  B4, 4,  B4,8,  C5,8,  D5,4,  E5,4,
  C5, 4,  A4,4,  A4,4, REST, 4,

  E5,2,  C5,2,
  D5,2,   B4,2,
  C5,2,   A4,2,
  GS4,2,  B4,4,  REST,8, 
  E5,2,   C5,2,
  D5,2,   B4,2,
  C5,4,   E5,4,  A5,2,
  GS5,2,
};
const int tetrisTempo = 144;

const PROGMEM int zeldaMelody[] = {
  AS4,-2,  F4,8,  F4,8,  AS4,8,
  GS4,16,  FS4,16,  GS4,-2,
  AS4,-2,  FS4,8,  FS4,8,  AS4,8,
  A4,16,  G4,16,  A4,-2,
  REST,1, 

  AS4,4,  F4,-4,  AS4,8,  AS4,16,  C5,16, D5,16, DS5,16,
  F5,2,  F5,8,  F5,8,  F5,8,  FS5,16, GS5,16,
  AS5,-2,  AS5,8,  AS5,8,  GS5,8,  FS5,16,
  GS5,-8,  FS5,16,  F5,2,  F5,4, 

  DS5,-8, F5,16, FS5,2, F5,8, DS5,8,
  CS5,-8, DS5,16, F5,2, DS5,8, CS5,8,
  C5,-8, D5,16, E5,2, G5,8, 
  F5,16, F4,16, F4,16, F4,16,F4,16,F4,16,F4,16,F4,16,F4,8, F4,16,F4,8,

  AS4,4,  F4,-4,  AS4,8,  AS4,16,  C5,16, D5,16, DS5,16,
  F5,2,  F5,8,  F5,8,  F5,8,  FS5,16, GS5,16,
  AS5,-2, CS6,4,
  C6,4, A5,2, F5,4,
  FS5,-2, AS5,4,
  A5,4, F5,2, F5,4,

  FS5,-2, AS5,4,
  A5,4, F5,2, D5,4,
  DS5,-2, FS5,4,
  F5,4, CS5,2, AS4,4,
  C5,-8, D5,16, E5,2, G5,8, 
  F5,16, F4,16, F4,16, F4,16,F4,16,F4,16,F4,16,F4,16,F4,8, F4,16,F4,8,
};
const int zeldaTempo = 88;

const PROGMEM int neverGonneGiveYouUpMelody[] = {
  D5,-4, E5,-4, A4,4,
  E5,-4, FS5,-4, A5,16, G5,16, FS5,8,
  D5,-4, E5,-4, A4,2,
  A4,16, A4,16, B4,16, D5,8, D5,16,
  D5,-4, E5,-4, A4,4,
  E5,-4, FS5,-4, A5,16, G5,16, FS5,8,
  D5,-4, E5,-4, A4,2,
  A4,16, A4,16, B4,16, D5,8, D5,16,
  REST,4, B4,8, CS5,8, D5,8, D5,8, E5,8, CS5,-8,
  B4,16, A4,2, REST,4, 

  REST,8, B4,8, B4,8, CS5,8, D5,8, B4,4, A4,8,
  A5,8, REST,8, A5,8, E5,-4, REST,4, 
  B4,8, B4,8, CS5,8, D5,8, B4,8, D5,8, E5,8, REST,8,
  REST,8, CS5,8, B4,8, A4,-4, REST,4,
  REST,8, B4,8, B4,8, CS5,8, D5,8, B4,8, A4,4,
  E5,8, E5,8, E5,8, FS5,8, E5,4, REST,4,
   
  D5,2, E5,8, FS5,8, D5,8,
  E5,8, E5,8, E5,8, FS5,8, E5,4, A4,4,
  REST,2, B4,8, CS5,8, D5,8, B4,8,
  REST,8, E5,8, FS5,8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,

  E5,-8, E5,-8, D5,-8, CS5,16, B4,-8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,8, A4,8, A4,8, 
  E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,

  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8,
  E5,4, D5,2, REST,4,
  REST,8, B4,8, D5,8, B4,8, D5,8, E5,4, REST,8,
  REST,8, CS5,8, B4,8, A4,-4, REST,4,
  REST,8, B4,8, B4,8, CS5,8, D5,8, B4,8, A4,4,
  REST,8, A5,8, A5,8, E5,8, FS5,8, E5,8, D5,8,
  
  REST,8, A4,8, B4,8, CS5,8, D5,8, B4,8,
  REST,8, CS5,8, B4,8, A4,-4, REST,4,
  B4,8, B4,8, CS5,8, D5,8, B4,8, A4,4, REST,8,
  REST,8, E5,8, E5,8, FS5,4, E5,-4, 
  D5,2, D5,8, E5,8, FS5,8, E5,4, 
  E5,8, E5,8, FS5,8, E5,8, A4,8, A4,4,

  REST,-4, A4,8, B4,8, CS5,8, D5,8, B4,8,
  REST,8, E5,8, FS5,8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  E5,-8, E5,-8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8, 

   E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8,  
  E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
   
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8,  
  E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8, 

  E5,4, D5,2, REST,4
};
const int neverGonnaGiveYouUpTempo = 144;

const PROGMEM int starWarsMelody[] = {
  AS4,8, AS4,8, AS4,8,
  F5,2, C6,2,
  AS5,8, A5,8, G5,8, F6,2, C6,4,  
  AS5,8, A5,8, G5,8, F6,2, C6,4,  
  AS5,8, A5,8, AS5,8, G5,2, C5,8, C5,8, C5,8,
  F5,2, C6,2,
  AS5,8, A5,8, G5,8, F6,2, C6,4,  
  
  AS5,8, A5,8, G5,8, F6,2, C6,4,
  AS5,8, A5,8, AS5,8, G5,2, C5,-8, C5,16, 
  D5,-4, D5,8, AS5,8, A5,8, G5,8, F5,8,
  F5,8, G5,8, A5,8, G5,4, D5,8, E5,4,C5,-8, C5,16,
  D5,-4, D5,8, AS5,8, A5,8, G5,8, F5,8,
  
  C6,-8, G5,16, G5,2, REST,8, C5,8,
  D5,-4, D5,8, AS5,8, A5,8, G5,8, F5,8,
  F5,8, G5,8, A5,8, G5,4, D5,8, E5,4,C6,-8, C6,16,
  F6,4, DS6,8, CS6,4, C6,8, AS5,4, GS5,8, G5,4, F5,8,
  C6,1,
};
const int starWarsTempo = 108;

const PROGMEM int miiChannelMelody[] = {
  FS4,8, REST,8, A4,8, CS5,8, REST,8,A4,8, REST,8, FS4,8,
  D4,8, D4,8, D4,8, REST,8, REST,4, REST,8, CS4,8,
  D4,8, FS4,8, A4,8, CS5,8, REST,8, A4,8, REST,8, F4,8,
  E5,-4, DS5,8, D5,8, REST,8, REST,4,
  
  GS4,8, REST,8, CS5,8, FS4,8, REST,8,CS5,8, REST,8, GS4,8,
  REST,8, CS5,8, G4,8, FS4,8, REST,8, E4,8, REST,8,
  E4,8, E4,8, E4,8, REST,8, REST,4, E4,8, E4,8,
  E4,8, REST,8, REST,4, DS4,8, D4,8, 

  CS4,8, REST,8, A4,8, CS5,8, REST,8,A4,8, REST,8, FS4,8,
  D4,8, D4,8, D4,8, REST,8, E5,8, E5,8, E5,8, REST,8,
  REST,8, FS4,8, A4,8, CS5,8, REST,8, A4,8, REST,8, F4,8,
  E5,2, D5,8, REST,8, REST,4,

  B4,8, G4,8, D4,8, CS4,4, B4,8, G4,8, CS4,8,
  A4,8, FS4,8, C4,8, B3,4, F4,8, D4,8, B3,8,
  E4,8, E4,8, E4,8, REST,4, REST,4, AS4,4,
  CS5,8, D5,8, FS5,8, A5,8, REST,8, REST,4, 

  REST,2, A3,4, AS3,4,
  A3,-4, A3,8, A3,2,
  REST,4, A3,8, AS3,8, A3,8, F4,4, C4,8,
  A3,-4, A3,8, A3,2,

  REST,2, B3,4, C4,4,
  CS4,-4, C4,8, CS4,2,
  REST,4, CS4,8, C4,8, CS4,8, GS4,4, DS4,8,
  CS4,-4, DS4,8, B3,1,
  
  E4,4, E4,4, E4,4, REST,8,

  FS4,8, REST,8, A4,8, CS5,8, REST,8,A4,8, REST,8, FS4,8,
  D4,8, D4,8, D4,8, REST,8, REST,4, REST,8, CS4,8,
  D4,8, FS4,8, A4,8, CS5,8, REST,8, A4,8, REST,8, F4,8,
  E5,-4, DS5,8, D5,8, REST,8, REST,4,
  
  GS4,8, REST,8, CS5,8, FS4,8, REST,8,CS5,8, REST,8, GS4,8,
  REST,8, CS5,8, G4,8, FS4,8, REST,8, E4,8, REST,8,
  E4,8, E4,8, E4,8, REST,8, REST,4, E4,8, E4,8,
  E4,8, REST,8, REST,4, DS4,8, D4,8, 

  CS4,8, REST,8, A4,8, CS5,8, REST,8,A4,8, REST,8, FS4,8,
  D4,8, D4,8, D4,8, REST,8, E5,8, E5,8, E5,8, REST,8,
  REST,8, FS4,8, A4,8, CS5,8, REST,8, A4,8, REST,8, F4,8,
  E5,2, D5,8, REST,8, REST,4,

  B4,8, G4,8, D4,8, CS4,4, B4,8, G4,8, CS4,8,
  A4,8, FS4,8, C4,8, B3,4, F4,8, D4,8, B3,8,
  E4,8, E4,8, E4,8, REST,4, REST,4, AS4,4,
  CS5,8, D5,8, FS5,8, A5,8, REST,8, REST,4, 

  REST,2, A3,4, AS3,4,
  A3,-4, A3,8, A3,2,
  REST,4, A3,8, AS3,8, A3,8, F4,4, C4,8,
  A3,-4, A3,8, A3,2,

  REST,2, B3,4, C4,4,
  CS4,-4, C4,8, CS4,2,
  REST,4, CS4,8, C4,8, CS4,8, GS4,4, DS4,8,
  CS4,-4, DS4,8, B3,1,
  
  E4,4, E4,4, E4,4, REST,8,
};
const int miiChannelTempo = 114;

const PROGMEM int canonInDMelody[] = {
  FS4,2, E4,2,
  D4,2, CS4,2,
  B3,2, A3,2,
  B3,2, CS4,2,
  FS4,2, E4,2,
  D4,2, CS4,2,
  B3,2, A3,2,
  B3,2, CS4,2,
  D4,2, CS4,2,
  B3,2, A3,2,
  G3,2, FS3,2,
  G3,2, A3,2,

  D4,4, FS4,8, G4,8, A4,4, FS4,8, G4,8, 
  A4,4, B3,8, CS4,8, D4,8, E4,8, FS4,8, G4,8, 
  FS4,4, D4,8, E4,8, FS4,4, FS3,8, G3,8,
  A3,8, G3,8, FS3,8, G3,8, A3,2,
  G3,4, B3,8, A3,8, G3,4, FS3,8, E3,8, 
  FS3,4, D3,8, E3,8, FS3,8, G3,8, A3,8, B3,8,

  G3,4, B3,8, A3,8, B3,4, CS4,8, D4,8,
  A3,8, B3,8, CS4,8, D4,8, E4,8, FS4,8, G4,8, A4,2,
  A4,4, FS4,8, G4,8, A4,4,
  FS4,8, G4,8, A4,8, A3,8, B3,8, CS4,8,
  D4,8, E4,8, FS4,8, G4,8, FS4,4, D4,8, E4,8,
  FS4,8, CS4,8, A3,8, A3,8,

  CS4,4, B3,4, D4,8, CS4,8, B3,4,
  A3,8, G3,8, A3,4, D3,8, E3,8, FS3,8, G3,8,
  A3,8, B3,4, G3,4, B3,8, A3,8, B3,4,
  CS4,8, D4,8, A3,8, B3,8, CS4,8, D4,8, E4,8,
  FS4,8, G4,8, A4,2,  
};
const int canonInDTempo = 150;

const PROGMEM int minuetInGMelody[] = {
  D5,4, G4,8, A4,8, B4,8, C5,8,
  D5,4, G4,4, G4,4,
  E5,4, C5,8, D5,8, E5,8, FS5,8,
  G5,4, G4,4, G4,4,
  C5,4, D5,8, C5,8, B4,8, A4,8,
  
  B4,4, C5,8, B4,8, A4,8, G4,8,
  FS4,4, G4,8, A4,8, B4,8, G4,8,
  A4,-2,
  D5,4, G4,8, A4,8, B4,8, C5,8, 
  D5,4, G4,4, G4,4,
  E5,4, C5,8, D5,8, E5,8, FS5,8,
  
  G5,4, G4,4, G4,4,
  C5,4, D5,8, C5,8, B4,8, A4,8,
  B4,4, C5,8, B4,8, A4,8, G4,8,
  A4,4, B4,8, A4,8, G4,8, FS4,8,
  G4,-2,

  D5,4, G4,8, A4,8, B4,8, C5,8,
  D5,4, G4,4, G4,4,
  E5,4, C5,8, D5,8, E5,8, FS5,8,
  G5,4, G4,4, G4,4,
  C5,4, D5,8, C5,8, B4,8, A4,8,
  
  B4,4, C5,8, B4,8, A4,8, G4,8,
  FS4,4, G4,8, A4,8, B4,8, G4,8,
  A4,-2,
  D5,4, G4,8, A4,8, B4,8, C5,8, 
  D5,4, G4,4, G4,4,
  E5,4, C5,8, D5,8, E5,8, FS5,8,
  
  G5,4, G4,4, G4,4,
  C5,4, D5,8, C5,8, B4,8, A4,8,
  B4,4, C5,8, B4,8, A4,8, G4,8,
  A4,4, B4,8, A4,8, G4,8, FS4,8,
  G4,-2,

  B5,4, G5,8, A5,8, B5,8, G5,8,
  A5,4, D5,8, E5,8, FS5,8, D5,8,
  G5,4, E5,8, FS5,8, G5,8, D5,8,
  CS5,4, B4,8, CS5,8, A4,4,
  A4,8, B4,8, CS5,8, D5,8, E5,8, FS5,8,

  G5,4, FS5,4, E5,4,
  FS5,4, A4,4, CS5,4,
  D5,-2,
  D5,4, G4,8, FS5,8, G4,4,
  E5,4,  G4,8, FS4,8, G4,4,
  D5,4, C5,4, B4,4,

  A4,8, G4,8, FS4,8, G4,8, A4,4,
  D4,8, E4,8, FS4,8, G4,8, A4,8, B4,8,
  C5,4, B4,4, A4,4,
  B4,8, D5,8, G4,4, FS4,4,
  G4,-2,
};
const int minuetInDTempo = 140;

const int* melodies[] = {
  tetrisMelody, zeldaMelody, neverGonneGiveYouUpMelody, starWarsMelody, miiChannelMelody, canonInDMelody, minuetInGMelody
};
const int tempos[] = {
  tetrisTempo, zeldaTempo, neverGonnaGiveYouUpTempo, starWarsTempo, miiChannelTempo, canonInDTempo, minuetInDTempo
};
const int musicNotes[] = {99, 110, 311, 88, 286, 124, 190}; 

// Misc Vars
int currentTrack = 0;
int currentNote = 0;
long musicDivider = 0;
long noteDuration = 0;
long wholenote = (60000 * 4) / tempos[currentTrack];

long score = 0;
long scoreAddition = 0;
int state = 0;
int difficulty = 0;
bool clockwise = true;

int currentLed = 0;
long currentTime = 0;
int targetLed = random(6, 27);
int targetLedS = targetLed + 1;

byte startState = LOW;
byte lastStartState = LOW;
byte interactState = LOW;
byte lastInteractState = LOW;

long gameRunLR = 0;
long musicPlayLR = 0;
int convertResult[4] = {0, 0, 0, 0};
int scoreResult[4] = {0, 0, 0, 0};

long currentPitch = 0;

// Resets state variables for a fresh game
void resetGame() {
  score = 0;
  clockwise = true;

  currentLed = 0;

  targetLed = random(8, 27);
  targetLedS = targetLed + 1;
}

// reset music state
void resetMusic() {
  musicDivider = 0;
  noteDuration = 0;
  wholenote = (60000 * 4) / tempos[currentTrack];
  currentNote = 0;
  currentTrack++;
  currentTrack %= 7;
}

void advanceGame() {
  state++;
}

// Setup for starting LED screen and pin output.
void setup() {
  Serial.begin(9600); // delete this after debugging
  for (int i = 0; i < 4; i++) {
    pinMode(dataPins[i], OUTPUT);
    pinMode(latchPins[i], OUTPUT);
    pinMode(clockPins[i], OUTPUT);
  }
  pinMode(startPin, INPUT);
  pinMode(interactPin, INPUT);
  pinMode(speakerPin, OUTPUT);

  randomSeed(analogRead(seedPin));
  renderDifficulty();
}

void playMusic() {
  if (currentTime - musicPlayLR >= noteDuration) {
    // stop any tones
    // calculates the duration of each note
    musicDivider = pgm_read_word(&melodies[currentTrack][currentNote + 1]);
    if (musicDivider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / musicDivider;
    } else if (musicDivider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(musicDivider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    currentPitch = pgm_read_word(&melodies[currentTrack][currentNote]);

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(speakerPin, currentPitch, noteDuration * 0.9);

    musicPlayLR = currentTime;
    currentNote += 2;

    // we can avoid race conditions since it's single core
    if (currentNote / 2 >= musicNotes[currentTrack]) {
      resetMusic();
    }
  }
}

// Just generates new values for targets a minimum of 5 leds away.
void generateTargets(int current) {
  targetLed = random(current + 5, current + 24) % 28;
  if (clockwise) {
    targetLedS = (targetLed + 1) % 28;
  } else {
    targetLedS = (targetLed + 27) % 28;
  }
}

// Custom power function that starts from power 1 instead of 0.
int customPower(int exponent) {
  int result = 2;
  for (int i = 0; i < exponent; i++) {
    result *= 2;
  }
  return result;
}

// Returning pointer to array of 4 results used to convert LED positions.
int* convert(int* leds) {
  int binary[4][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
  };

  for (int i = 0; i <= sizeof(leds) / sizeof(leds[0]) + 2; i++) {
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

// Essentially daisy chaining a 28 bit output
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

// Display data through a bitshifter
void displayBitShifter(byte dataOut, int bitShifter) {
  // Set latchPin low to allow data flow
  digitalWrite(latchPins[bitShifter], LOW);
  // Shift out 8 bits LSB first, on rising edge of clock
  bool pinState;
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
  // Set latchPin to high to lock and send data
  digitalWrite(latchPins[bitShifter], HIGH);
}

void displayScore() {
  int* converted = scoreConvert(score);

  for (int i = 0; i < 4; i++) {
    displayBitShifter(converted[i], i);
  }
}

// Specific rendering for difficulty at the start of the game.  
void renderDifficulty() {
  int base = difficulty * 4;
  int toConvert[] = {base, base + 1, base + 2, base + 3};

  int* converted = convert(toConvert);

  for (int i = 0; i < 4; i++) {
    displayBitShifter(converted[i], i);
  }
}

// Game Main Menu Function
void gameMain() {
  if (!lastInteractState && interactState) {
    difficulty++;
    difficulty %= 7;
    renderDifficulty();
  }
  if (!lastStartState && startState) {
    advanceGame();
  }
}

// Game run iteration func
void gameRun() {
  if (currentTime - gameRunLR >= speeds[difficulty] - score) {   
    int toConvert[] = {currentLed, targetLed, targetLedS};
    int* converted = convert(toConvert);

    for (int i = 0; i < 4; i++) {
      displayBitShifter(converted[i], i);
    }

    if (clockwise) {
      currentLed++;
    } else {
      currentLed += 27;
    }
    currentLed %= 28;

    if (clockwise && currentLed == (targetLedS + 1) % 28 || !clockwise && currentLed == (targetLedS + 27) % 28) {
      advanceGame();
      score *= difficulty;
      displayScore();
      return;
    }

    gameRunLR = currentTime;
  }

  if (!lastInteractState && interactState) {
    if (currentLed == targetLed || currentLed == targetLedS) {
      score++;
      scoreAddition++;
      clockwise = !clockwise;
      generateTargets(currentLed);
    } else {
      advanceGame();
      score *= difficulty;
      displayScore();
    }
  }
}

// Gameover score display iterator
void gameOver() {
  if (!lastStartState && startState) {
    advanceGame();
    renderDifficulty();
    resetGame();
  }
  if (!lastInteractState && interactState) {
    resetMusic();
  }
}

// Main synchronous loop
void loop() {
  currentTime = millis();

  startState = digitalRead(startPin);
  interactState = digitalRead(interactPin);

  playMusic();

  if (state == 0) {
    gameMain();
  } else if (state == 1) {
    gameRun();
  } else if (state == 2) {
    gameOver();
  } else {
    state = 0;
  }

  lastStartState = startState;
  lastInteractState = interactState;
}