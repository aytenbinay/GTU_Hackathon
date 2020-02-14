void goForMission() {
  while (!missionIsTaken) {
    goOnLine();
    turn(checkTurn());
  }
  while (1) {
    followLine();
    checkDistance();
    Serial.println(distancee);
    if (distancee < 6) {
      checkDistance();
      if (distancee < 6) break;
    }
  }
  stopMotors();
  mission = findMission();
  turnBack();
  goUntilT();
  turn(RIGHT);
}

void completeMission() {
  switch (mission) {
    case ENEMY:
      repelEnemy();
      break;
    case ALLIED:
      supportAllied();
      break;
    case CIVILIAN:
      dontTouchCivilian();
      break;
  }
}


void goOnLine() {
  while (1) {
    followLine();
    if (computeQtr() < 5) break;
  }
  stopMotors();
}

int checkTurn() {
  int start=millis();
  while (1) {
    readQtr();
    if ((qtrVal[5] + qtrVal[6] + qtrVal[7]) < 2 ) {
      return RIGHT;
    } else if ((qtrVal[0] + qtrVal[1] + qtrVal[2]) < 2) {
      return LEFT;
    }
    if(millis()-start>1000){
      setMotors(-baseRight,-baseLeft);
      delay(500);
      goOnLine();
      start=millis();
    }
  }
}

void goUntilT() {
  while (1) {
    followLine();
    if (computeQtr() < 2) break;
  }

  stopMotors();
}



void repelEnemy() {
  goOnLine();
  turn(LEFT);
  goUntilT();
  turnBack();
  goUntilT();
  turn(LEFT);
}

void supportAllied() {
  goOnLine();
  turn(LEFT);
  goUntilT();
  dropAmmo();
  turnBack();
  goUntilT();
  turn(LEFT);
}

void dontTouchCivilian() {
  goOnLine();
  setMotors(baseRight, baseLeft);
  delay(200);
  stopMotors();
}

int findMission() {
  int redCounter = 0;
  int greenCounter = 0;
  int elseCounter = 0;

  while (1) {
    readColor();
    if ((red > 1.5) && (red < 2.30) && (green > 0.20) && (green < 0.70) && (blue > 0.20) && (blue < 0.7)) { // kırmızı renk olma durumu
      redCounter++;
      greenCounter = 0;
      elseCounter = 0;
    }
    else if ((red > 0.5) && (red < 1.2) && (green > 1.1) && (green < 1.7) && (blue > 0.3) && (blue < 0.90)) { // yeşil renk olma durumu
      redCounter = 0;
      greenCounter++;
      elseCounter = 0;
    } else {
      redCounter = 0;
      greenCounter = 0;
      elseCounter++;
    }
    
    if (redCounter > 2) {
      return ENEMY;
    }
    else if (greenCounter > 2) {
      return ALLIED;
    }
    else if (elseCounter > 2) {
      return CIVILIAN;
    }
  }
}

void dropAmmo() {
  for (int i = 80; i < 160; i++) {
    myServo.write(i);
    delay(10);
  }
  delay(200);
  
  for (int i = 160; i > 80; i--) {
    myServo.write(i);
    delay(10);
  }
  
}
