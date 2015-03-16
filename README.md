#DUAL-MOTOR DRAWING MACHINE
A dual stepper motor drawing machine.
The system can be seen in action [here.](http://youtu.be/ItNGdXCSbFE)

###Hardware
- Arduino Mega 2560 R3
- Two EasyDriver Stepper Motor Drivers
- Two 57BYGH420 unipolar stepper motors
- One HD-1600A micro servo
The basic setup for the system can seen in the ```isometricSchematic.ai``` file.

###Software
The arduino serial address in `ofApp::setup()` (see below) may vary system-to-system.
```
	ard.connect("/dev/ttyACM0", 57600);
```
A list of connected serial devices can be accesses via the terminal:
- Linux: `ls /dev/ttyACM*`
- OSX: `ls /dev/tty.*`

###Setup
Make a copy of ```machine.config.template``` named ```machine.config``` and edit the values to match the perticular context
