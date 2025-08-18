#include <arduino.h>
#include <math.h>
#include "Notes.h"

//Constants
const int TRIGGER_PIN = 2;
const int ECHO_PIN = 3;
const int LED_PIN = 10;
const int LED_PIN_2 = 9;
const int LED_PIN_3 = 6;

const int TRIGGER_PIN_2 = 5;
const int ECHO_PIN_2 = 4; 

const int SPEAKER_PIN = 7;

//Variables
float duration, distance;
float duration2, distance2;

int testMelody[] = {
  NOTE_A4
};

//Built-in Functions
void setup() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(TRIGGER_PIN_2, OUTPUT);
  pinMode(ECHO_PIN_2, INPUT);

  pinMode(SPEAKER_PIN, OUTPUT);

  Serial.begin(9600);
  }

 void loop() {

  digitalWrite(TRIGGER_PIN, LOW);

  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN, HIGH);

  delayMicroseconds(10);

  digitalWrite(TRIGGER_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);

  delay(50);

  digitalWrite(TRIGGER_PIN_2, LOW);

  delayMicroseconds(2);

  digitalWrite(TRIGGER_PIN_2, HIGH);

  delayMicroseconds(10);

  digitalWrite(TRIGGER_PIN_2, LOW);

  duration2 = pulseIn(ECHO_PIN_2, HIGH);
  
//  Serial.println("Duration 2: " + (String)duration2);
//  Serial.println("Duration 1: " + (String)duration);

  distance2 = (duration2*0.0343f) / 2.0f;
  Serial.println("Distance 2: " + (String)distance2);
  distance = ((duration*0.0343f) / 2.0f);

//  Serial.println(distance);

  if(300.0f > distance && distance > 40.0f) {
    analogWrite(LED_PIN, (byte)0);
  } else {
    analogWrite(LED_PIN, calculateBrightness());
  }

  if(300.0f > distance && distance > 50.0f) {
    analogWrite(LED_PIN_2, (byte)0);
  } else {
    analogWrite(LED_PIN_2, calculateBrightness());
  }

  if(300.0f > distance && distance > 60.0f) {
    analogWrite(LED_PIN_3, (byte)0);
   
    tone(SPEAKER_PIN, NOTE_C4);
  } else {
    analogWrite(LED_PIN_3, calculateBrightness());
     noTone(NOTE_C4);
    
  }

  delay(100);
}

byte calculateBrightness() {
  Serial.println("Brightness: " + (String)constrain((255.0f * (1 - (distance2 / 60.0f))), 0, 255));

  // return (byte)constrain((255.0f * (1 - (distance2 / 60.0f))), 0, 255);

  return (byte)constrain( (255.0f / logb(1.0f / 255.0f, 255.0f) ) * logb((distance2 + 1) / 61.0f, 255.0f), 0.0f, 255.0f);
}

float logb(float number, float base) {
  return (float)log10(number) / (float)log10(base);
}

float calculateDuration(float seconds) {
  return 1000 / seconds;
}
