void setupDigit() {
  pinMode(LED_SHIFT_DATA_PIN, OUTPUT);      
  pinMode(LED_SHIFT_STORAGE_PIN, OUTPUT);      
  pinMode(LED_SHIFT_SHIFT_PIN, OUTPUT);
  displayDigit(-1, false); // off
}

void displayDigit(int digit, boolean displayDot) {
  byte value = 0;
  if (digit >= 0 && digit <= 9) {
    value = DIGIT_CODES[digit];
  }
  if (displayDot) {
    value |= DOT_CODE;
  }
  value = ~value;
  digitalWrite(LED_SHIFT_STORAGE_PIN, LOW);
  shiftOut(LED_SHIFT_DATA_PIN, LED_SHIFT_SHIFT_PIN, LSBFIRST, value);
  digitalWrite(LED_SHIFT_STORAGE_PIN, HIGH);
}
