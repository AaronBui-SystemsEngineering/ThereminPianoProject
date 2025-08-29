#include "Notes.h"

const int AUDIO_PIN = 8; 
const int BUTTON_PIN = 2;
const int RESET_PIN = 3;

int buttonState = 0;
int lastButtonState = 0;

int resetState = 0;
int lastResetState = 0;

int current = 0;

int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};

float durations[] = {
  1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.5
};


void setup() {
  // for (int i = 0; i < 14; i++) {
  //   tone(AUDIO_PIN, melody[i], durations[i] * 1000);

  //   delay((durations[i] * 1000));
  // }

  noTone(AUDIO_PIN);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(RESET_PIN, INPUT);
  
}

void loop() {
  buttonState = digitalRead(BUTTON_PIN);
  resetState = digitalRead(RESET_PIN);

  if(buttonState != lastButtonState) {
    if(buttonState == HIGH) {
      tone(AUDIO_PIN, melody[current]);
      current = (current + 1) % 14;
    } else {
      noTone(AUDIO_PIN);
    }
  }

  if(resetState != lastResetState) {
    if(resetState == HIGH) {
      current = 0;
    }
  }

  lastButtonState = buttonState;
  lastResetState = resetState;

  
}