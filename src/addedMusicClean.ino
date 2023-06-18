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

const long dataPins[4] = {13, 10, 7, 4};
const long latchPins[4] = {12, 9, 6, 3};
const long clockPins[4] = {11, 8, 5, 2};
const long startPin = 14;
const long longeractPin = 15;
const long seedPin = 18;
const long speakerPin = 19;

const long speeds[7] = {150, 120, 95, 75, 60, 50, 40};

const PROGMEM long tetrisMelody[] = {E5,4,B4,8,C5,8,D5,4,C5,8,B4,8,A4,4,A4,8,C5,8,E5,4,D5,8,C5,8,B4,-4,C5,8,D5,4,E5,4,C5,4,A4,4,A4,8,A4,4,B4,8,C5,8,D5,-4,F5,8,A5,4,G5,8,F5,8,E5,-4,C5,8,E5,4,D5,8,C5,8,B4,4,B4,8,C5,8,D5,4,E5,4,C5,4,A4,4,A4,4,REST,4,E5,4,B4,8,C5,8,D5,4,C5,8,B4,8,A4,4,A4,8,C5,8,E5,4,D5,8,C5,8,B4,-4,C5,8,D5,4,E5,4,C5,4,A4,4,A4,8,A4,4,B4,8,C5,8,D5,-4,F5,8,A5,4,G5,8,F5,8,E5,-4,C5,8,E5,4,D5,8,C5,8,B4,4,B4,8,C5,8,D5,4,E5,4,C5,4,A4,4,A4,4,REST,4,E5,2,C5,2,D5,2,B4,2,C5,2,A4,2,GS4,2,B4,4,REST,8,E5,2,C5,2,D5,2,B4,2,C5,4,E5,4,A5,2,GS5,2};
const long tetrisTempo = 144;

const PROGMEM long zeldaMelody[] = {AS4,-2,F4,8,F4,8,AS4,8,GS4,16,FS4,16,GS4,-2,AS4,-2,FS4,8,FS4,8,AS4,8,A4,16,G4,16,A4,-2,REST,1,AS4,4,F4,-4,AS4,8,AS4,16,C5,16,D5,16,DS5,16,F5,2,F5,8,F5,8,F5,8,FS5,16,GS5,16,AS5,-2,AS5,8,AS5,8,GS5,8,FS5,16,GS5,-8,FS5,16,F5,2,F5,4,DS5,-8,F5,16,FS5,2,F5,8,DS5,8,CS5,-8,DS5,16,F5,2,DS5,8,CS5,8,C5,-8,D5,16,E5,2,G5,8,F5,16,F4,16,F4,16,F4,16,F4,16,F4,16,F4,16,F4,16,F4,8,F4,16,F4,8,AS4,4,F4,-4,AS4,8,AS4,16,C5,16,D5,16,DS5,16,F5,2,F5,8,F5,8,F5,8,FS5,16,GS5,16,AS5,-2,CS6,4,C6,4,A5,2,F5,4,FS5,-2,AS5,4,A5,4,F5,2,F5,4,FS5,-2,AS5,4,A5,4,F5,2,D5,4,DS5,-2,FS5,4,F5,4,CS5,2,AS4,4,C5,-8,D5,16,E5,2,G5,8,F5,16,F4,16,F4,16,F4,16,F4,16,F4,16,F4,16,F4,16,F4,8,F4,16,F4,8};
const long zeldaTempo = 88;

const PROGMEM long neverGonneGiveYouUpMelody[] = {D5,-4,E5,-4,A4,4,E5,-4,FS5,-4,A5,16,G5,16,FS5,8,D5,-4,E5,-4,A4,2,A4,16,A4,16,B4,16,D5,8,D5,16,D5,-4,E5,-4,A4,4,E5,-4,FS5,-4,A5,16,G5,16,FS5,8,D5,-4,E5,-4,A4,2,A4,16,A4,16,B4,16,D5,8,D5,16,REST,4,B4,8,CS5,8,D5,8,D5,8,E5,8,CS5,-8,B4,16,A4,2,REST,4,REST,8,B4,8,B4,8,CS5,8,D5,8,B4,4,A4,8,A5,8,REST,8,A5,8,E5,-4,REST,4,B4,8,B4,8,CS5,8,D5,8,B4,8,D5,8,E5,8,REST,8,REST,8,CS5,8,B4,8,A4,-4,REST,4,REST,8,B4,8,B4,8,CS5,8,D5,8,B4,8,A4,4,E5,8,E5,8,E5,8,FS5,8,E5,4,REST,4,D5,2,E5,8,FS5,8,D5,8,E5,8,E5,8,E5,8,FS5,8,E5,4,A4,4,REST,2,B4,8,CS5,8,D5,8,B4,8,REST,8,E5,8,FS5,8,E5,-4,A4,16,B4,16,D5,16,B4,16,FS5,-8,FS5,-8,E5,-4,A4,16,B4,16,D5,16,B4,16,E5,-8,E5,-8,D5,-8,CS5,16,B4,-8,A4,16,B4,16,D5,16,B4,16,D5,4,E5,8,CS5,-8,B4,16,A4,8,A4,8,A4,8,E5,4,D5,2,A4,16,B4,16,D5,16,B4,16,FS5,-8,FS5,-8,E5,-4,A4,16,B4,16,D5,16,B4,16,A5,4,CS5,8,D5,-8,CS5,16,B4,8,A4,16,B4,16,D5,16,B4,16,D5,4,E5,8,CS5,-8,B4,16,A4,4,A4,8,E5,4,D5,2,REST,4,REST,8,B4,8,D5,8,B4,8,D5,8,E5,4,REST,8,REST,8,CS5,8,B4,8,A4,-4,REST,4,REST,8,B4,8,B4,8,CS5,8,D5,8,B4,8,A4,4,REST,8,A5,8,A5,8,E5,8,FS5,8,E5,8,D5,8,REST,8,A4,8,B4,8,CS5,8,D5,8,B4,8,REST,8,CS5,8,B4,8,A4,-4,REST,4,B4,8,B4,8,CS5,8,D5,8,B4,8,A4,4,REST,8,REST,8,E5,8,E5,8,FS5,4,E5,-4,D5,2,D5,8,E5,8,FS5,8,E5,4,E5,8,E5,8,FS5,8,E5,8,A4,8,A4,4,REST,-4,A4,8,B4,8,CS5,8,D5,8,B4,8,REST,8,E5,8,FS5,8,E5,-4,A4,16,B4,16,D5,16,B4,16,FS5,-8,FS5,-8,E5,-4,A4,16,B4,16,D5,16,B4,16,E5,-8,E5,-8,D5,-8,CS5,16,B4,8,A4,16,B4,16,D5,16,B4,16,D5,4,E5,8,CS5,-8,B4,16,A4,4,A4,8,E5,4,D5,2,A4,16,B4,16,D5,16,B4,16,FS5,-8,FS5,-8,E5,-4,A4,16,B4,16,D5,16,B4,16,A5,4,CS5,8,D5,-8,CS5,16,B4,8,A4,16,B4,16,D5,16,B4,16,D5,4,E5,8,CS5,-8,B4,16,A4,4,A4,8,E5,4,D5,2,A4,16,B4,16,D5,16,B4,16,FS5,-8,FS5,-8,E5,-4,A4,16,B4,16,D5,16,B4,16,A5,4,CS5,8,D5,-8,CS5,16,B4,8,A4,16,B4,16,D5,16,B4,16,D5,4,E5,8,CS5,-8,B4,16,A4,4,A4,8,E5,4,D5,2,A4,16,B4,16,D5,16,B4,16,FS5,-8,FS5,-8,E5,-4,A4,16,B4,16,D5,16,B4,16,A5,4,CS5,8,D5,-8,CS5,16,B4,8,A4,16,B4,16,D5,16,B4,16,D5,4,E5,8,CS5,-8,B4,16,A4,4,A4,8,E5,4,D5,2,REST,4};
const long neverGonnaGiveYouUpTempo = 144;

const PROGMEM long starWarsMelody[] = {AS4,8,AS4,8,AS4,8,F5,2,C6,2,AS5,8,A5,8,G5,8,F6,2,C6,4,AS5,8,A5,8,G5,8,F6,2,C6,4,AS5,8,A5,8,AS5,8,G5,2,C5,8,C5,8,C5,8,F5,2,C6,2,AS5,8,A5,8,G5,8,F6,2,C6,4,AS5,8,A5,8,G5,8,F6,2,C6,4,AS5,8,A5,8,AS5,8,G5,2,C5,-8,C5,16,D5,-4,D5,8,AS5,8,A5,8,G5,8,F5,8,F5,8,G5,8,A5,8,G5,4,D5,8,E5,4,C5,-8,C5,16,D5,-4,D5,8,AS5,8,A5,8,G5,8,F5,8,C6,-8,G5,16,G5,2,REST,8,C5,8,D5,-4,D5,8,AS5,8,A5,8,G5,8,F5,8,F5,8,G5,8,A5,8,G5,4,D5,8,E5,4,C6,-8,C6,16,F6,4,DS6,8,CS6,4,C6,8,AS5,4,GS5,8,G5,4,F5,8,C6,1};
const long starWarsTempo = 108;

const PROGMEM long miiChannelMelody[] = {FS4,8,REST,8,A4,8,CS5,8,REST,8,A4,8,REST,8,FS4,8,D4,8,D4,8,D4,8,REST,8,REST,4,REST,8,CS4,8,D4,8,FS4,8,A4,8,CS5,8,REST,8,A4,8,REST,8,F4,8,E5,-4,DS5,8,D5,8,REST,8,REST,4,GS4,8,REST,8,CS5,8,FS4,8,REST,8,CS5,8,REST,8,GS4,8,REST,8,CS5,8,G4,8,FS4,8,REST,8,E4,8,REST,8,E4,8,E4,8,E4,8,REST,8,REST,4,E4,8,E4,8,E4,8,REST,8,REST,4,DS4,8,D4,8,CS4,8,REST,8,A4,8,CS5,8,REST,8,A4,8,REST,8,FS4,8,D4,8,D4,8,D4,8,REST,8,E5,8,E5,8,E5,8,REST,8,REST,8,FS4,8,A4,8,CS5,8,REST,8,A4,8,REST,8,F4,8,E5,2,D5,8,REST,8,REST,4,B4,8,G4,8,D4,8,CS4,4,B4,8,G4,8,CS4,8,A4,8,FS4,8,C4,8,B3,4,F4,8,D4,8,B3,8,E4,8,E4,8,E4,8,REST,4,REST,4,AS4,4,CS5,8,D5,8,FS5,8,A5,8,REST,8,REST,4,REST,2,A3,4,AS3,4,A3,-4,A3,8,A3,2,REST,4,A3,8,AS3,8,A3,8,F4,4,C4,8,A3,-4,A3,8,A3,2,REST,2,B3,4,C4,4,CS4,-4,C4,8,CS4,2,REST,4,CS4,8,C4,8,CS4,8,GS4,4,DS4,8,CS4,-4,DS4,8,B3,1,E4,4,E4,4,E4,4,REST,8,FS4,8,REST,8,A4,8,CS5,8,REST,8,A4,8,REST,8,FS4,8,D4,8,D4,8,D4,8,REST,8,REST,4,REST,8,CS4,8,D4,8,FS4,8,A4,8,CS5,8,REST,8,A4,8,REST,8,F4,8,E5,-4,DS5,8,D5,8,REST,8,REST,4,GS4,8,REST,8,CS5,8,FS4,8,REST,8,CS5,8,REST,8,GS4,8,REST,8,CS5,8,G4,8,FS4,8,REST,8,E4,8,REST,8,E4,8,E4,8,E4,8,REST,8,REST,4,E4,8,E4,8,E4,8,REST,8,REST,4,DS4,8,D4,8,CS4,8,REST,8,A4,8,CS5,8,REST,8,A4,8,REST,8,FS4,8,D4,8,D4,8,D4,8,REST,8,E5,8,E5,8,E5,8,REST,8,REST,8,FS4,8,A4,8,CS5,8,REST,8,A4,8,REST,8,F4,8,E5,2,D5,8,REST,8,REST,4,B4,8,G4,8,D4,8,CS4,4,B4,8,G4,8,CS4,8,A4,8,FS4,8,C4,8,B3,4,F4,8,D4,8,B3,8,E4,8,E4,8,E4,8,REST,4,REST,4,AS4,4,CS5,8,D5,8,FS5,8,A5,8,REST,8,REST,4,REST,2,A3,4,AS3,4,A3,-4,A3,8,A3,2,REST,4,A3,8,AS3,8,A3,8,F4,4,C4,8,A3,-4,A3,8,A3,2,REST,2,B3,4,C4,4,CS4,-4,C4,8,CS4,2,REST,4,CS4,8,C4,8,CS4,8,GS4,4,DS4,8,CS4,-4,DS4,8,B3,1,E4,4,E4,4,E4,4,REST,8};
const long miiChannelTempo = 114;

const PROGMEM long canonInDMelody[] = {FS4,2,E4,2,D4,2,CS4,2,B3,2,A3,2,B3,2,CS4,2,FS4,2,E4,2,D4,2,CS4,2,B3,2,A3,2,B3,2,CS4,2,D4,2,CS4,2,B3,2,A3,2,G3,2,FS3,2,G3,2,A3,2,D4,4,FS4,8,G4,8,A4,4,FS4,8,G4,8,A4,4,B3,8,CS4,8,D4,8,E4,8,FS4,8,G4,8,FS4,4,D4,8,E4,8,FS4,4,FS3,8,G3,8,A3,8,G3,8,FS3,8,G3,8,A3,2,G3,4,B3,8,A3,8,G3,4,FS3,8,E3,8,FS3,4,D3,8,E3,8,FS3,8,G3,8,A3,8,B3,8,G3,4,B3,8,A3,8,B3,4,CS4,8,D4,8,A3,8,B3,8,CS4,8,D4,8,E4,8,FS4,8,G4,8,A4,2,A4,4,FS4,8,G4,8,A4,4,FS4,8,G4,8,A4,8,A3,8,B3,8,CS4,8,D4,8,E4,8,FS4,8,G4,8,FS4,4,D4,8,E4,8,FS4,8,CS4,8,A3,8,A3,8,CS4,4,B3,4,D4,8,CS4,8,B3,4,A3,8,G3,8,A3,4,D3,8,E3,8,FS3,8,G3,8,A3,8,B3,4,G3,4,B3,8,A3,8,B3,4,CS4,8,D4,8,A3,8,B3,8,CS4,8,D4,8,E4,8,FS4,8,G4,8,A4,2};
const long canonInDTempo = 150;

const PROGMEM long minuetInGMelody[] = {D5,4,G4,8,A4,8,B4,8,C5,8,D5,4,G4,4,G4,4,E5,4,C5,8,D5,8,E5,8,FS5,8,G5,4,G4,4,G4,4,C5,4,D5,8,C5,8,B4,8,A4,8,B4,4,C5,8,B4,8,A4,8,G4,8,FS4,4,G4,8,A4,8,B4,8,G4,8,A4,-2,D5,4,G4,8,A4,8,B4,8,C5,8,D5,4,G4,4,G4,4,E5,4,C5,8,D5,8,E5,8,FS5,8,G5,4,G4,4,G4,4,C5,4,D5,8,C5,8,B4,8,A4,8,B4,4,C5,8,B4,8,A4,8,G4,8,A4,4,B4,8,A4,8,G4,8,FS4,8,G4,-2,D5,4,G4,8,A4,8,B4,8,C5,8,D5,4,G4,4,G4,4,E5,4,C5,8,D5,8,E5,8,FS5,8,G5,4,G4,4,G4,4,C5,4,D5,8,C5,8,B4,8,A4,8,B4,4,C5,8,B4,8,A4,8,G4,8,FS4,4,G4,8,A4,8,B4,8,G4,8,A4,-2,D5,4,G4,8,A4,8,B4,8,C5,8,D5,4,G4,4,G4,4,E5,4,C5,8,D5,8,E5,8,FS5,8,G5,4,G4,4,G4,4,C5,4,D5,8,C5,8,B4,8,A4,8,B4,4,C5,8,B4,8,A4,8,G4,8,A4,4,B4,8,A4,8,G4,8,FS4,8,G4,-2,B5,4,G5,8,A5,8,B5,8,G5,8,A5,4,D5,8,E5,8,FS5,8,D5,8,G5,4,E5,8,FS5,8,G5,8,D5,8,CS5,4,B4,8,CS5,8,A4,4,A4,8,B4,8,CS5,8,D5,8,E5,8,FS5,8,G5,4,FS5,4,E5,4,FS5,4,A4,4,CS5,4,D5,-2,D5,4,G4,8,FS5,8,G4,4,E5,4,G4,8,FS4,8,G4,4,D5,4,C5,4,B4,4,A4,8,G4,8,FS4,8,G4,8,A4,4,D4,8,E4,8,FS4,8,G4,8,A4,8,B4,8,C5,4,B4,4,A4,4,B4,8,D5,8,G4,4,FS4,4,G4,-2};
const long minuetInDTempo = 140;
// hello there
const PROGMEM long brahmsLullabyMelody[] = {G4,4,G4,4,AS4,-4,G4,8,G4,4,AS4,4,REST,4,G4,8,AS4,8,DS5,4,D5,-4,C5,8,C5,4,AS4,4,F4,8,G4,8,GS4,4,F4,4,F4,8,G4,8,GS4,4,REST,4,F4,8,GS4,8,D5,8,C5,8,AS4,4,D5,4,DS5,4,REST,4,DS4,8,DS4,8,DS5,2,C5,8,GS4,8,AS4,2,G4,8,DS4,8,GS4,4,AS4,4,C5,4,AS4,2,DS4,8,DS4,8,DS5,2,C5,8,GS4,8,AS4,2,G4,8,DS4,8,AS4,4,G4,4,DS4,4,DS4,2};
const long brahmsLullabyTempo = 80;

const PROGMEM long harryPotterMelody[] = {REST,2,D4,4,G4,-4,AS4,8,A4,4,G4,2,D5,4,C5,-2,A4,-2,G4,-4,AS4,8,A4,4,F4,2,GS4,4,D4,-1,D4,4,G4,-4,AS4,8,A4,4,G4,2,D5,4,F5,2,E5,4,DS5,2,B4,4,DS5,-4,D5,8,CS5,4,CS4,2,B4,4,G4,-1,AS4,4,D5,2,AS4,4,D5,2,AS4,4,DS5,2,D5,4,CS5,2,A4,4,AS4,-4,D5,8,CS5,4,CS4,2,D4,4,D5,-1,REST,4,AS4,4,D5,2,AS4,4,D5,2,AS4,4,F5,2,E5,4,DS5,2,B4,4,DS5,-4,D5,8,CS5,4,CS4,2,AS4,4,G4,-1};
const long harryPotterTempo = 144;

const PROGMEM long merryChristmasMelody[] = {C5,4,F5,4,F5,8,G5,8,F5,8,E5,8,D5,4,D5,4,D5,4,G5,4,G5,8,A5,8,G5,8,F5,8,E5,4,C5,4,C5,4,A5,4,A5,8,AS5,8,A5,8,G5,8,F5,4,D5,4,C5,8,C5,8,D5,4,G5,4,E5,4,F5,2,C5,4,F5,4,F5,8,G5,8,F5,8,E5,8,D5,4,D5,4,D5,4,G5,4,G5,8,A5,8,G5,8,F5,8,E5,4,C5,4,C5,4,A5,4,A5,8,AS5,8,A5,8,G5,8,F5,4,D5,4,C5,8,C5,8,D5,4,G5,4,E5,4,F5,2,C5,4,F5,4,F5,4,F5,4,E5,2,E5,4,F5,4,E5,4,D5,4,C5,2,A5,4,AS5,4,A5,4,G5,4,C6,4,C5,4,C5,8,C5,8,D5,4,G5,4,E5,4,F5,2,C5,4,F5,4,F5,8,G5,8,F5,8,E5,8,D5,4,D5,4,D5,4,G5,4,G5,8,A5,8,G5,8,F5,8,E5,4,C5,4,C5,4,A5,4,A5,8,AS5,8,A5,8,G5,8,F5,4,D5,4,C5,8,C5,8,D5,4,G5,4,E5,4,F5,2,C5,4,F5,4,F5,4,F5,4,E5,2,E5,4,F5,4,E5,4,D5,4,C5,2,A5,4,AS5,4,A5,4,G5,4,C6,4,C5,4,C5,8,C5,8,D5,4,G5,4,E5,4,F5,2,C5,4,F5,4,F5,8,G5,8,F5,8,E5,8,D5,4,D5,4,D5,4,G5,4,G5,8,A5,8,G5,8,F5,8,E5,4,C5,4,C5,4,A5,4,A5,8,AS5,8,A5,8,G5,8,F5,4,D5,4,C5,8,C5,8,D5,4,G5,4,E5,4,F5,2,C5,4,F5,4,F5,8,G5,8,F5,8,E5,8,D5,4,D5,4,D5,4,G5,4,G5,8,A5,8,G5,8,F5,8,E5,4,C5,4,C5,4,A5,4,A5,8,AS5,8,A5,8,G5,8,F5,4,D5,4,C5,8,C5,8,D5,4,G5,4,E5,4,F5,2,REST,4};
const long merryChristmasTempo = 140;

const PROGMEM long silentNightMelody[] = {G4,-4,A4,8,G4,4,E4,-2,G4,-4,A4,8,G4,4,E4,-2,D5,2,D5,4,B4,-2,C5,2,C5,4,G4,-2,A4,2,A4,4,C5,-4,B4,8,A4,4,G4,-4,A4,8,G4,4,E4,-2,A4,2,A4,4,C5,-4,B4,8,A4,4,G4,-4,A4,8,G4,4,E4,-2,D5,2,D5,4,F5,-4,D5,8,B4,4,C5,-2,E5,-2,C5,4,G4,4,E4,4,G4,-4,F4,8,D4,4,C4,-2,C4,-1};
const long silentNightTempo = 140;

const PROGMEM long superMarioBrosMelody[] = {E5,8,E5,8,REST,8,E5,8,REST,8,C5,8,E5,8,G5,4,REST,4,G4,8,REST,4,C5,-4,G4,8,REST,4,E4,-4,A4,4,B4,4,AS4,8,A4,4,G4,-8,E5,-8,G5,-8,A5,4,F5,8,G5,8,REST,8,E5,4,C5,8,D5,8,B4,-4,C5,-4,G4,8,REST,4,E4,-4,A4,4,B4,4,AS4,8,A4,4,G4,-8,E5,-8,G5,-8,A5,4,F5,8,G5,8,REST,8,E5,4,C5,8,D5,8,B4,-4,REST,4,G5,8,FS5,8,F5,8,DS5,4,E5,8,REST,8,GS4,8,A4,8,C4,8,REST,8,A4,8,C5,8,D5,8,REST,4,DS5,4,REST,8,D5,-4,C5,2,REST,2,REST,4,G5,8,FS5,8,F5,8,DS5,4,E5,8,REST,8,GS4,8,A4,8,C4,8,REST,8,A4,8,C5,8,D5,8,REST,4,DS5,4,REST,8,D5,-4,C5,2,REST,2,C5,8,C5,4,C5,8,REST,8,C5,8,D5,4,E5,8,C5,4,A4,8,G4,2,C5,8,C5,4,C5,8,REST,8,C5,8,D5,8,E5,8,REST,1,C5,8,C5,4,C5,8,REST,8,C5,8,D5,4,E5,8,C5,4,A4,8,G4,2,E5,8,E5,8,REST,8,E5,8,REST,8,C5,8,E5,4,G5,4,REST,4,G4,4,REST,4,C5,-4,G4,8,REST,4,E4,-4,A4,4,B4,4,AS4,8,A4,4,G4,-8,E5,-8,G5,-8,A5,4,F5,8,G5,8,REST,8,E5,4,C5,8,D5,8,B4,-4,C5,-4,G4,8,REST,4,E4,-4,A4,4,B4,4,AS4,8,A4,4,G4,-8,E5,-8,G5,-8,A5,4,F5,8,G5,8,REST,8,E5,4,C5,8,D5,8,B4,-4,E5,8,C5,4,G4,8,REST,4,GS4,4,A4,8,F5,4,F5,8,A4,2,D5,-8,A5,-8,A5,-8,A5,-8,G5,-8,F5,-8,E5,8,C5,4,A4,8,G4,2,E5,8,C5,4,G4,8,REST,4,GS4,4,A4,8,F5,4,F5,8,A4,2,B4,8,F5,4,F5,8,F5,-8,E5,-8,D5,-8,C5,8,E4,4,E4,8,C4,2,E5,8,C5,4,G4,8,REST,4,GS4,4,A4,8,F5,4,F5,8,A4,2,D5,-8,A5,-8,A5,-8,A5,-8,G5,-8,F5,-8,E5,8,C5,4,A4,8,G4,2,E5,8,C5,4,G4,8,REST,4,GS4,4,A4,8,F5,4,F5,8,A4,2,B4,8,F5,4,F5,8,F5,-8,E5,-8,D5,-8,C5,8,E4,4,E4,8,C4,2,C5,8,C5,4,C5,8,REST,8,C5,8,D5,8,E5,8,REST,1,C5,8,C5,4,C5,8,REST,8,C5,8,D5,4,E5,8,C5,4,A4,8,G4,2,E5,8,E5,8,REST,8,E5,8,REST,8,C5,8,E5,4,G5,4,REST,4,G4,4,REST,4,E5,8,C5,4,G4,8,REST,4,GS4,4,A4,8,F5,4,F5,8,A4,2,D5,-8,A5,-8,A5,-8,A5,-8,G5,-8,F5,-8,E5,8,C5,4,A4,8,G4,2,E5,8,C5,4,G4,8,REST,4,GS4,4,A4,8,F5,4,F5,8,A4,2,B4,8,F5,4,F5,8,F5,-8,E5,-8,D5,-8,C5,8,E4,4,E4,8,C4,2,C5,-4,G4,-4,E4,4,A4,-8,B4,-8,A4,-8,GS4,-8,AS4,-8,GS4,-8,G4,8,D4,8,E4,-2};
const long superMarioBrosTempo = 200;

const PROGMEM long takeOnMeMelody[] = {FS5,8,FS5,8,D5,8,B4,8,REST,8,B4,8,REST,8,E5,8,REST,8,E5,8,REST,8,E5,8,GS5,8,GS5,8,A5,8,B5,8,A5,8,A5,8,A5,8,E5,8,REST,8,D5,8,REST,8,FS5,8,REST,8,FS5,8,REST,8,FS5,8,E5,8,E5,8,FS5,8,E5,8,FS5,8,FS5,8,D5,8,B4,8,REST,8,B4,8,REST,8,E5,8,REST,8,E5,8,REST,8,E5,8,GS5,8,GS5,8,A5,8,B5,8,A5,8,A5,8,A5,8,E5,8,REST,8,D5,8,REST,8,FS5,8,REST,8,FS5,8,REST,8,FS5,8,E5,8,E5,8,FS5,8,E5,8,FS5,8,FS5,8,D5,8,B4,8,REST,8,B4,8,REST,8,E5,8,REST,8,E5,8,REST,8,E5,8,GS5,8,GS5,8,A5,8,B5,8,A5,8,A5,8,A5,8,E5,8,REST,8,D5,8,REST,8,FS5,8,REST,8,FS5,8,REST,8,FS5,8,E5,8,E5,8,FS5,8,E5,8};
const long takeOnMeTempo = 140;

const long* melodies[] = {
  tetrisMelody, zeldaMelody, neverGonneGiveYouUpMelody, starWarsMelody, miiChannelMelody, canonInDMelody, minuetInGMelody, brahmsLullabyMelody, harryPotterMelody, merryChristmasMelody, silentNightMelody, superMarioBrosMelody, takeOnMeMelody
};
const long tempos[] = {
  tetrisTempo, zeldaTempo, neverGonnaGiveYouUpTempo, starWarsTempo, miiChannelTempo, canonInDTempo, minuetInDTempo, brahmsLullabyTempo, harryPotterTempo, merryChristmasTempo, silentNightTempo, superMarioBrosTempo, takeOnMeTempo
};
const long musicNotes[] = {99, 110, 311, 88, 286, 124, 190, 54, 62, 195, 47, 312, 96};

long currentTrack = 0;
long currentNote = 0;
long musicDivider = 0;
long noteDuration = 0;
long wholenote = (60000 * 4) / tempos[currentTrack];
long currentPitch = 0;

long score = 0;
long scoreAddition = 1;
long state = 0;
long difficulty = 0;
long difficultyAdjustment = 0;
bool clockwise = true;

long currentLed = 0;
long currentTime = 0;
long targetLed = random(6, 27);
long targetLedS = targetLed + 1;

byte startState = LOW;
byte lastStartState = LOW;
byte longeractState = LOW;
byte lastlongeractState = LOW;

long gameRunLR = 0;
long musicPlayLR = 0;
long convertResult[4] = {0, 0, 0, 0};
long scoreResult[4] = {0, 0, 0, 0};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(dataPins[i], OUTPUT);
    pinMode(latchPins[i], OUTPUT);
    pinMode(clockPins[i], OUTPUT);
  }
  pinMode(startPin, INPUT);
  pinMode(longeractPin, INPUT);
  pinMode(speakerPin, OUTPUT);

  randomSeed(analogRead(seedPin));
  renderDifficulty();
}

void resetGame() {
  score = 0;
  scoreAddition = (difficulty + 1) * (difficulty + 1);
  difficultyAdjustment = 0;
  clockwise = true;

  currentLed = 0;

  targetLed = random(8, 27);
  targetLedS = targetLed + 1;
}

void resetMusic() {
  musicDivider = 0;
  noteDuration = 0;
  wholenote = (60000 * 4) / tempos[currentTrack];
  currentNote = 0;
  currentPitch = 0;  

  currentTrack++;
  currentTrack %= 13;
}

void advanceGame() {
  state++;
}

void playMusic() {
  if (currentTime - musicPlayLR >= noteDuration) {
    noTone(speakerPin);
    musicDivider = pgm_read_word(&melodies[currentTrack][currentNote + 1]);

    if (musicDivider > 0) {
      noteDuration = (wholenote) / musicDivider;
    } else if (musicDivider < 0) {
      noteDuration = (wholenote) / abs(musicDivider);
      noteDuration *= 1.5;
    }

    currentPitch = pgm_read_word(&melodies[currentTrack][currentNote]);

    tone(speakerPin, currentPitch, noteDuration * 0.9);

    musicPlayLR = currentTime;
    currentNote += 2;

    if (currentNote / 2 >= musicNotes[currentTrack]) {
      resetMusic();
    }
  }
}

void generateTargets(long current) {
  targetLed = random(current + 5, current + 24) % 28;
  if (clockwise) {
    targetLedS = (targetLed + 1) % 28;
  } else {
    targetLedS = (targetLed + 27) % 28;
  }
}

long customPower(long exponent) {
  long result = 2;
  for (int i = 0; i < exponent; i++) {
    result *= 2;
  }
  return result;
}

long* convert(long* leds) {
  bool binary[4][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
  };

  for (int i = 0; i <= sizeof(leds) / sizeof(leds[0]) + 3; i++) {
    long shiftRegister = leds[i] / 7;
    long bit = leds[i] % 7;
    binary[shiftRegister][bit] = 1;
  }

  for (int i = 0; i < 4; i++) {
    long decimal = 255;
    for (long j = 0 ; j < 7 ; j++) {
      if (binary[i][j] == 0) {
        decimal -= customPower(6 - j);
      }
    }
    convertResult[i] = decimal;
  }

  return convertResult;
}

long* scoreConvert(long scoreTemp) {
  bool binary[4][7] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
  };

  long arr[24];
  long counter = 0;

  while (scoreTemp != 0) {
		arr[counter] = scoreTemp % 2;
		counter++;
		scoreTemp /= 2;
	}

  for (int i = counter - 1; i >= 0; i--) {
    if (arr[i] == 1) {
      long shiftRegister = i / 7;
      long bit = i % 7;
      binary[shiftRegister][bit] = 1;
    }
  }

  for (int i = 0; i < 4; i++) {
    long decimal = 255;
    for (long j = 0 ; j < 7 ; j++) {
      if (binary[i][j] == 0) {
        decimal -= customPower(6 - j);
      }
    }
    scoreResult[i] = decimal;
  }

  return scoreResult;
}

void displayShiftRegister(byte dataOut, long shiftRegister) {
  bool pinState;

  digitalWrite(latchPins[shiftRegister], LOW);
  digitalWrite(dataPins[shiftRegister], LOW);
  digitalWrite(clockPins[shiftRegister], LOW);

  for (int i = 0; i <= 7; i++) {
    digitalWrite(clockPins[shiftRegister], LOW);

    if (dataOut & (1 << i)) {
      pinState = HIGH;
    } else {
      pinState = LOW;
    }

    digitalWrite(dataPins[shiftRegister], pinState);
    digitalWrite(clockPins[shiftRegister], HIGH);
  }

  digitalWrite(clockPins[shiftRegister], LOW);
  digitalWrite(latchPins[shiftRegister], HIGH);
}

void displayScore() {
  long* converted = scoreConvert(score);

  for (int i = 0; i < 4; i++) {
    displayShiftRegister(converted[i], i);
  }
}

void renderDifficulty() {
  long base = difficulty * 4;
  long toConvert[] = {base, base + 1, base + 3, base + 2};
  Serial.begin(9600);
  Serial.println(base);

  long* converted = convert(toConvert);

  for (int i = 0; i < 4; i++) {
    displayShiftRegister(converted[i], i);
  }
}

void gameMain() {
  if (!lastlongeractState && longeractState) {
    difficulty++;
    difficulty %= 7;
    renderDifficulty();
  }
  if (!lastStartState && startState) {
    advanceGame();
  }
}

void gameRun() {
  if (currentTime - gameRunLR >= speeds[difficulty] - difficultyAdjustment * 1.5) {   
    long toConvert[] = {currentLed, targetLed, targetLedS};
    long* converted = convert(toConvert);

    for (int i = 0; i < 4; i++) {
      displayShiftRegister(converted[i], i);
    }

    if (clockwise) {
      currentLed++;
      currentLed %= 28;
    } else {
      currentLed += 27;
      currentLed %= 28;
    }
    

    if (clockwise && currentLed == (targetLedS + 1) % 28 || !clockwise && currentLed == (targetLedS + 27) % 28) {
      advanceGame();
      score += difficulty;
      displayScore();
      return;
    }

    gameRunLR = currentTime;
  }

  if (!lastlongeractState && longeractState) {
    if (currentLed == targetLed || currentLed == targetLedS) {
      score += scoreAddition;
      scoreAddition += difficulty;
      difficultyAdjustment++;
      clockwise = !clockwise;
      generateTargets(currentLed);
    } else {
      advanceGame();
      score += difficulty;
      displayScore();
    }
  }
}

void gameOver() {
  if (!lastStartState && startState) {
    advanceGame();
    renderDifficulty();
    resetGame();
  }
  if (!lastlongeractState && longeractState) {
    resetMusic();
  }
}

void loop() {
  currentTime = millis();

  startState = digitalRead(startPin);
  longeractState = digitalRead(longeractPin);

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
  lastlongeractState = longeractState;
}
