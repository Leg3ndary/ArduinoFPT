/*
Pop the lock gamebox code, Copyright Leg3ndary 2023.
*/

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

const int scoreAnimationSpeed = 3000;

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

// Melodies
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

const PROGMEM int pinkPantherMelody[] = {
  REST,2, REST,4, REST,8, DS4,8, 
  E4,-4, REST,8, FS4,8, G4,-4, REST,8, DS4,8,
  E4,-8, FS4,8,  G4,-8, C5,8, B4,-8, E4,8, G4,-8, B4,8,   
  AS4,2, A4,-16, G4,-16, E4,-16, D4,-16, 
  E4,2, REST,4, REST,8, DS4,4,

  E4,-4, REST,8, FS4,8, G4,-4, REST,8, DS4,8,
  E4,-8, FS4,8,  G4,-8, C5,8, B4,-8, G4,8, B4,-8, E5,8,
  DS5,1,   
  D5,2, REST,4, REST,8, DS4,8, 
  E4,-4, REST,8, FS4,8, G4,-4, REST,8, DS4,8,
  E4,-8, FS4,8,  G4,-8, C5,8, B4,-8, E4,8, G4,-8, B4,8,   
  
  AS4,2, A4,-16, G4,-16, E4,-16, D4,-16, 
  E4,-4, REST,4,
  REST,4, E5,-8, D5,8, B4,-8, A4,8, G4,-8, E4,-8,
  AS4,16, A4,-8, AS4,16, A4,-8, AS4,16, A4,-8, AS4,16, A4,-8,   
  G4,-16, E4,-16, D4,-16, E4,16, E4,16, E4,2,
 
};
const int pinkPantherTempo = 160;

const PROGMEM int neverGonneGiveYouUpMelody[] = {
  D5,-4, E5,-4, A4,4, //1
  E5,-4, FS5,-4, A5,16, G5,16, FS5,8,
  D5,-4, E5,-4, A4,2,
  A4,16, A4,16, B4,16, D5,8, D5,16,
  D5,-4, E5,-4, A4,4, //repeat from 1
  E5,-4, FS5,-4, A5,16, G5,16, FS5,8,
  D5,-4, E5,-4, A4,2,
  A4,16, A4,16, B4,16, D5,8, D5,16,
  REST,4, B4,8, CS5,8, D5,8, D5,8, E5,8, CS5,-8,
  B4,16, A4,2, REST,4, 

  REST,8, B4,8, B4,8, CS5,8, D5,8, B4,4, A4,8, //7
  A5,8, REST,8, A5,8, E5,-4, REST,4, 
  B4,8, B4,8, CS5,8, D5,8, B4,8, D5,8, E5,8, REST,8,
  REST,8, CS5,8, B4,8, A4,-4, REST,4,
  REST,8, B4,8, B4,8, CS5,8, D5,8, B4,8, A4,4,
  E5,8, E5,8, E5,8, FS5,8, E5,4, REST,4,
   
  D5,2, E5,8, FS5,8, D5,8, //13
  E5,8, E5,8, E5,8, FS5,8, E5,4, A4,4,
  REST,2, B4,8, CS5,8, D5,8, B4,8,
  REST,8, E5,8, FS5,8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,

  E5,-8, E5,-8, D5,-8, CS5,16, B4,-8, A4,16, B4,16, D5,16, B4,16, //18
  D5,4, E5,8, CS5,-8, B4,16, A4,8, A4,8, A4,8, 
  E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,

  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8,  //23
  E5,4, D5,2, REST,4,
  REST,8, B4,8, D5,8, B4,8, D5,8, E5,4, REST,8,
  REST,8, CS5,8, B4,8, A4,-4, REST,4,
  REST,8, B4,8, B4,8, CS5,8, D5,8, B4,8, A4,4,
  REST,8, A5,8, A5,8, E5,8, FS5,8, E5,8, D5,8,
  
  REST,8, A4,8, B4,8, CS5,8, D5,8, B4,8, //29
  REST,8, CS5,8, B4,8, A4,-4, REST,4,
  B4,8, B4,8, CS5,8, D5,8, B4,8, A4,4, REST,8,
  REST,8, E5,8, E5,8, FS5,4, E5,-4, 
  D5,2, D5,8, E5,8, FS5,8, E5,4, 
  E5,8, E5,8, FS5,8, E5,8, A4,8, A4,4,

  REST,-4, A4,8, B4,8, CS5,8, D5,8, B4,8, //35
  REST,8, E5,8, FS5,8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  E5,-8, E5,-8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8, 

   E5,4, D5,2, A4,16, B4,16, D5,16, B4,16, //40
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16,
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8,  
  E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
   
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16, //45
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8,  
  E5,4, D5,2, A4,16, B4,16, D5,16, B4,16,
  FS5,-8, FS5,-8, E5,-4, A4,16, B4,16, D5,16, B4,16, //45
  
  A5,4, CS5,8, D5,-8, CS5,16, B4,8, A4,16, B4,16, D5,16, B4,16,
  D5,4, E5,8, CS5,-8, B4,16, A4,4, A4,8, 

  E5,4, D5,2, REST,4
};
const int neverGonnaGiveYouUpTempo = 114;

const PROGMEM int starWarsMelody[] = {
  AS4,8, AS4,8, AS4,8,//1
  F5,2, C6,2,
  AS5,8, A5,8, G5,8, F6,2, C6,4,  
  AS5,8, A5,8, G5,8, F6,2, C6,4,  
  AS5,8, A5,8, AS5,8, G5,2, C5,8, C5,8, C5,8,
  F5,2, C6,2,
  AS5,8, A5,8, G5,8, F6,2, C6,4,  
  
  AS5,8, A5,8, G5,8, F6,2, C6,4, //8  
  AS5,8, A5,8, AS5,8, G5,2, C5,-8, C5,16, 
  D5,-4, D5,8, AS5,8, A5,8, G5,8, F5,8,
  F5,8, G5,8, A5,8, G5,4, D5,8, E5,4,C5,-8, C5,16,
  D5,-4, D5,8, AS5,8, A5,8, G5,8, F5,8,
  
  C6,-8, G5,16, G5,2, REST,8, C5,8,//13
  D5,-4, D5,8, AS5,8, A5,8, G5,8, F5,8,
  F5,8, G5,8, A5,8, G5,4, D5,8, E5,4,C6,-8, C6,16,
  F6,4, DS6,8, CS6,4, C6,8, AS5,4, GS5,8, G5,4, F5,8,
  C6,1
};
const int starWarsTempo = 150;

const PROGMEM int miiChannelMelody[] = {
  FS4,8, REST,8, A4,8, CS5,8, REST,8,A4,8, REST,8, FS4,8, //1
  D4,8, D4,8, D4,8, REST,8, REST,4, REST,8, CS4,8,
  D4,8, FS4,8, A4,8, CS5,8, REST,8, A4,8, REST,8, F4,8,
  E5,-4, DS5,8, D5,8, REST,8, REST,4,
  
  GS4,8, REST,8, CS5,8, FS4,8, REST,8,CS5,8, REST,8, GS4,8, //5
  REST,8, CS5,8, G4,8, FS4,8, REST,8, E4,8, REST,8,
  E4,8, E4,8, E4,8, REST,8, REST,4, E4,8, E4,8,
  E4,8, REST,8, REST,4, DS4,8, D4,8, 

  CS4,8, REST,8, A4,8, CS5,8, REST,8,A4,8, REST,8, FS4,8, //9
  D4,8, D4,8, D4,8, REST,8, E5,8, E5,8, E5,8, REST,8,
  REST,8, FS4,8, A4,8, CS5,8, REST,8, A4,8, REST,8, F4,8,
  E5,2, D5,8, REST,8, REST,4,

  B4,8, G4,8, D4,8, CS4,4, B4,8, G4,8, CS4,8, //13
  A4,8, FS4,8, C4,8, B3,4, F4,8, D4,8, B3,8,
  E4,8, E4,8, E4,8, REST,4, REST,4, AS4,4,
  CS5,8, D5,8, FS5,8, A5,8, REST,8, REST,4, 

  REST,2, A3,4, AS3,4, //17 
  A3,-4, A3,8, A3,2,
  REST,4, A3,8, AS3,8, A3,8, F4,4, C4,8,
  A3,-4, A3,8, A3,2,

  REST,2, B3,4, C4,4, //21
  CS4,-4, C4,8, CS4,2,
  REST,4, CS4,8, C4,8, CS4,8, GS4,4, DS4,8,
  CS4,-4, DS4,8, B3,1,
  
  E4,4, E4,4, E4,4, REST,8,//25

  FS4,8, REST,8, A4,8, CS5,8, REST,8,A4,8, REST,8, FS4,8, //1
  D4,8, D4,8, D4,8, REST,8, REST,4, REST,8, CS4,8,
  D4,8, FS4,8, A4,8, CS5,8, REST,8, A4,8, REST,8, F4,8,
  E5,-4, DS5,8, D5,8, REST,8, REST,4,
  
  GS4,8, REST,8, CS5,8, FS4,8, REST,8,CS5,8, REST,8, GS4,8, //5
  REST,8, CS5,8, G4,8, FS4,8, REST,8, E4,8, REST,8,
  E4,8, E4,8, E4,8, REST,8, REST,4, E4,8, E4,8,
  E4,8, REST,8, REST,4, DS4,8, D4,8, 

  CS4,8, REST,8, A4,8, CS5,8, REST,8,A4,8, REST,8, FS4,8, //9
  D4,8, D4,8, D4,8, REST,8, E5,8, E5,8, E5,8, REST,8,
  REST,8, FS4,8, A4,8, CS5,8, REST,8, A4,8, REST,8, F4,8,
  E5,2, D5,8, REST,8, REST,4,

  B4,8, G4,8, D4,8, CS4,4, B4,8, G4,8, CS4,8, //13
  A4,8, FS4,8, C4,8, B3,4, F4,8, D4,8, B3,8,
  E4,8, E4,8, E4,8, REST,4, REST,4, AS4,4,
  CS5,8, D5,8, FS5,8, A5,8, REST,8, REST,4, 

  REST,2, A3,4, AS3,4, //17 
  A3,-4, A3,8, A3,2,
  REST,4, A3,8, AS3,8, A3,8, F4,4, C4,8,
  A3,-4, A3,8, A3,2,

  REST,2, B3,4, C4,4, //21
  CS4,-4, C4,8, CS4,2,
  REST,4, CS4,8, C4,8, CS4,8, GS4,4, DS4,8,
  CS4,-4, DS4,8, B3,1,
  
  E4,4, E4,4, E4,4, REST,8,//25
};
const int miiChannelTempo = 154;

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
const int canonInDTempo = 140;

const PROGMEM int minuetInGMelody[] = {
  D5,4, G4,8, A4,8, B4,8, C5,8, //1
  D5,4, G4,4, G4,4,
  E5,4, C5,8, D5,8, E5,8, FS5,8,
  G5,4, G4,4, G4,4,
  C5,4, D5,8, C5,8, B4,8, A4,8,
  
  B4,4, C5,8, B4,8, A4,8, G4,8,//6
  FS4,4, G4,8, A4,8, B4,8, G4,8,
  A4,-2,
  D5,4, G4,8, A4,8, B4,8, C5,8, 
  D5,4, G4,4, G4,4,
  E5,4, C5,8, D5,8, E5,8, FS5,8,
  
  G5,4, G4,4, G4,4,
  C5,4, D5,8, C5,8, B4,8, A4,8, //12
  B4,4, C5,8, B4,8, A4,8, G4,8,
  A4,4, B4,8, A4,8, G4,8, FS4,8,
  G4,-2,

  D5,4, G4,8, A4,8, B4,8, C5,8, //1
  D5,4, G4,4, G4,4,
  E5,4, C5,8, D5,8, E5,8, FS5,8,
  G5,4, G4,4, G4,4,
  C5,4, D5,8, C5,8, B4,8, A4,8,
  
  B4,4, C5,8, B4,8, A4,8, G4,8,//6
  FS4,4, G4,8, A4,8, B4,8, G4,8,
  A4,-2,
  D5,4, G4,8, A4,8, B4,8, C5,8, 
  D5,4, G4,4, G4,4,
  E5,4, C5,8, D5,8, E5,8, FS5,8,
  
  G5,4, G4,4, G4,4,
  C5,4, D5,8, C5,8, B4,8, A4,8, //12
  B4,4, C5,8, B4,8, A4,8, G4,8,
  A4,4, B4,8, A4,8, G4,8, FS4,8,
  G4,-2,

  B5,4, G5,8, A5,8, B5,8, G5,8,//17
  A5,4, D5,8, E5,8, FS5,8, D5,8,
  G5,4, E5,8, FS5,8, G5,8, D5,8,
  CS5,4, B4,8, CS5,8, A4,4,
  A4,8, B4,8, CS5,8, D5,8, E5,8, FS5,8,

  G5,4, FS5,4, E5,4, //22
  FS5,4, A4,4, CS5,4,
  D5,-2,
  D5,4, G4,8, FS5,8, G4,4,
  E5,4,  G4,8, FS4,8, G4,4,
  D5,4, C5,4, B4,4,

  A4,8, G4,8, FS4,8, G4,8, A4,4, //28
  D4,8, E4,8, FS4,8, G4,8, A4,8, B4,8,
  C5,4, B4,4, A4,4,
  B4,8, D5,8, G4,4, FS4,4,
  G4,-2,
};
const int minuetInDTempo = 180;

const int* melodies[] = {
  tetrisMelody, pinkPantherMelody, neverGonneGiveYouUpMelody, starWarsMelody, miiChannelMelody, canonInDMelody, minuetInGMelody
};
const int tempos[] = {
  tetrisTempo, pinkPantherTempo, neverGonnaGiveYouUpTempo, starWarsTempo, miiChannelTempo, canonInDTempo, minuetInDTempo
};
const int musicNotes[] = {99, 311, 311, 311, 311, 311, 311}; 

// Misc Vars
int currentMelodyTempo = 0;
int musicDivider = 0, noteDuration = 0;
int wholenote = (60000 * 4) / tempos[currentMelodyTempo];
int currentNote = 0;
int currentPitch = 0;

long score = 0;
long scoreAddition = 1;
int state = 0;
int difficulty = 0;
bool clockwise = true;

int currentLed = 0;
long currentTime = 0;

int targetLed = random(8, 27);
int targetLedS = targetLed + 1;

int startState = 0;
int lastStartState = 0;
int interactState = 0;
int lastInteractState = 0;

int gameRunLR = 0;
int musicPlayLR = 0;
int convertResult[4] = {0, 0, 0, 0};
int scoreResult[4] = {0, 0, 0, 0};

int scoreAnimationCount = 0;
int scoreAnimationDivisor = 0;

// Resets state variables for a fresh game
void resetGame() {
  score = 0;
  clockwise = true;

  currentLed = 0;

  targetLed = random(8, 27);
  targetLedS = targetLed + 1;

  scoreAnimationCount = 0;
  scoreAnimationDivisor = 0;
}

// reset music state
void resetMusic() {
  wholenote = (60000 * 4) / tempos[currentMelodyTempo];
  currentNote = 0;
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

  renderDifficulty();
  randomSeed(analogRead(seedPin));
}

void playMusic() {
  if (currentTime - musicPlayLR >= noteDuration) {
    // stop any tones
    noTone(speakerPin);
    // calculates the duration of each note
    musicDivider = pgm_read_word(melodies[currentMelodyTempo][currentNote + 1]);
    if (musicDivider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / musicDivider;
    } else if (musicDivider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(musicDivider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    currentPitch = pgm_read_word(melodies[currentMelodyTempo][currentNote]);

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(speakerPin, currentPitch, noteDuration * 0.9);

    musicPlayLR = currentTime;
    currentNote += 2;

    if (currentNote / 2 >= musicNotes[currentMelodyTempo]) {
      currentNote = 0;
    }
  }
}

// Just generates new values for targets a minimum of 5 leds away.
void generateTargets(int current) {
  targetLed = random(current + 5, current + 24) % 28;
  targetLedS = (targetLed + 1) % 28;
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

// Shift out the data to the set bitShifter
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

// Game run iteration func
void gameRun() {
  if (currentTime - gameRunLR >= speeds[difficulty] - score) {
    if (clockwise) {
      if (currentLed == (targetLedS + 1) % 28) {
        state++;
        score *= difficulty;
      }
    } else {
      if (currentLed == (targetLedS - 1) % 28) {
        state++;
        score *= difficulty;
      }
    }

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
      scoreAddition++;
      clockwise = !clockwise;
      generateTargets(currentLed);
    } else {
      state++;
      score *= difficulty;
      return;
    }
  }
}

// Gameover score display iterator
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

// Main synchronous loop
void loop() {
  currentTime = millis();
  startState = digitalRead(startPin);
  interactState = digitalRead(interactPin);

  playMusic();

  if (state == 0) {
    if (!lastInteractState && interactState) {
      difficulty++;
      difficulty %= 7;
      renderDifficulty();
    }
    if (!lastStartState && startState) {
      state++;
    }
  } else if (state == 1)
  {
    gameRun();
  } else if (state == 2) {
    gameOver();
    if (!lastStartState && startState) {
      state++;
      renderDifficulty();
      resetGame();
    }
    if (!lastInteractState && interactState) {
      currentMelodyTempo++;
      currentMelodyTempo %= 6;
      resetMusic();
    }
  } else {
    state = 0;
  }

  lastStartState = startState;
  lastInteractState = interactState;
}
