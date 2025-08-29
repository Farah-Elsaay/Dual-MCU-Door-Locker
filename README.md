# Dual Microcontroller-Based Door Locker Security System

## Overview
This project implements a **secure smart door control system** using two ATmega32 microcontrollers.  
The system provides **password-based authentication**, **EEPROM storage**, **motorized door control**, and integrates a **PIR motion sensor** and **buzzer** for enhanced security.

It is designed as a **layered architecture** project with reusable embedded C drivers and clear separation between the **Human-Machine Interface (HMI_ECU)** and the **Control ECU**.

---

## Features
- 🔑 **Password Protection** – 5-digit password stored in external EEPROM
- 📟 **LCD & Keypad Interface** – user-friendly control
- 🔗 **UART Communication** – HMI_ECU ↔ Control_ECU
- 💾 **EEPROM Storage** – secure password storage
- ⚙️ **Motorized Door Control** – open/close using H-bridge
- 🚨 **Buzzer Alerts** – failed attempts & security alarms
- 👀 **PIR Motion Sensor** – keeps door open while people enter
- 🔒 **Security Lockout** – system locks after 3 incorrect attempts

---

## System Architecture

**Block Diagram**


- **HMI_ECU**: LCD, keypad, UART interface
- **Control_ECU**: EEPROM, motor control, buzzer, PIR sensor

---

## Operation Flow
1. **Set Password** – user enters and confirms a 5-digit password.
2. **Main Menu** – choose between opening the door or changing the password.
3. **Open Door**  
   - Enter password → verified against EEPROM.  
   - If correct → motor unlocks door → PIR keeps it open while detecting motion → motor locks door when motion stops.  
   - If incorrect → system gives 3 attempts → buzzer + lockout on failure.
4. **Change Password** – requires entering the old password successfully.

---

## Hardware Components
- ATmega32 (x2)  
- 16x2 LCD (HMI_ECU)  
- 4x4 Keypad (HMI_ECU)  
- External EEPROM (I2C)  
- H-Bridge Motor Driver + DC Motor  
- PIR Motion Sensor (Control_ECU)  
- Buzzer (Control_ECU)

---

## Software & Drivers
The project reuses and extends drivers developed in the course:  

- **GPIO Driver** – general I/O control  
- **UART Driver** – serial communication (configurable struct-based init)  
- **LCD Driver** – 8-bit data mode  
- **Keypad Driver** – 4x4 matrix keypad scanning  
- **I2C Driver** – for EEPROM communication  
- **PWM Driver** – motor speed control (Timer0)  
- **Timer Driver** – configurable for delays and timing  
- **Buzzer Driver** – simple ON/OFF control  
- **PIR Driver** – motion detection  

---

## Demo & Documentation
- 📺 [System Demo Video](https://youtu.be/X5EwIRfGAAY)  
- 📄 [Final Project Report (PDF)](Documentation/Final_Project.pdf)



