#define BUTTON_PIN      2
#define GREEN_LED_PIN   3
#define YELLOW_LED_PIN  4
#define RED_LED_PIN     5
#define SPEAKER_PIN     6
#define ALARM_LED_PIN   7

#define SENSOR_PIN        0
#define SENSOR_THRESHOLD  800

#define ALARM_PERIOD_MS 500
#define ALARM_LOW_FREQ  635
#define ALARM_HIGH_FREQ 912

#define CYCLE_PERIOD_MS (1000 / 20)


// *****************************
// State Management

typedef void (*StateCycleFunction) ();

StateCycleFunction stateCycle;


// *****************************
// Handling button

bool buttonPressed = false;

bool buttonGotPressed() {
  if (digitalRead(BUTTON_PIN) == 0) {
    bool buttonWasPressed = buttonPressed;
    buttonPressed = true;
    if (!buttonWasPressed) Serial.write("Button pressed!\n");
    return !buttonWasPressed;
  }
  else {
    buttonPressed = false;
    return false;
  }
}


// *****************************
// Handling Sensor

bool sensorIsOn = true;

bool checkSensor() {
  bool sensorWasOn = sensorIsOn;
  int value = analogRead(SENSOR_PIN);
//  for (int i = 0; i < value / 100; i++) Serial.write('X');
//  Serial.println();
  sensorIsOn = value > SENSOR_THRESHOLD;
  if (sensorWasOn != sensorIsOn) {
    if (sensorIsOn) Serial.println("Sensor is NOT blocked");
    else Serial.println("Sensor IS blocked");
    digitalWrite(RED_LED_PIN, !sensorIsOn);
  }
  return sensorIsOn;
}


// *****************************
// STANDBY STATE 

void switchToStandbyState() {
  Serial.write("STANDBY\n");
  
  digitalWrite(GREEN_LED_PIN, 1);
  digitalWrite(YELLOW_LED_PIN, 0);
  digitalWrite(ALARM_LED_PIN, 0);

  noTone(SPEAKER_PIN);

  stateCycle = standbyCycle;
}

void standbyCycle() {

  checkSensor();

  if (buttonGotPressed()) {
    if (sensorIsOn) {
      switchToArmedState();
      return;
    }
    else Serial.println("Sensor is blocked - not arming");
  }
}


// *****************************
// ARMED STATE 

void switchToArmedState() {
  Serial.println("ARMED");
  
  digitalWrite(GREEN_LED_PIN, 0);
  digitalWrite(YELLOW_LED_PIN, 1);
  digitalWrite(ALARM_LED_PIN, 0);

  noTone(SPEAKER_PIN);

  stateCycle = armedCycle;
}

void armedCycle() {
  if (!checkSensor()) {
    switchToAlarmState();
    return;
  }

  if (buttonGotPressed()) {
    switchToStandbyState();
    return;
  }
}


// *****************************
// ALARM STATE 

unsigned long nextAlarmToneChange;
bool lowTone;

void switchToAlarmState() {
  Serial.println("ALARM");
  
  digitalWrite(GREEN_LED_PIN, 0);
  digitalWrite(YELLOW_LED_PIN, 1);
  digitalWrite(ALARM_LED_PIN, 1);

  noTone(SPEAKER_PIN);

  nextAlarmToneChange = 0;
  lowTone = true;

  stateCycle = alarmCycle;  
}

void alarmCycle() {
  checkSensor();

  if (buttonGotPressed()) {
    switchToStandbyState();
    return;
  }

  unsigned long now = millis();
  if (now > nextAlarmToneChange) {
    nextAlarmToneChange = now + ALARM_PERIOD_MS;
    lowTone = !lowTone;
    if (lowTone) {
      digitalWrite(YELLOW_LED_PIN, 0);
      tone(SPEAKER_PIN, ALARM_LOW_FREQ);      
    }
    else {
      digitalWrite(YELLOW_LED_PIN, 1);
      tone(SPEAKER_PIN, ALARM_HIGH_FREQ);            
    }
  }

}



// *****************************
// Standard Program Lifecycle

void setup() {
  Serial.begin(57600);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  pinMode(ALARM_LED_PIN, OUTPUT);

  digitalWrite(RED_LED_PIN, 0);

  switchToStandbyState();
}

void loop() {
  StateCycleFunction prevStateCycle;
  do {
    prevStateCycle = stateCycle;
    stateCycle();    
  } while (stateCycle != prevStateCycle);

  delay(CYCLE_PERIOD_MS);
}

