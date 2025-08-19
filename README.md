
# Automatic Cat Feeder

## Overview
This project is an Automatic Cat Feeder designed and built as an embedded systems project. The system automates the process of feeding a cat at scheduled times, with remote control and monitoring capabilities. It integrates hardware and software components, including a microcontroller, motor control, WiFi communication, and a user interface.

## Features
- Scheduled feeding times with precise portion control
- Manual feed option via remote interface (Blynk app)
- WiFi connectivity using ESP8266 for remote monitoring and control
- Motorized dispensing mechanism
- LCD display for status updates
- Safety and error handling (e.g., jam detection)

## Hardware
- Microcontroller (e.g., STM32 or TM4C123)
- ESP8266 WiFi module
- Stepper or DC motor for food dispensing
- LCD display (e.g., Nokia5110 or AGM1264F)
- Power supply and supporting circuitry
- Custom PCB (see `HW/` folder for schematics and board files)

## Software
- Written in C for embedded systems
- Modular code structure (see `inc/` for drivers and modules)
- Real-time scheduling and timer management
- WiFi communication handled via ESP8266 module
- Blynk integration for mobile app control

## Usage
1. Assemble the hardware as per the provided schematics in the `HW/` folder.
2. Flash the firmware to the microcontroller using the provided source files.
3. Connect the ESP8266 module and configure WiFi credentials.
4. Use the Blynk app to monitor and control feeding remotely.
5. LCD displays current status and feeding schedule.

## Project Structure
- `main.c` - Main application logic
- `MotorControl.c` - Motor driver and control logic
- `esp8266.c`/`esp8266.h` - WiFi communication
- `Timer2.c`, `Timer3.c` - Timer modules for scheduling
- `inc/` - Peripheral drivers and hardware abstraction
- `HW/` - Schematics, PCB layout, and hardware resources

## Pictures
<!-- Drop your first project picture here -->
![Project Picture 1](path/to/your/picture1.jpg)

<!-- Drop your second project picture here -->
![Project Picture 2](path/to/your/picture2.jpg)

## Credits
Developed for EE 445L Embedded Systems coursework, 2022.

---
*For more details, see the code comments and hardware documentation in the repository.*

