const int AUDIO_PIN = 8; 


void setup() {
  tone(AUDIO_PIN, 262, 4000);

  delay(4000);

  noTone(AUDIO_PIN);
}

void loop() {
  
}