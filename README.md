# 🔐 Dual Microcontroller-Based Door Locker Security System  

![GitHub repo size](https://img.shields.io/github/repo-size/yourusername/Dual-MCU-Door-Locker?color=blue)  
![GitHub last commit](https://img.shields.io/github/last-commit/yourusername/Dual-MCU-Door-Locker?color=green)  
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)  
![Platform](https://img.shields.io/badge/Platform-ATmega32-blue)  

---

## 📖 Table of Contents
- [📌 Overview](#-overview)
- [✨ Features](#-features)
- [🛠 Hardware Components](#-hardware-components)
- [⚙️ System Architecture](#️-system-architecture)
- [💻 Software & Drivers](#-software--drivers)
- [🚀 Operation Workflow](#-operation-workflow)
- [📂 Repository Structure](#-repository-structure)
- [🎥 Demo & References](#-demo--references)
- [📄 Documentation](#-documentation)
- [👤 Author](#-author)

---

## 📌 Overview  
This project implements a **dual-microcontroller smart door security system** based on the **ATmega32**. It uses **two ECUs** communicating over UART:  

- **HMI_ECU (Human-Machine Interface)** → Provides user interaction through a **16x2 LCD** and a **4x4 keypad**.  
- **Control_ECU** → Controls the **door motor (via H-bridge)**, manages the **EEPROM storage**, handles **buzzer alerts**, and integrates a **PIR motion sensor** for enhanced functionality.  

The system ensures **secure password authentication**, **user-friendly interface**, and **reliable motorized door control**.  

🔑 **Key Idea**: Without the correct password, the door won’t unlock. After 3 failed attempts, the system activates an alarm and locks input for 1 minute.  

---

## ✨ Features  
✅ Password protection with EEPROM storage  
✅ UART communication between two ECUs  
✅ LCD + Keypad interface for user-friendly control  
✅ Motorized door control (unlock/lock) using H-Bridge  
✅ PIR motion detection to hold door open while people enter  
✅ Buzzer alerts for failed attempts & alarms  
✅ Security lock after 3 incorrect attempts (1-minute lockout)  
✅ Option to change password after successful authentication  

---

## 🛠 Hardware Components  

### 🔹 HMI_ECU
- **16x2 LCD (8-bit mode)** → Displays messages and system status  
- **4x4 Keypad** → User input (password entry, options)  
- **UART** → Communication with Control_ECU  

### 🔹 Control_ECU
- **ATmega32 Microcontroller**  
- **External EEPROM (via I2C)** → Stores system passwords  
- **H-Bridge Motor Driver + DC Motor** → Controls door opening/closing  
- **PIR Motion Sensor** → Keeps door open if motion detected  
- **Buzzer** → Alerts for failed authentication  

---

## ⚙️ System Architecture  

```text
+-----------------+            UART            +------------------+
|   HMI_ECU       |  <---------------------->  |   Control_ECU    |
|                 |                            |                  |
| - LCD (16x2)    |                            | - EEPROM (I2C)   |
| - Keypad (4x4)  |                            | - DC Motor (PWM) |
| - UART TX/RX    |                            | - PIR Sensor     |
|                 |                            | - Buzzer         |
+-----------------+                            +------------------+
