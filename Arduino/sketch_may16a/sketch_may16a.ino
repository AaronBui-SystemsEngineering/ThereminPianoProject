#include "Notes.h"

const int AUDIO_PIN = 8; 

int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};

int durations[] = {
  1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 3
};


void setup() {
  for (int i = 0; i < 14; i++) {
    tone(AUDIO_PIN, melody[i], durations[i] * 1000);

    delay((durations[i] * 1000));
  }

  noTone(AUDIO_PIN);
  
}

void loop() {
  
}