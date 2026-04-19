// Wire Controller Reader
// by Nicholas Zambetti [http://www.zambetti.com](http://www.zambetti.com)

// Demonstrates use of the Wire library
// Reads data from an I2C/TWI peripheral device
// Refer to the "Wire Peripheral Sender" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

// ================ PIN DEFINITIONS ================
// Status of Generation
#define GREEN_STATUS 13
#define RED_STATUS 12

// Level of power output
#define BLUE_L0 10
#define BLUE_L1 9
#define BLUE_L2 5
#define BLUE_L3 3
#define BLUE_L4 6

// Cycle through sources
#define BUTTON_L 8
#define BUTTON_R 7

// user control of power gen
#define POT_PIN A0

// another visual representation of power output
#define FAN_PIN 11


// ================ VARS ================
int buttonL_state = LOW;
int buttonR_state = LOW;
int buttonL_prevState = LOW;
int buttonR_prevState = LOW;
int buttonL_lastDebounce = 0;
int buttonR_lastDebounce = 0;
unsigned long debounceDelay = 50;

int generationLevel = 0;
bool distruptionActive = false;

void setup() {
  Serial.begin(9600);  // DEBUG

  Wire.begin();


  pinMode(GREEN_STATUS, OUTPUT);
  digitalWrite(GREEN_STATUS, HIGH);  // initialize to good status
  pinMode(RED_STATUS, OUTPUT);

  pinMode(BLUE_L0, OUTPUT);
  pinMode(BLUE_L1, OUTPUT);
  pinMode(BLUE_L2, OUTPUT);
  pinMode(BLUE_L3, OUTPUT);
  pinMode(BLUE_L4, OUTPUT);

  pinMode(BUTTON_L, INPUT_PULLUP);
  pinMode(BUTTON_R, INPUT_PULLUP);
}

void loop() {
  int potVal = analogRead(POT_PIN);
  generationLevel = map(potVal, 0, 1023, 0, 255);

  updatePowerLEDs();
  updateStatusLEDs();

  handle_L_button();
  handle_R_button();


  // digitalWrite(BLUE_L0, HIGH);
  // digitalWrite(BLUE_L1, HIGH);
  // digitalWrite(BLUE_L2, HIGH);
  // digitalWrite(BLUE_L3, HIGH);
  // digitalWrite(BLUE_L4, HIGH);
}

// update blue LED's based on potentiometer input
void updatePowerLEDs() {
  int level = generationLevel;

  analogWrite(BLUE_L0, (level > 40) ? level : 0);
  analogWrite(BLUE_L1, (level > 90) ? level : 0);
  analogWrite(BLUE_L2, (level > 140) ? level : 0);
  analogWrite(BLUE_L3, (level > 190) ? level : 0);
  analogWrite(BLUE_L4, (level > 230) ? level : 0);

  analogWrite(FAN_PIN, level);  // Fan speed follows generation
}

// update green and red LED's based on if master node send a distruption (simualted RNG)
void updateStatusLEDs() {
  if (distruptionActive) {
    digitalWrite(RED_STATUS, HIGH);
    digitalWrite(GREEN_STATUS, LOW);
  } else {
    digitalWrite(RED_STATUS, LOW);
    digitalWrite(GREEN_STATUS, HIGH);
  }
}

// handles click on right button. Action = cycle to prev energy source. Wraps around if at min.
void handle_L_button() {
  int reading = digitalRead(BUTTON_L);

  // update debounce and reset timer on state change
  if (reading != buttonL_lastDebounce) {
    buttonL_lastDebounce = millis();
  }

  // hanle jitter
  if (millis() - buttonL_lastDebounce > debounceDelay) {
    // check for press
    if (reading != buttonL_state) {
      //
      if (buttonL_state == HIGH) {
        Serial.println("[DEBUG] - button L clicked");
        // go back to previous source
      }
    }
  }
  buttonL_lastDebounce = reading;
}

// handles click on right button. Action = cycle to next energy source. Wraps around if at max.
void handle_R_button() {
  int reading = digitalRead(BUTTON_R);

  // update debounce
  if (reading != buttonR_lastDebounce) buttonR_lastDebounce = millis();

  // hanle jitter
  if (millis() - buttonR_lastDebounce > debounceDelay) {
    // check for press
    if (reading != buttonR_state) {
      //
      if (buttonR_state == HIGH) {
        Serial.println("[DEBUG] - button R clicked");
        // go to next source
      }
    }
  }
  buttonR_lastDebounce = reading;
}