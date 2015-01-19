#DUAL-MOTOR DRAWING MACHINE
A dual stepper motor drawing machine.
The system can be seen in action [here.](http://youtu.be/ItNGdXCSbFE)

###Hardware
- Arduino Mega 2560 R3
- Two EasyDriver Stepper Motor Drivers
- Two 57BYGH420 unipolar stepper motors

###Software
The arduino serial address in `ofApp::setup()` (see below) may vary system-to-system.
```
	ard.connect("/dev/ttyACM0", 57600);
```
A list of connected serial devices can be accesses via the terminal:
- Linux: `ls /dev/ttyACM*`
- OSX: `ls /dev/tty.*`

