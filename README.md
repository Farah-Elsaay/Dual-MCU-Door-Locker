# 🔐 Dual Microcontroller-Based Door Locker Security System  

<p align="center">
  <img src="https://img.shields.io/badge/Microcontroller-ATmega32-blue?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Language-C-orange?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Platform-Embedded-green?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Communication-UART-lightgrey?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Simulation-Proteus-yellow?style=for-the-badge"/>
</p>  

A **secure door locker system** built with **two ATmega32 microcontrollers**.  
The project implements **password authentication, motorized door locking, EEPROM storage, PIR motion detection, and buzzer alarms** for enhanced security.  

---

## ✨ Features  

- 🔑 **Password Protection**  
  - 5-digit password stored in external EEPROM (I²C).  
  - Option to change password after successful verification.  

- 📟 **HMI Interface**  
  - 16x2 LCD for displaying messages.  
  - 4x4 Keypad for password input and menu navigation.  

- 🔗 **Dual MCU Communication**  
  - HMI_ECU ↔ Control_ECU via UART.  

- ⚙️ **Motorized Door Control**  
  - H-Bridge + DC Motor.  
  - Unlock (CW rotation), hold open if PIR detects motion, lock (CCW rotation).  

- 👀 **Motion Detection**  
  - PIR sensor keeps the door open while someone is entering.  

- 🚨 **Security Lockout**  
  - 3 wrong attempts → buzzer ON + system lock for 1 minute.  

---

## 🖥️ Hardware Components  

- **2 × ATmega32** @ 8 MHz (HMI_ECU & Control_ECU)  
- **LCD 16x2** (8-bit mode)  
- **Keypad 4x4**  
- **External EEPROM** (I²C)  
- **H-Bridge Motor Driver + DC Motor**  
- **PIR Motion Sensor**  
- **Buzzer**  

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
