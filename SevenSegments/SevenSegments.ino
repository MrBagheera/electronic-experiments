
// 0 segment
const int SEGMENTS_BASE =  2;
const int SEGMENT_0 = SEGMENTS_BASE;
const int SEGMENT_1 = SEGMENTS_BASE + 1;
const int SEGMENT_2 = SEGMENTS_BASE + 2;
const int SEGMENT_3 = SEGMENTS_BASE + 3;
const int SEGMENT_4 = SEGMENTS_BASE + 4;
const int SEGMENT_5 = SEGMENTS_BASE + 5;
const int SEGMENT_6 = SEGMENTS_BASE + 6;
const int SEGMENT_7 = SEGMENTS_BASE + 7;

int inByte = 0;         // incoming serial byte
boolean displayDot = false;


void setup() {
  setupDigit();
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
        Serial.println(inByte);
        Serial.println("OK");
        Serial.flush();
        break;
    }
  }  
}
