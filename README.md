# 🔐 Dual Microcontroller-Based Door Locker Security System  

<p align="center">
  <img src="https://img.shields.io/badge/Microcontroller-ATmega32-blue?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Platform-FreeRTOS-green?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Interface-UART-orange?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Storage-EEPROM-purple?style=for-the-badge"/>
</p>  

## 📌 Project Overview  
This project implements a **smart and secure door control system** using **two ATmega32 microcontrollers**:  

- **HMI_ECU (Human-Machine Interface)** – keypad + LCD for user interaction.  
- **Control_ECU** – handles password verification, EEPROM storage, and motorized door control.  

The system features **password authentication**, **EEPROM-based storage**, **motion detection via PIR**, **buzzer alerts**, and **motor-driven door lock/unlock control**.  
  

---

## 🎯 Objective  
Develop a **secure and efficient smart door locker system** with:  
- Multi-layered architecture  
- UART-based ECU communication  
- Motorized lock/unlock mechanism  
- PIR sensor for enhanced safety  

---

## ⚙️ Features  
- 🔑 **Password Protection** – 5-digit password stored in EEPROM.  
- 📟 **LCD & Keypad Interface** – for input and feedback.  
- 🔄 **UART Communication** – between HMI_ECU & Control_ECU.  
- 💾 **EEPROM Storage** – secure password storage.  
- ⚡ **Motorized Door Control** – using an H-Bridge.  
- 🚨 **Buzzer Alert** – on failed attempts.  
- 🕵️ **PIR Motion Sensor** – keeps door open until motion stops.  
- 🔒 **Security Lock** – locks for 1 min after 3 wrong attempts.  
- 🔄 **Password Change Option** – after verification.  

---

## 🛠️ Hardware Components  
- **ATmega32 Microcontrollers (2x)**  
- **16x2 LCD**  
- **4x4 Keypad**  
- **External EEPROM (I²C)**  
- **DC Motor + H-Bridge**  
- **Buzzer**  
- **PIR Motion Sensor**  

---

## 🧩 System Architecture  

**HMI_ECU**  
- LCD (Port A + PC0, PC1)  
- Keypad (Port B)  
- UART TX/RX  

**Control_ECU**  
- EEPROM via I²C (PC0, PC1)  
- Buzzer (PC7)  
- Motor Control via H-Bridge (PD6, PD7, PB3/OC0)  
- PIR Sensor (PC2)  

---

## 🔄 Operation Flow  
1. **Set Password** – User enters and confirms a 5-digit password.  
2. **Open Door** – Enter password → motor unlocks → PIR detects entry → motor locks.  
3. **Change Password** – Re-enter password → set new one.  
4. **Security Handling** – 3 failed attempts → buzzer + system lock for 1 min.  

---

## 📂 Drivers Implemented  
- **GPIO Driver**  
- **UART Driver (configurable)**  
- **LCD Driver (8-bit mode)**  
- **Keypad Driver**  
- **I²C Driver (EEPROM communication)**  
- **PWM Driver (Timer0 for motor)**  
- **Timer Driver (Timers 0/1/2)**  
- **Buzzer Driver**  
- **PIR Sensor Driver**  
- **DC Motor Driver**  
- **EEPROM Driver**  

---

## 📹 Demo & References  
- 🎥 [Project Demo Video](https://youtu.be/X5EwIRfGAAY)  
- 📚 [How to add PIR sensor to Proteus](https://youtu.be/bhT90bM-Vdw)  

---

## 🚀 Skills Demonstrated  
- Embedded Systems Design  
- C Programming with **FreeRTOS**  
- Microcontroller Interfacing (UART, I²C, GPIO, PWM, Timers)  
- Hardware-Software Co-design  
- Security System Development  

---

 

