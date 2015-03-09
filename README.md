# 雪他 (Yukita) Arduino Code V0.3.0
## Notes:
- In this version we adjusted the code to constanly send the ip address and the version of code to TouchOSC so that the rx light (red) would flash letting the user know it was connected.
- The plowcodding was changed to just one section of code; this was done just to discover different ways to move the plow. At this point we do not have a working plow idea. 

## Hardware:
- Router
- Ethernet Shield
- Arduino Uno (We only tested using an Uno)
- LED for the simulation of each motor control
- LED for the simulation of lights
- LED for the simulation of the plow

## Software: 
- Arduino IDE
- TouchOSC app (other OSC apps may work, but the layout provided is in TouchOSC format and we only test using TouchOSC)
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
- The Yukita page provides information about Yukita.
    -    IP address is synced via code to the controller device as well as the code version
    -    Curret time can be found on the same page
    -    current battery life of controller can also be found

## Manifest:
Incompassing files:
- Arduino3.touchosc
    - TouchOSC Layout
- ArduinoOSC_Test3.ino
    - The Arduino code
- Yukita_Diagram_V0.3.0.png
- Yukita_Diagram_V0.3.0.fzz
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
- Continuous sync of ip address and code vversion to controller

