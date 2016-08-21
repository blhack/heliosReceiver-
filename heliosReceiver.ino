#define sparkLag 3000
#define numOfTorches 12

int torchNumber;

int sparkPin = 14;

byte someByte;
unsigned long torchTimes[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
int torchFuel[12] = {2,3,4,5,6,7,8,9,10,11,12,13};
unsigned long showTimes[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int showPins[15] = {23,25,27,29,31,33,35,37,41,43,45,47,49,51,53};
unsigned long sparkOff;
unsigned long lastKeepAlive;
int showNumber = 0;

void setup() {
  for (int i=0; i<12; i++) {
    pinMode(torchFuel[i], OUTPUT);
  }
  for (int i=0; i<15; i++) {
    pinMode(showPins[i], OUTPUT);
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
    if (torchNumber >= 20) {
      showNumber = torchNumber - 20;
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

  for (int i=0; i<15; i++) {
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
  lightShow();
  delay(10);
}
