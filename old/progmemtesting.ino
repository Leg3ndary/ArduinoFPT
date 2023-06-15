const int int_array[] PROGMEM = {0, 1, 2, 3, 4};
const int numElements = sizeof(int_array) / sizeof(int_array[0]);

void setup() {
  int readValue;
  Serial.begin(9600);


  for (int i = 0; i < numElements; i++)
  {
    readValue = pgm_read_word(&int_array[i]);
    Serial.println(readValue);
  }
  Serial.println("Done");
}

void loop() {}