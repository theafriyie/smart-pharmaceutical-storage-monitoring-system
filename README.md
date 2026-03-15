# Smart Pharmaceutical Storage Monitoring and Control System

This project presents the design and implementation of a smart temperature and humidity monitoring and control system for pharmaceutical storage facilities, using M&G Pharmaceutical Company as a case study.

The system was developed to protect temperature-sensitive medicines by continuously monitoring environmental conditions, triggering alerts when values go outside safe ranges, and automatically activating a cooling mechanism when necessary.

## Project Background

Maintaining proper temperature and humidity is essential in pharmaceutical storage because poor environmental conditions can reduce medicine quality, cause financial loss, and create public health risks. This project addresses that challenge by replacing manual monitoring with an automated real-time monitoring and response system.

## Objectives

- Monitor temperature and humidity in real time
- Display readings locally and remotely
- Send alerts when thresholds are exceeded
- Automatically activate cooling when needed
- Store environmental data for tracking and review

## Key Features

- Real-time temperature and humidity monitoring
- DHT22-based environmental sensing
- Arduino Uno and ESP8266-based embedded control
- Relay-controlled cooling fan activation
- 16x2 I2C LCD for on-site display
- Firebase Realtime Database integration
- Firebase Cloud Messaging notifications
- Flutter mobile application for remote monitoring
- Notification history and trend viewing
- User authentication for secure app access

## Hardware Components

- Arduino Uno R3
- ESP8266 NodeMCU v1.0
- DHT22 temperature and humidity sensor
- 1-channel 5V relay module
- 16x2 I2C LCD display
- DC cooling fan
- 5V regulated power supply
- Jumper wires
- Prototype enclosure

## Software Stack

- Arduino IDE
- Embedded C/C++
- Flutter
- Firebase Realtime Database
- Firebase Cloud Messaging
- Android Studio

## How the System Works

1. The DHT22 sensor reads temperature and humidity values in real time.
2. The Arduino-based control logic checks whether readings remain within allowed thresholds.
3. If a threshold is exceeded, the system activates the relay-controlled cooling fan.
4. Sensor readings are displayed on the LCD screen.
5. Sensor readings and alerts are sent to Firebase.
6. The Flutter mobile app fetches and displays live values remotely.
7. Push notifications are sent to users when unsafe conditions are detected.

## Repository Structure

- `firmware/` – embedded code for sensing, control logic, and communication
- `mobile_app/` – Flutter app information, screenshots, and related files
- `hardware/` – hardware setup, components, and circuit notes
- `system_diagrams/` – architecture diagrams, DFDs, use case diagrams, and flowcharts
- `images/` – prototype photos, LCD screenshots, and app screenshots
- `documentation/` – thesis, abstract, and supporting documentation

## Results Summary

The implemented system successfully achieved real-time monitoring, automatic threshold response, cloud synchronization, mobile access, and alert delivery. It demonstrated a practical and scalable solution for pharmaceutical storage monitoring in real-world settings.

## Applications

- Pharmaceutical warehouses
- Medical storage rooms
- Vaccine storage monitoring
- Laboratory environmental monitoring
- Other safety-critical storage environments

## Author

John Afriyie Oduro
