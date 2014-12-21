void setupButtons() {
  pinMode(BUTTONS_SELECTOR_0, OUTPUT);      
  pinMode(BUTTONS_SELECTOR_1, OUTPUT);      
  pinMode(BUTTONS_SELECTOR_2, OUTPUT);      
  pinMode(BUTTONS_SELECTOR_3, OUTPUT);        
}

int readButtons() {
  for (int i = 0; i < 16; i++) {
    selectButton(i);
    delay(1);
    int value = analogRead(BUTTIONS_INPUT);
    if (value > 512) {
      return transformButton(i);
    }
  }
  return NO_BUTTON;
}

// compensates from idiod board design
int transformButton(int i) {
  switch (i) {
    case 4: return 2;
    case 7: return 3;
    case 0: return 4;
    case 3: return 5;
    case 13: return 7;
    case 2: return 8;
    case 5: return 9;
    case 9: return 0;
    default: return i;
  }
}

void selectButton(int i) {
  digitalWrite(BUTTONS_SELECTOR_0, i & 0b0001);
  digitalWrite(BUTTONS_SELECTOR_1, i & 0b0010);
  digitalWrite(BUTTONS_SELECTOR_2, i & 0b0100);
  digitalWrite(BUTTONS_SELECTOR_3, i & 0b1000);
}

