# IR-Controlled Fan and RGB LED System

This project combines two Arduino-based systems: an IR-controlled fan and an IR-controlled RGB LED. Both systems use an infrared remote control for user input, demonstrating the versatility of IR communication in home automation and lighting control.

## Project Structure

This repository contains two main Arduino files, each representing a separate but similar project:

1. `fan_control.ino`: Controls a DC fan using IR remote inputs.
2. `rgb_control.ino`: Manages an RGB LED using the same IR remote.

While these projects are separate, they share similar IR decoding logic and can be used with the same remote control.

## Features

### Fan Control System ('fan_control.ino')
- Control fan speed using IR remote
- 9 speed levels (0-9)
- Forward and reverse direction control
- Gradual speed increase/decrease

### RGB LED Control System ('rgb_control.ino')
- Control RGB LED colors using IR remote
- 6 preset colors
- Adjustable brightness
- On/Off functionality

## Hardware 

- Arduino Uno 
- IR Receiver module 
- 5V DC fan
- RGB LED
- IR Remote Control
- Resistors and wires 
