# 🚘 ADAS System Project

This repository contains a modular implementation of an Advanced Driver-Assistance System (ADAS) including four key features developed by our engineering team.


## 🧠 Features Overview

| Feature                   | Description                                                                  |
|---------------------------|------------------------------------------------------------------------------|
| Lane Keep Assist (LKA)    | Detects lane lines and sends steering angle to Arduino for real-time control. |
| Blind Spot Monitor (BSM)  | Uses dual cameras to detect motion in blind zones and alerts via Arduino.     |
| Driver Monitoring System  | Tracks driver attentiveness and sends alerts or stops the vehicle if needed. |
| Adaptive Cruise Control   | Uses YOLOv8 and RealSense to detect obstacles ahead and manage speed safely.  |




## 📁 Project Structure

adas-system/
├── lane_keep_assist/
│ ├── main.py
│ ├── init.py
│ ├── arduino/
│ │ └── lka_arduino_code.ino
│ └── hardware/
│ └── camera.md
│
├── blind_spot_monitor/
│ ├── main.py
│ ├── init.py
│ ├── arduino/
│ │ └── bsm_arduino_code.ino
│ └── hardware/
│ ├── left_camera.md
│ └── right_camera.md
│
├── driver_monitoring_system/
│ ├── main.py
│ ├── init.py
│ ├── arduino/
│ │ └── dms_arduino_code.ino
│ └── hardware/
│ ├── webcam.md
│ └── buzzer.md
│
├── adaptive_cruise_control/
│ ├── main.py
│ ├── init.py
│ ├── arduino/
│ │ └── acc_arduino_code.ino
│ └── hardware/
│ ├── realsense_camera.md
│ └── motor_control.md
│
├── requirements.txt
└── README.md



## 🛠 Requirements

Install dependencies using:

pip install -r requirements.txt





## 🛣 Lane Keep Assist (LKA)

This feature uses OpenCV techniques like Canny edge detection and Hough transforms to detect road lane markings. Based on the detected lane curvature, it calculates a steering angle and sends it to the Arduino, which controls a motor or servo accordingly.

### 🔧 Hardware Used
- **Camera:** USB front-facing camera  
- **Controller:** Arduino Uno or Nano  
- **Actuator:** Servo motor or motor driver  

### 🔌 Arduino Pins
- **D9** → Servo or motor control output  



## 📸 Blind Spot Monitor (BSM)

This feature uses two side-mounted cameras to detect objects in blind spots via motion detection. If an object is present, it alerts the driver using LEDs and buzzers via Arduino.

**Hardware:**
- 2 USB Cameras  
- Arduino  
- LED Indicators  
- Optional: Buzzer  

**Arduino Pins:**
- Left Indicator: D8  
- Right Indicator: D9  
- Buzzer: D10






## 👁 Driver Monitoring System (DMS)

Monitors driver’s face, drowsiness, or distraction using computer vision. Sends warnings or engages safety stop.

**Hardware:**
- Webcam (driver-facing)  
- Arduino  
- Vibration Motor + Buzzer

**Arduino Pins:**
- Vibration motor: D9  
- Buzzer: D8  






## 🚗 Adaptive Cruise Control (ACC)

This module uses an Intel RealSense depth camera and YOLOv8 object detection to estimate the distance to objects in front of the vehicle. Based on proximity, it sends serial commands to an Arduino to stop or go.

**Hardware:**
- RealSense D435 camera  
- Arduino Uno/Nano  
- Motor driver (D9)  
- Buzzer (D10)

**How It Works:**
1. YOLOv8 detects objects in the camera feed.
2. RealSense provides depth data at each object’s center point.
3. If an object is closer than 1.5 meters, a "stop" signal is sent to the Arduino.
4. Otherwise, a "go" signal is sent.

**Serial Commands Sent to Arduino:**
- "go" → Motor ON  
- "stop" → Motor OFF, buzzer ON







## 🧪 How to Run Each Feature

Run the Python entry point for each feature:

```bash
python3 -m lane_keep_assist.main
python3 -m blind_spot_monitor.main
python3 -m driver_monitoring_system.main
python3 -m adaptive_cruise_control.main




## 📜 License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT).

You are free to use, modify, and distribute this software for personal or commercial purposes, provided that the original license is included with any substantial portions of the project.

© 2025 ADAS System Team. All rights reserved.
