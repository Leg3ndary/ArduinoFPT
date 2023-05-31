const int start = 3;
const int interact = 2;
const int led = 4;
volatile byte ledOn = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(start, INPUT_PULLUP);
  pinMode(led, OUTPUT);
//   pinMode(interact, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(start), startISR, CHANGE);
//   attachInterrupt(digitalPinToInterrupt(interact), interactISR, CHANGE);
}

void startISR() {
  Serial.println(ledOn);
  if(ledOn == HIGH) {
    ledOn == LOW;
  } else {
    ledOn == HIGH;
  }
}


void loop() {
    digitalWrite(led, ledOn);
    delay(10);
}
