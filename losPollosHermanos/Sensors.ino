const int qtrMults[] = {7, 5, 3, 1, -1, -3, -5, -7};

int getPosition() {
  readQtr();
  int sum = 0;
  int valueCounter = 0;
  for (byte i = 0; i < 8; i++) {
    if (qtrVal[i] == 0) {
      valueCounter++;
    }
    sum += qtrVal[i] * qtrMults[i];
  }
  if (valueCounter == 0) {
    return positionLast;
  }
  sum /= valueCounter;
  return sum;
}

void defineSensors() {
  defineQtr();
  defineUltrasonic();
}

void defineQtr() {
  for (int i = 0; i < qtr; i++) {
    pinMode(qtrPins[i], INPUT_PULLUP);
  }
}

void readQtr() {
  for (int i = 0; i < qtr; i++) {
    qtrVal[i] = digitalRead(qtrPins[i]);
  }
}

void printQtr() {
  readQtr();
  for (int i = 0; i < qtr; i++) {
    Serial.print(qtrVal[i]);
    Serial.print("--");
  }
  Serial.println();
}

int computeQtr() {
  int value = 0;
  readQtr();

  for (int i = 0; i < qtr; i++) {
    value += qtrVal[i];
  }

  return value;
}

void defineUltrasonic() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);
}

void checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
 distancee = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
}
