const int start = 3;
const int led = 4;
byte ledOn = HIGH;

void setup() {
  Serial.begin(9600);

  pinMode(start, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void thingy() {
  digitalWrite(led, LOW);
  delay(500);
  digitalWrite(led, HIGH);
}

void loop() {
  Serial.println(start);
  if(digitalRead(start) == HIGH) {
    thingy();
  }
}
