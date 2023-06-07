/*
speaker1 is meant for the main melody and rythm
speaker2 is meant for the beat and to create harmony

The defines are all macros meant ot make the code look neater, these are all preprocessed before compile time.
*/
#define RE 0
#define GS2 104
#define A2 110
#define B2 123
#define C3 131
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define GS3 208
#define A3 220
#define B3 247
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define GS4 415
#define A4 440  
#define B4 494
#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define A5 880

const int speaker = 19;

/*
Music related stuff
*/
// Tempo is how fast it's going, it should run at around 140 BPM but to make doing eigth notes easier we set a tempo of 70
const int tempo = 140;
int tetrisMelody[] = {E5,E5,B4,C5,D5,C5,B4,A4,A4,C5,E5,D5,C5};
int tetrisMBeats[] = {2, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1};

void playTone(int speaker, int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speaker, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speaker, LOW);
    delayMicroseconds(tone);
  }
}

void setup() {
  pinMode(speaker, OUTPUT);
}

void loop() {
  for (int i = 0; i < sizeof(tetrisMelody) / sizeof(tetrisMelody[0]); i++) {
    if (tetrisMelody[i] == 0) {
      delay(tempo);
    } else {
      playTone(speaker, tetrisMelody[i], tempo);
    }
    delay(tempo / 4);
  }
}