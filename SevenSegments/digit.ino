void setupDigit() {
  pinMode(SEGMENT_0, OUTPUT);      
  pinMode(SEGMENT_1, OUTPUT);      
  pinMode(SEGMENT_2, OUTPUT);      
  pinMode(SEGMENT_3, OUTPUT);      
  pinMode(SEGMENT_4, OUTPUT);      
  pinMode(SEGMENT_5, OUTPUT);      
  pinMode(SEGMENT_6, OUTPUT);      
  pinMode(SEGMENT_7, OUTPUT);        
}

void displayDigit(int digit, boolean displayDot) {
  switch (digit) {
    case 0:
      digitalWrite(SEGMENT_0, 0);
      digitalWrite(SEGMENT_1, 0);
      digitalWrite(SEGMENT_2, 0);
      digitalWrite(SEGMENT_3, 0);
      digitalWrite(SEGMENT_4, 1);
      digitalWrite(SEGMENT_5, 0);
      digitalWrite(SEGMENT_6, 0);
      break;
    case 1:
      digitalWrite(SEGMENT_0, 1);
      digitalWrite(SEGMENT_1, 0);
      digitalWrite(SEGMENT_2, 0);
      digitalWrite(SEGMENT_3, 1);
      digitalWrite(SEGMENT_4, 1);
      digitalWrite(SEGMENT_5, 1);
      digitalWrite(SEGMENT_6, 1);
      break;
    case 2:
      digitalWrite(SEGMENT_0, 0);
      digitalWrite(SEGMENT_1, 0);
      digitalWrite(SEGMENT_2, 1);
      digitalWrite(SEGMENT_3, 1);
      digitalWrite(SEGMENT_4, 0);
      digitalWrite(SEGMENT_5, 0);
      digitalWrite(SEGMENT_6, 0);
      break;
    case 3:
      digitalWrite(SEGMENT_0, 0);
      digitalWrite(SEGMENT_1, 0);
      digitalWrite(SEGMENT_2, 0);
      digitalWrite(SEGMENT_3, 1);
      digitalWrite(SEGMENT_4, 0);
      digitalWrite(SEGMENT_5, 1);
      digitalWrite(SEGMENT_6, 0);
      break;
    case 4:
      digitalWrite(SEGMENT_0, 1);
      digitalWrite(SEGMENT_1, 0);
      digitalWrite(SEGMENT_2, 0);
      digitalWrite(SEGMENT_3, 0);
      digitalWrite(SEGMENT_4, 0);
      digitalWrite(SEGMENT_5, 1);
      digitalWrite(SEGMENT_6, 1);
      break;
    case 5:
      digitalWrite(SEGMENT_0, 0);
      digitalWrite(SEGMENT_1, 1);
      digitalWrite(SEGMENT_2, 0);
      digitalWrite(SEGMENT_3, 0);
      digitalWrite(SEGMENT_4, 0);
      digitalWrite(SEGMENT_5, 1);
      digitalWrite(SEGMENT_6, 0);
      break;
    case 6:
      digitalWrite(SEGMENT_0, 0);
      digitalWrite(SEGMENT_1, 1);
      digitalWrite(SEGMENT_2, 0);
      digitalWrite(SEGMENT_3, 0);
      digitalWrite(SEGMENT_4, 0);
      digitalWrite(SEGMENT_5, 0);
      digitalWrite(SEGMENT_6, 0);
      break;
    case 7:
      digitalWrite(SEGMENT_0, 0);
      digitalWrite(SEGMENT_1, 0);
      digitalWrite(SEGMENT_2, 0);
      digitalWrite(SEGMENT_3, 1);
      digitalWrite(SEGMENT_4, 1);
      digitalWrite(SEGMENT_5, 1);
      digitalWrite(SEGMENT_6, 1);
      break;
    case 8:
      digitalWrite(SEGMENT_0, 0);
      digitalWrite(SEGMENT_1, 0);
      digitalWrite(SEGMENT_2, 0);
      digitalWrite(SEGMENT_3, 0);
      digitalWrite(SEGMENT_4, 0);
      digitalWrite(SEGMENT_5, 0);
      digitalWrite(SEGMENT_6, 0);
      break;
    case 9:
      digitalWrite(SEGMENT_0, 0);
      digitalWrite(SEGMENT_1, 0);
      digitalWrite(SEGMENT_2, 0);
      digitalWrite(SEGMENT_3, 0);
      digitalWrite(SEGMENT_4, 0);
      digitalWrite(SEGMENT_5, 1);
      digitalWrite(SEGMENT_6, 0);
      break;
    default:
      digitalWrite(SEGMENT_0, 1);
      digitalWrite(SEGMENT_1, 1);
      digitalWrite(SEGMENT_2, 1);
      digitalWrite(SEGMENT_3, 1);
      digitalWrite(SEGMENT_4, 1);
      digitalWrite(SEGMENT_5, 1);
      digitalWrite(SEGMENT_6, 1);
      break;
  }
  
  digitalWrite(SEGMENT_7, (displayDot? 0 : 1));
  
}
