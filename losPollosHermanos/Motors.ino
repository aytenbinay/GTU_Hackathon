void setMotors(int rightSpeed, int leftSpeed) {
  if (rightSpeed > 0) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  if (leftSpeed > 0) {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  } else {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  analogWrite(enA, abs(rightSpeed));
  analogWrite(enB, abs(leftSpeed));
}

void defineMotors() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void turnBack(){
  setMotors(-baseRight,-baseLeft);
  delay(300);
  stopMotors();
  turnRight();
}


void turnLeft() {
  setMotors(80, -80);
  delay(400);
  while (1) {
    readQtr();
    if (qtrVal[3] == 0) break;
  }
  setMotors(-baseRight, baseLeft);
  delay(50);
  setMotors(0, 0);
}

void turnRight() {
  setMotors(-80, 80);
  delay(400);
  while (1) {
    readQtr();
    if (qtrVal[5] == 0) break;
  }
  setMotors(baseRight, -baseLeft);
  delay(50);
  setMotors(0, 0);
}

void turn(int dir){
  setMotors(baseRight,baseLeft);
  delay(300); //değişecek
  if(computeQtr()<8) missionIsTaken=true;
  if(dir ==RIGHT){
    turnRight();
  }else if(dir==LEFT){
    turnLeft();
  }
}


void stopMotors() {
  setMotors(-baseRight, -baseLeft);
  delay(50);
  setMotors(0, 0);
}

void defineServo(){
  myServo.write(80);
  myServo.attach(11);
}
