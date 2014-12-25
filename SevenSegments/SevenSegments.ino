
#include "pitches.h"


// LEDs and 7(+1) segment digit display via shift register
const int LED_SHIFT_DATA_PIN = 2;
const int LED_SHIFT_STORAGE_PIN = 3;
const int LED_SHIFT_SHIFT_PIN = 4;
byte DIGIT_CODES[] = { 
  0b10111110, // 0
  0b00000110, // 1
  0b01111100, // 2
  0b01011110, // 3
  0b11000110, // 4
  0b11011010, // 5
  0b11111010, // 6
  0b00001110, // 7
  0b11111110, // 8
  0b11011110  // 9
};
const byte DOT_CODE = 0b00000001;


// buttons multiplexor
const int BUTTONS_SELECTOR_BASE = 10;
const int BUTTONS_SELECTOR_0 = BUTTONS_SELECTOR_BASE;
const int BUTTONS_SELECTOR_1 = BUTTONS_SELECTOR_BASE + 1;
const int BUTTONS_SELECTOR_2 = BUTTONS_SELECTOR_BASE + 2;
const int BUTTONS_SELECTOR_3 = BUTTONS_SELECTOR_BASE + 3;
const int BUTTIONS_INPUT = A0;
const int NO_BUTTON = -1;


// tones
const int TONE_PIN = 5;
const long DIGIT_TONE_DURATION = 500;
unsigned short DIGIT_TONES[] = {
  NOTE_A4, // 0
  NOTE_B4, // 1
  NOTE_C5, // 2
  NOTE_D5, // 3
  NOTE_E5, // 4
  NOTE_F5, // 5
  NOTE_G5, // 6
  NOTE_A5, // 7
  NOTE_B5, // 8
  NOTE_C6  // 9
};


int inByte = 0;         // incoming serial byte
boolean displayDot = false;


void setup() {
  setupDigit();
  setupButtons();
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available() > 0) {
    // get incoming byte:
    inByte = Serial.read();
    switch (inByte) {
      case '.':
        displayDot = !displayDot;
        break;
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
        displayDigit(inByte - '0', displayDot);
        Serial.println(inByte - '0');
        Serial.println("OK");
        Serial.flush();
        break;
    }
  }
  else {
    int button = readButtonPress();
    if (button != NO_BUTTON) {
      displayDigit(button, displayDot);
      tone(TONE_PIN, DIGIT_TONES[button], DIGIT_TONE_DURATION);
      Serial.println(button);
      Serial.flush();
    }
  }
}
