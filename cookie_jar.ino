const int sensorPin = 2;       // OUT pin from US-016
const int devicePin = 13;         // Device pin
const int ledPin = 12;
const int buzzerPin = 3;       // Buzzer pin

const int ledPinStart = 8;
const int ledPinEnd = 12;

int targetCount = 5;     // Touches to trigger LED

int touchCount = 0;
bool objectPreviouslyDetected = false;

unsigned long ledTurnOffTime = 0;

unsigned long lastTriggerTime = 0;
unsigned long triggerResolution = 1000; // ms

void setLedLights() {
  for (int ledPin=ledPinStart; ledPin<=ledPinEnd; ledPin++) {
    if (ledPin<ledPinStart + touchCount) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }
  }
}

void runMarqueeEffect() {
  // Blink all LEDs once
  for (int i=0; i<1; i++) {
  for (int ledPin = ledPinStart; ledPin <= ledPinEnd; ledPin++) {
    digitalWrite(ledPin, HIGH);
    delay(50);  // short blink
    digitalWrite(ledPin, LOW);
    delay(50);
  }
  
  }
  

  // Turn all LEDs on
  for (int ledPin = ledPinStart; ledPin <= ledPinEnd; ledPin++) {
    digitalWrite(ledPin, HIGH);
  }
}


void setTurnOffAllLeds() {
  for (int ledPin = ledPinStart; ledPin<=ledPinEnd; ledPin++) {
    digitalWrite(ledPin, LOW);
  }
}

void playCongratulationsTone() {
  int melody[] = {
    523, 587, 659, 698, 784, 880, 988, 1047  // C-D-E-F-G-A-B-C (upbeat)
  };
  int duration = 150; // milliseconds per note

  for (int i = 0; i < 8; i++) {
    tone(buzzerPin, melody[i]);
    delay(duration);
    noTone(buzzerPin);
    delay(50); // short pause between notes
  }
}


void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(devicePin, OUTPUT);
  for (int ledPin = ledPinStart; ledPin<=ledPinEnd; ledPin++) {
    pinMode(ledPin, OUTPUT);
  }
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Touch detected (rising edge)
  int sensorState = digitalRead(sensorPin);

  if (sensorState == LOW && (millis() - lastTriggerTime) > triggerResolution) {
    lastTriggerTime = millis();
    touchCount++;
    setLedLights();
    // digitalWrite(buzzerPin, HIGH);
    // delay(10);
    // digitalWrite(buzzerPin, LOW);
    // delay(100);
    if (touchCount < targetCount) {
      tone(buzzerPin, 500*touchCount); 
      delay(100);            // Duration of beep
      noTone(buzzerPin);     // Stop the tone
    }
  }


  // LED on when target reacheddevicePin
  if (touchCount >= targetCount) {
    //setLedLights();
    digitalWrite(devicePin, HIGH);
    runMarqueeEffect();
    playCongratulationsTone();
    touchCount = 0;
    delay(5000);
    digitalWrite(devicePin, LOW);


    setTurnOffAllLeds();
  }

  delay(500); // debounce
}
