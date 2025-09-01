# 🔐 Dual Microcontroller-Based Door Locker Security System  

<p align="center">
  <img src="https://img.shields.io/badge/Microcontroller-ATmega32-blue?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Language-C-orange?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Platform-Embedded-green?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Communication-UART-lightgrey?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Simulation-Proteus-yellow?style=for-the-badge"/>
</p>  

A **secure smart door control system** using **two ATmega32 microcontrollers**.  
The system features **password authentication, motorized door locking, EEPROM storage, PIR motion detection, and buzzer alarms**.  

---

## ✨ Features  

- 🔑 **Password Authentication**  
  - Stored in **external EEPROM (I²C)**  
  - Secure access with verification and change option  

- 📟 **HMI Interface**  
  - 16x2 LCD for system messages  
  - 4x4 Keypad for password input  

- 🔗 **Dual MCU Communication**  
  - HMI_ECU ↔ Control_ECU via **UART**  

- ⚙️ **Door Control**  
  - DC Motor + H-Bridge  
  - Unlock (CW rotation), hold with PIR, lock (CCW rotation)  

- 👀 **Motion Detection**  
  - PIR sensor keeps the door open while movement is detected  

- 🚨 **Security Lockout**  
  - 3 failed attempts → buzzer ON + 1-minute lock  

---

## 🖥️ Hardware Components  

- **Microcontrollers:** 2 × ATmega32 @ 8 MHz  
- **Input Devices:** 4x4 Keypad, PIR Sensor  
- **Output Devices:** 16x2 LCD, Buzzer, DC Motor (via H-Bridge)  
- **Memory:** External EEPROM (I²C)  

---

## ⚙️ System Architecture  

```mermaid
flowchart TD
    User[User] --> |Password Input| HMI[HMI_ECU<br/>LCD + Keypad]
    HMI --> |UART| CTRL[Control_ECU]
    CTRL --> |I²C| EEPROM[External EEPROM]
    CTRL --> |PWM + H-Bridge| Motor[DC Motor + Door]
    CTRL --> PIR[PIR Motion Sensor]
    CTRL --> Buzzer[Buzzer]

---

## Demo & Documentation
- 📺 [System Demo Video](https://youtu.be/X5EwIRfGAAY)  
- 📄 [Final Project Report (PDF)](Documentation/Final_Project.pdf)



