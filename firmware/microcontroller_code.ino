# Firmware

This folder contains the embedded firmware for the smart pharmaceutical storage monitoring and control system.

The firmware is responsible for:
- reading temperature and humidity values from the DHT22 sensor
- applying threshold-based decision logic
- activating the relay-controlled cooling fan
- updating the LCD display
- sending data to the connected cloud pipeline

## Main Responsibilities

- Real-time sensor acquisition
- Threshold checking
- Automatic control response
- Local display support
- Communication with connected modules

## Main Hardware Controlled by Firmware

- DHT22 sensor
- Arduino Uno / ESP8266
- Relay module
- Cooling fan
- LCD display
