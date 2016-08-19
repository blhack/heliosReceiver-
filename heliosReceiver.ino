#define sparkLag 3000
#define numOfTorches 12

int torchNumber;

int sparkPin = 14;

byte someByte;
unsigned long torchTimes[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int torchFuel[12] = {2,3,4,5,6,7,8,9,10,11,12,13};
unsigned long showTimes[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int showPins[10] = {23,24,25,26,27,28,29,47,48,49,50,51,52,53};
unsigned long sparkOff;
unsigned long lastKeepAlive;
int showNumber = 0;

void setup() {
  for (int i=0; i<numOfTorches; i++) {
    pinMode(torchFuel[i], OUTPUT);
    digitalWrite(torchFuel[i], LOW);
    delay(100);
    digitalWrite(torchFuel[i], HIGH);
    delay(100);
    }
  pinMode(18, INPUT_PULLUP);
  pinMode(sparkPin, OUTPUT);
  Serial.begin(9600);
}

void readSerial() {
  if (Serial.available()) {
    someByte = Serial.read();
    torchNumber = int(someByte);
    if (torchNumber <= numOfTorches) {
      torchTimes[torchNumber] = millis() + 150;
    }
    if (torchNumber >= 100) {
      showNumber = torchNumber - 100;
      showTimes[showNumber] = millis() + 500;
    }
  }
}

void setTorches() {
  for (int i=0; i<numOfTorches; i++) {
    if (torchTimes[i] > millis()) {
      digitalWrite(torchFuel[i], LOW);
      sparkOff = millis() + 5000;
    }
    else {
      digitalWrite(torchFuel[i], HIGH);
    }
  }
}

void setSparks() {
  if (millis() < sparkOff) {
    digitalWrite(sparkPin, LOW);
  } else {
    digitalWrite(sparkPin, HIGH);
  }
}

void keepAlive() {
  if ((millis() - lastKeepAlive) > 5000) {
    Serial.write(13);
    lastKeepAlive = millis();
  }
}

void lightShow() {
  for (int i=0; i<=14; i++) {
    if (showTimes[i] > millis()) {
      digitalWrite(showPins[i], HIGH);
    } else {
      digitalWrite(showPins[i], LOW);
    }
  }
}

void loop() {
  readSerial();
  setSparks();
  setTorches();
  setLighting();
  lightShow();
  delay(10);
}
