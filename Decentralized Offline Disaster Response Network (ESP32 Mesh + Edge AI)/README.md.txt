# 🚨 Decentralized Offline Disaster Response Network  
### ESP32 Mesh + Edge AI

## 📌 Overview
A self-healing decentralized disaster communication network built using ESP32 mesh networking and edge intelligence.

This system works completely offline and is designed for:
- Earthquakes
- Floods
- Fire disasters
- Gas leaks
- Remote rescue operations

---

## 🧠 Key Features

- 📡 ESP32 Mesh Network (No Internet Required)
- 🔁 Self-Healing Communication
- 🤖 Edge AI (Local Decision Making)
- 🔥 Fire & Gas Detection
- 🌍 Offline Command Dashboard
- 🔋 Low Power Operation

---

## 🏗 Architecture

Sensor Nodes collect:
- Temperature
- Gas levels
- Vibration

Nodes communicate through ESP-MESH.

Command Node displays:
- Alerts
- Node Status
- Emergency Broadcasts

---

## 🛠 Hardware Required

- ESP32 Dev Kit (2+ recommended)
- DHT11 Temperature Sensor
- MQ-2 Gas Sensor
- MPU6050 (Optional)
- OLED Display (0.96” I2C)
- Jumper wires
- Power bank / Li-ion battery

---

## ⚙ Software Stack

- Arduino IDE
- ESP-MESH Library
- FreeRTOS
- TinyML (Optional future upgrade)

---

## 🚀 How It Works

1. Sensor node collects data
2. Edge AI processes locally
3. Alert packet sent through mesh
4. Command node displays alert
5. System reroutes automatically if node fails

---

## 📈 Future Improvements

- LoRa Backup Communication
- GPS Integration
- TinyML-based Disaster Classification
- Drone Integration
- Web-based Offline Dashboard

---

## 🏆 Hackathon Impact

A scalable, low-cost disaster response system that functions without centralized infrastructure.

---

## 📜 License
MIT License
