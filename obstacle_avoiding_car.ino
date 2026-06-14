// =========================
// OBSTACLE AVOIDING CAR
// ARDUINO + HW-130 L293D SHIELD + HC-SR04 + SERVO
// 4 DC MOTORS (M1–M4) + SERVO-MOUNTED ULTRASONIC
// =========================

#include <AFMotor.h>
#include <Servo.h>

const int trigPin = A0;
const int echoPin = A1;

const int servoPin = 9;
Servo headServo;

const int CENTER_ANGLE = 90;
const int LEFT_ANGLE   = 150;
const int RIGHT_ANGLE  = 30;

AF_DCMotor motorFL(1);
AF_DCMotor motorRL(2);
AF_DCMotor motorFR(3);
AF_DCMotor motorRR(4);

const int baseSpeed    = 170;
const int turnSpeed    = 170;
const int stopDistance = 20;
const int backTime     = 300;
const int turnTime     = 350;

long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000UL);

  if (duration == 0) return 300;

  long distance = duration * 0.034 / 2;
  return distance;
}

long getDistanceAtAngle(int angle) {
  headServo.write(angle);
  delay(300);
  return getDistanceCM();
}

void setAllSpeeds(int s) {
  motorFL.setSpeed(s);
  motorRL.setSpeed(s);
  motorFR.setSpeed(s);
  motorRR.setSpeed(s);
}

void moveForward(int s) {
  setAllSpeeds(s);
  motorFL.run(FORWARD);
  motorRL.run(FORWARD);
  motorFR.run(FORWARD);
  motorRR.run(FORWARD);
}

void moveBackward(int s) {
  setAllSpeeds(s);
  motorFL.run(BACKWARD);
  motorRL.run(BACKWARD);
  motorFR.run(BACKWARD);
  motorRR.run(BACKWARD);
}

void turnLeft(int s) {
  motorFL.setSpeed(0);
  motorRL.setSpeed(0);
  motorFL.run(RELEASE);
  motorRL.run(RELEASE);

  motorFR.setSpeed(s);
  motorRR.setSpeed(s);
  motorFR.run(FORWARD);
  motorRR.run(FORWARD);
}

void turnRight(int s) {
  motorFR.setSpeed(0);
  motorRR.setSpeed(0);
  motorFR.run(RELEASE);
  motorRR.run(RELEASE);

  motorFL.setSpeed(s);
  motorRL.setSpeed(s);
  motorFL.run(FORWARD);
  motorRL.run(FORWARD);
}

void stopMotors() {
  motorFL.setSpeed(0);
  motorRL.setSpeed(0);
  motorFR.setSpeed(0);
  motorRR.setSpeed(0);

  motorFL.run(RELEASE);
  motorRL.run(RELEASE);
  motorFR.run(RELEASE);
  motorRR.run(RELEASE);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  headServo.attach(servoPin);
  headServo.write(CENTER_ANGLE);
  delay(500);

  Serial.begin(9600);

  stopMotors();
  delay(1000);
}

void loop() {
  long frontDist = getDistanceAtAngle(CENTER_ANGLE);

  Serial.print("Front distance: ");
  Serial.print(frontDist);
  Serial.println(" cm");

  if (frontDist > stopDistance) {
    moveForward(baseSpeed);
  } else {
    stopMotors();
    delay(200);

    moveBackward(baseSpeed);
    delay(backTime);

    stopMotors();
    delay(200);

    long leftDist = getDistanceAtAngle(LEFT_ANGLE);
    long rightDist = getDistanceAtAngle(RIGHT_ANGLE);

    headServo.write(CENTER_ANGLE);

    if (leftDist > rightDist) {
      turnLeft(turnSpeed);
    } else {
      turnRight(turnSpeed);
    }

    delay(turnTime);
    stopMotors();
    delay(100);
  }

  delay(50);
}
