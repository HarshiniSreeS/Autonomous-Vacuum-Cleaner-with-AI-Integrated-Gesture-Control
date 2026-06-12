# Autonomous Vacuum Cleaner with AI-Integrated Gesture Control

## Computational Physics Project

### Faculty Guide

**Dr. Jithin Velayudhan**

### Team 17

| Name            | Roll Number      |
| --------------- | ---------------- |
| S Harshini Sree | CB.SC.U4AIE25044 |
| Thiyaanesh N R  | CB.SC.U4AIE25055 |
| Yuvanidhi R     | CB.SC.U4AIE25062 |
| Prakeya S       | CB.SC.U4AIE25042 |

---

# Problem Definition

## Problem Statement

Traditional vacuum cleaners require manual operation and lack intelligent control, making cleaning inefficient and labor-intensive.

This project aims to design an autonomous vacuum cleaner that integrates AI-based gesture control for enhanced usability.

## Core Challenge

The core challenge lies in enabling seamless coordination between AI-based gesture recognition and autonomous navigation, ensuring accurate control and uninterrupted operation within limited hardware resources.

## Relevance to Computational Physics

The project applies Computational Physics principles in:

* Modeling sensor data
* Optimizing motion dynamics
* Simulating real-time robotic behavior

It involves computational algorithms for:

* Data processing
* AI-driven decision-making
* Physical system simulation

This links theoretical computation with practical hardware implementation.

---

# Objectives

1. Develop an AI-driven autonomous navigation system.
2. Integrate gesture recognition using computer vision.
3. Design and integrate a unified hardware-software control framework.

---

# Proposed Methodology

## Workflow

```text
Vision
  ↓
Serial
  ↓
Execute
  ↓
Feedback
```

### Step 1: Vision

The PC runs MATLAB to capture live video frames from the webcam.

### Step 2: Gesture Recognition

The MATLAB program interprets extracted features to classify the recognized gesture.

### Step 3: Serial Communication

MATLAB sends the generated command signal through the USB Serial Port to the connected Arduino Uno.

### Step 4: Execution

Arduino receives the command and controls the motors accordingly.

### Step 5: Feedback

The executed action moves the vacuum cleaner.

The webcam captures the updated environment and sends new visual information back into the system.

---

# Physics Behind the Motion

The vacuum's motion follows basic physics concepts including:

* Velocity
* Acceleration
* Friction

### AI-Based Motion Control

* AI dynamically adjusts motor speed and turning using real-time sensor data.
* Smooth movement and stable navigation are achieved through feedback control.
* Combines physical motion principles with computational decision-making.

---

# Sensor Technology

Sensors act as the "eyes" and "ears" of the vacuum cleaner, enabling perception and interaction with the surrounding environment.

## Navigation Process

1. Sensor scans the environment
2. Obstacle detection and distance measurement
3. Data processing and environment mapping
4. Path planning and decision making
5. Navigation and movement adjustment

## Core Sensors

| Sensor                      | Function                                  |
| --------------------------- | ----------------------------------------- |
| Infrared Sensor             | Detects nearby objects using IR light     |
| Ultrasonic Sensor           | Measures distance using sound waves       |
| Time-of-Flight (ToF) Sensor | Calculates distance using reflected light |
| LiDAR Sensor                | Scans surroundings using laser beams      |
| Camera System               | Captures visual data                      |

---

# Data Recording

## Sensor Data

### Ultrasonic Sensors

The trigger emits an ultrasonic pulse toward an obstacle.

The echo signal calculates the time required for the pulse to return.

When the measured distance becomes smaller than a predefined threshold:

* The object is identified as an obstacle.
* The robot changes direction to avoid collision.

### Visual Data

The camera module captures real-time hand gestures for AI-based control.

---

# Data Acquisition Process (Hand Gesture Recognition)

1. Capture images using webcam
2. Collect multiple samples for each gesture
3. Organize images into labeled folders
4. Preprocess images
5. Split data into:

   * Training set
   * Validation set
   * Test set
6. Train the CNN using the cleaned dataset

---

# AI Algorithms Used

## Image Preprocessing

Images are resized and normalized before being fed into the CNN model.

## Convolutional Neural Network (CNN)

CNN is used for gesture recognition.

Recognized gestures are converted into commands such as:

* Forward
* Left
* Right
* Stop

## Transfer Learning

A pretrained neural network (`netTrained`) is used.

## Softmax Classification Layer

Example:

```text
Fist : 0.85
Palm : 0.10
```

## Threshold Logic

Only predictions above a predefined confidence threshold are accepted.

---

# Communication and Control Interface

## Gesture Mapping

| Gesture     | Action  |
| ----------- | ------- |
| Palm        | Forward |
| Fist        | Stop    |
| Thumbs Down | Left    |
| Thumbs Up   | Right   |

---

# Hardware Implementation

## Components Used

* Arduino Uno
* HW-130 L293D Motor Driver Shield
* Li-ion Battery
* Ultrasonic Sensor
* Servo Motor
* Four DC Motors
* Camera Module

---

# Source Code

## MATLAB Code (Gesture Recognition → Robot Control)

```matlab
clear; clc;

% --- 1. Settings ---
arduinoPort = "COM7";  % <--- CHANGE THIS TO YOUR ARDUINO PORT!
baudRate = 9600;

% --- 2. Setup Arduino Connection ---
disp(['Connecting to Arduino on ', arduinoPort, '...']);
try
    arduino = serialport(arduinoPort, baudRate);
    configureTerminator(arduino, "CR/LF");
    disp('Arduino Connected!');
catch
    error('Failed to connect. Check if Arduino is plugged in and COM port is correct.');
end

% --- 3. Load AI Model ---
disp('Loading AI Model...');
load('trained_gesture_net.mat');
inputSize = netTrained.Layers(1).InputSize(1:2);
cam = webcam();

disp('------------------------------------------------');
disp('  ROBOT CONTROL LIVE  ');
disp('  Sending commands: F, L, R, S');
disp('------------------------------------------------');

figure('Name', 'Robot Controller');
lastCommand = '';

while true
    % 1. Get Image
    img = snapshot(cam);
    imgResized = imresize(img, inputSize);

    % 2. Predict
    [label, scores] = classify(netTrained, imgResized);
    confidence = max(scores);
    gesture = char(label);

    % 3. Send Command Logic
    if confidence > 0.50
        cmdToSend = '';

        switch gesture
            case 'forward'
                cmdToSend = 'F';
            case 'left'
                cmdToSend = 'L';
            case 'right'
                cmdToSend = 'R';
            case 'stop'
                cmdToSend = 'S';
        end

        if ~strcmp(cmdToSend, lastCommand)
            write(arduino, cmdToSend, "char");
            lastCommand = cmdToSend;
            disp(['Sent to Robot: ', cmdToSend]);
        end
    else
        if ~strcmp(lastCommand, 'S')
            write(arduino, 'S', "char");
            lastCommand = 'S';
            disp('Unsure - Stopping Robot');
        end
    end

    % 4. Show Feed
    imshow(img);
    title(['Robot Action: ', gesture], 'FontSize', 18, 'Color', 'm');
    drawnow;
end
```

---

## Arduino Code (Obstacle Avoiding Car)

```cpp
// =========================
// OBSTACLE AVOIDING CAR
// ARDUINO + HW-130 L293D SHIELD + HC-SR04 + SERVO
// 4 DC MOTORS (M1–M4) + SERVO-MOUNTED ULTRASONIC
// =========================

#include <AFMotor.h>
#include <Servo.h>

// ---------- Ultrasonic pins ----------
const int trigPin = A0;
const int echoPin = A1;

// ---------- Servo (sensor head) ----------
const int servoPin = 9;
Servo headServo;

// Servo angles
const int CENTER_ANGLE = 90;
const int LEFT_ANGLE   = 150;
const int RIGHT_ANGLE  = 30;

// ---------- Motors ----------
AF_DCMotor motorFL(1);
AF_DCMotor motorRL(2);
AF_DCMotor motorFR(3);
AF_DCMotor motorRR(4);

// ---------- Settings ----------
const int baseSpeed    = 170;
const int turnSpeed    = 170;
const int stopDistance = 20;
const int backTime     = 300;
const int turnTime     = 350;

// ================== HELPER FUNCTIONS ==================

long getDistanceCM() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000UL);

  if (duration == 0) {
    return 300;
  }

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

// ================== SETUP ==================

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

// ================== MAIN LOOP ==================

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
    Serial.print("Left: ");
    Serial.print(leftDist);
    Serial.println(" cm");

    long rightDist = getDistanceAtAngle(RIGHT_ANGLE);
    Serial.print("Right: ");
    Serial.print(rightDist);
    Serial.println(" cm");

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
```

---
## ESP32 Code (Wi-Fi Command Forwarder)

```cpp
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

#define RXD2 16
#define TXD2 17

void handleCmd() {
  if (!server.hasArg("d")) {
    server.send(400, "text/plain", "Missing command");
    return;
  }

  char cmd = server.arg("d")[0];
  Serial2.write(cmd);

  server.send(200, "text/plain", "OK");
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Serial.println("ESP32 IP:");
  Serial.println(WiFi.localIP());

  server.on("/cmd", handleCmd);
  server.begin();
}

void loop() {
  server.handleClient();
}
```

---

# Results

- Achieves autonomous navigation with obstacle avoidance.
- Successfully follows recognized hand gestures.
- AI-integrated gesture control provides intuitive interaction.
- Sensor feedback improves stability and accuracy.
- Maintains smooth speed control and navigation.

---

# Conclusion

The system effectively combines:

- Artificial Intelligence
- Physics-based motion control
- Sensor intelligence

### Key Outcomes

- Demonstrates a feasible low-cost smart cleaning solution.
- Enables gesture-based interaction.
- Uses feedback control for improved performance.
- Provides an enhanced user experience.

---

# Future Improvements

- Full SLAM-based mapping
- Mobile application integration
- Voice assistant support
- Advanced deep-learning gesture recognition
- LiDAR-based navigation
- Automatic charging dock

---

# References

1. P. Singh and A. Sharma, *Cleaning Robot with Hand Gesture*, IJERT, 2019.
2. S. A. Khan and R. Patel, *Smart Vacuum Cleaner*, Materials Today: Proceedings, 2021.
3. O. A. Ogbomo and T. I. Omonhinmin, *A Hand Gesture Controlled Vacuum Cleaning Robot*, 2022.
4. R. Gupta et al., *IoT-Based Smart Vacuum Cleaner*, 2023.
5. S. Kim and D. Park, *A Control Strategy for an Autonomous Robotic Vacuum*, arXiv:1412.0591.
6. https://youtu.be/hHIIWpZcYNs?si=i4k-VetMv8UKkqQ0
