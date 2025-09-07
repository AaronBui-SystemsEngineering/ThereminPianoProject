#include "Notes.h"
#include <SoftwareSerial.h>
#include <Adafruit_VS1053.h>

const int AUDIO_PIN = A4; 
const int BUTTON_PIN = A3;
const int RESET_PIN = A5;
const int BUTTON_3 = A2;

#define PATH "TRACK001.mp3"
#define MP3_CS   6   
#define MP3_DCS  7   
#define DREQ     2   
#define SD_CS    9

int buttonState = 0;
int lastButtonState = 0;

int resetState = 0;
int lastResetState = 0;

int audioPlayButtonState = 0;
int lastAudioPlayButtonState = 0;

int current = 0;

int melody[] = {
  NOTE_C4, NOTE_C4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4, NOTE_C4
};

float durations[] = {
  1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.5
};

Adafruit_VS1053_FilePlayer music = Adafruit_VS1053_FilePlayer(
  8, 6, 7, 2, 9
);

void setup() {
  // for (int i = 0; i < 14; i++) {
  //   tone(AUDIO_PIN, melody[i], durations[i] * 1000);

  //   delay((durations[i] * 1000));
  // }

  noTone(AUDIO_PIN);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(RESET_PIN, INPUT);
  pinMode(BUTTON_3, INPUT);

  Serial.begin(9600);

  if(!music.begin()) {
    Serial.println("cant initialise the thing");
    while(true);
  }

  if(!SD.begin(9)) {
    Serial.println("cant initialise sd because no sd card or wrong pin");
    while(true);
  }

  music.setVolume(10, 10);

  if(!SD.exists(PATH)) {
    Serial.println("Audio file does not exist!!!");
    while(true);
  }

  File root = SD.open("/");

  // Serial.println("Files inside the SD card are:");

  // printDirectory(root, 0);

  music.startPlayingFile(PATH);
}

void loop() {
  if(music.playingMusic) {
    return;
  }

  buttonState = digitalRead(BUTTON_PIN);
  resetState = digitalRead(RESET_PIN);
  audioPlayButtonState = digitalRead(BUTTON_3);

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

  if(audioPlayButtonState != lastAudioPlayButtonState) {
    if(audioPlayButtonState == HIGH && !music.playingMusic) {
      Serial.println("Playing sound");
      Serial.println(digitalRead(13));
      music.startPlayingFile(PATH);
    }
  }

  lastButtonState = buttonState;
  lastResetState = resetState;
  lastAudioPlayButtonState = audioPlayButtonState;
}

void printDirectory(File dir, int numTabs) {

  while (true) {

    File entry =  dir.openNextFile();

    if (! entry) {

      // no more files

      break;

    }

    for (uint8_t i = 0; i < numTabs; i++) {

      Serial.print('\t');

    }

    Serial.print(entry.name());

    if (entry.isDirectory()) {

      Serial.println("/");

      printDirectory(entry, numTabs + 1);

    } else {

      // files have sizes, directories do not

      Serial.print("\t\t");

      Serial.println(entry.size(), DEC);

    }

    entry.close();

  }
}