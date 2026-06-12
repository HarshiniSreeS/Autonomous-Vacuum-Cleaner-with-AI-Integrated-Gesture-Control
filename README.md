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
PASTE YOUR MATLAB CODE HERE EXACTLY AS PROVIDED
```

---

## ESP32 Code (Wi-Fi Command Forwarder)

```cpp
PASTE YOUR ESP32 CODE HERE EXACTLY AS PROVIDED
```

---

## Arduino Code (Obstacle Avoiding Car)

```cpp
PASTE YOUR ARDUINO CODE HERE EXACTLY AS PROVIDED
```

---

# Results

* Achieves autonomous navigation with obstacle avoidance.
* Successfully follows recognized hand gestures.
* AI-integrated gesture control provides intuitive interaction.
* Sensor feedback improves stability and accuracy.
* Maintains smooth speed control and navigation.

---

# Conclusion

The system effectively combines:

* Artificial Intelligence
* Physics-based motion control
* Sensor intelligence

Key outcomes:

* Demonstrates a feasible low-cost smart cleaning solution.
* Enables gesture-based interaction.
* Uses feedback control for improved performance.
* Provides an enhanced user experience.

---

# Future Improvements

* Full SLAM-based mapping
* Mobile application integration
* Voice assistant support
* Advanced deep-learning gesture recognition
* LiDAR-based navigation
* Automatic charging dock

---

# References

1. P. Singh and A. Sharma, *Cleaning Robot with Hand Gesture*, IJERT, 2019.
2. S. A. Khan and R. Patel, *Smart Vacuum Cleaner*, Materials Today: Proceedings, 2021.
3. O. A. Ogbomo and T. I. Omonhinmin, *A Hand Gesture Controlled Vacuum Cleaning Robot*, 2022.
4. R. Gupta et al., *IoT-Based Smart Vacuum Cleaner*, 2023.
5. S. Kim and D. Park, *A Control Strategy for an Autonomous Robotic Vacuum*, arXiv:1412.0591.
6. https://youtu.be/hHIIWpZcYNs?si=i4k-VetMv8UKkqQ0
