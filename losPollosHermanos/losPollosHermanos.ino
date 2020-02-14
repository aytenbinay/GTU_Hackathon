#include <Servo.h>
#include <Adafruit_TCS34725.h>
#include <PID_v1.h>
#define qtr 8

uint16_t  r, g, b, c;
float red, green, blue, average;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

const int baseRight = 110;
const int baseLeft = 110;

int positionLast;
int pos;
int error;
int lastError;
double Setpoint, Input, Output;

float kp = 1.9;
float ki = 0.4;
float kd = 0.8;


const byte qtrPins[] = {A7, A6, A5, A4, A3, A2, A1, A0};
int qtrVal[] = {0, 0, 0, 0, 0, 0, 0, 0};


const int trigPin = 9;
const int echoPin = 8;
long duration;
int distancee = 0;

int enA = 2;
int in1 = 3;
int in2 = 4;
// motor two
int enB = 7;
int in3 = 5;
int in4 = 6;

Servo myServo;

boolean missionIsTaken = false;

enum directions {
  RIGHT,
  LEFT
};

enum missions {
  ENEMY,
  ALLIED,
  CIVILIAN
};

int mission = 999;

void setup() {
  // put your setup code here, to run once:
  defineSensors();
  defineServo();
  defineMotors();
  initPID();
  setMotors(baseRight, baseLeft);
  Serial.begin(9600);
}

void loop() {
  goForMission();
  completeMission();
  missionIsTaken = false;
}
