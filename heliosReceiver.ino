#define sparkLag 3000
#define numOfTorches 8

int torchNumber;

byte someByte;
unsigned long torchTimes[8] = {0,0,0,0,0,0,0,0};
int torchFuel[8] = {2,3,4,5,6,7,8,9};
int spark[8] = {10,11,12,13,14,15,16,17};
unsigned long lastKeepAlive;

void setup() {
  for (int i=0; i<numOfTorches; i++) {
    pinMode(torchFuel[i], OUTPUT);
    pinMode(spark[i], OUTPUT);
    digitalWrite(torchFuel[i], LOW);
    delay(100);
    digitalWrite(torchFuel[i], HIGH);
    digitalWrite(spark[i], LOW);
    delay(100);
    digitalWrite(spark[i], HIGH);
  }
  Serial.begin(9600);
}

void readSerial() {
  if (Serial.available()) {
    someByte = Serial.read();
    torchNumber = int(someByte);
    if (torchNumber <= numOfTorches) {
      torchTimes[torchNumber] = millis() + 100;
    }
  }
}

void setTorches() {
  for (int i=0; i<numOfTorches; i++) {
    if (torchTimes[i] > millis()) {
      digitalWrite(torchFuel[i], LOW);
    }
    else {
      digitalWrite(torchFuel[i], HIGH);
    }
  }
}

void setSparks() {
  for (int i=0; i<numOfTorches; i++) {
    if ((torchTimes[i] + sparkLag) > millis()) {
      digitalWrite(spark[i], LOW);
    } else {
      digitalWrite(spark[i], HIGH);
    }
  }
}

void keepAlive() {
  if ((millis() - lastKeepAlive) > 5000) {
    Serial.write(13);
    lastKeepAlive = millis();
  }
}

void loop() {
  readSerial();
  setSparks();
  setTorches();
  //keepAlive();
  delay(10);
}
