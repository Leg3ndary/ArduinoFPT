// Project 12 - Melody Player https://musescore.com/user/16693/scores/38133
int speakerPin = 9;
int length = 15; // the number of notes
char notes[] = "ccggaagffeeddc "; // a space represents a rest
int beats[] = {1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4};
int tempo = 300;
long currentTime = 0;
long currentMicro = 0;
int currentNote = 0;
long musicTimeLR = 0;
long musicMicroLR = 0;
int lastNoteMicro = 0;

bool isHigh = false;
long duration = 0;
long toneMicro = 0;

void playTone(int tone, int duration) {
  // for (long i = 0; i < duration * 1000L; i += tone * 2) {
  if ()
    if (currentMicro - musicMicroLR < tone) {
      if (isHigh) {
        digitalWrite(speakerPin, LOW);
        isHigh = false;
      } else {
        digitalWrite(speakerPin, HIGH);
        isHigh = true;
      }
    }
  // }
}

void playNote(char note, int duration) {
  char names[] = {
    'c',
    'd',
    'e',
    'f',
    'g',
    'a',
    'b',
    'C'
  };
  int tones[] = {
    1915,
    1700,
    1519,
    1432,
    1275,
    1136,
    1014,
    956
  };
  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      toneMicro = 0;
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  pinMode(speakerPin, OUTPUT);
}

void gameMusic() {
  if (currentMicro - musicMicroLR + lastNoteMicro < tempo * 500) {
    if (lastNoteMicro != 0) {
      lastNoteMicro = 0;
    }
    if (notes[currentNote] == ' ') {
      lastNoteMicro = beats[currentNote] * tempo * 1000;
    } else {
      playNote(notes[currentNote], beats[currentNote] * tempo);
    }
    currentNote++;
  }
  musicMicroLR = currentMicro;
}

void loop() {
  currentMicro = micros();

  gameMusic();
}
