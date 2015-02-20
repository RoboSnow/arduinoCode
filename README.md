# 雪他 (Yukita) Arduino Code V0.2.0
## Notes:
- In this version we rewrote the code to be more realistic to what we would need to drive Yukita. We added code to control lights, left and right hdraulic motors, and control the plow.
    - The plow code is theoratical at this point because we are unsure of how it is going to work.
- The circuit diagram provided is in the [Fritzing](http://fritzing.org/home/) format; a .png version is also provided.

## Hardware:
- Router
- Ethernet Shield
- Arduino Uno (We only tested using an Uno)
- LED for the simulation of each motor control
- LED for the simulation of lights
- LED for the simulation of the plow

## Software: 
- Arduino IDE
- TouchOSC app (other OSC apps may work, but the layout provided is in TouchOSC format)
- [TouchOSC Editor](http://hexler.net/software/touchosc)

## Installation:
After the installation of the Arduino IDE, TouchOSC app and TouchOSC Editor:
- Sync the layout to your device using TouchOSC Editor
- Upload the code to your Arduino

## Operation:
After uploading the code to your arduino and the layout to the app:
- The control page provides the basic controls. 
    - All controls are toggle buttons
    - forward = both motor toggles pressed (both motor LEDs on)
    - turn = only the right or left motor toggle pressed (only one motor LED on)
- Lights turn on and off via the "light" toggle (lights LEDs on or off)
- Plow toggle turns plow LEDs on or off (plow LEDs on or off)

## Manifest:
Incompassing files
- Arduino2.touchosc
    - TouchOSC Layout
- ArduinoOSC_Test2.ino
    - The Arduino code
- Yukita_Diagram_V0.2.0.png
- Yukita_Diagram_V0.2.0.fzz
- COPYING.md
    - Licensing file
- README.md
    - This file

## License:
- GNU GPLV3
- See COPYING.md for license information

## Support:
- If you have any questions or problems feel free to email us at 234111@shakopeeschools.org
- Also see [trippylighting's blog](http://trippylighting.com/teensy-arduino-ect/touchosc-and-arduino-oscuino/) for more information regaurding OSCuino

## ChangeLog:
- Added motor control 
- Added lighting control
- Added plow control*
    -  Code works, but we did not relate this to an actual design

