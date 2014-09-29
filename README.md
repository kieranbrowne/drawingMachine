#DUAL-MOTOR DRAWING MACHINE
A dual stepper motor drawing machine.
The system can be seen in action [here.](http://youtu.be/ItNGdXCSbFE)

###Hardware
- Two Arduino Unos loaded with `StandardFirmata.ino`
- Two ITE-IM120417015 Stepper Shields
- Two 57BYGH420 unipolar stepper motors

###Software
The arduino serial addresses in `ofApp::setup()` (see below) may vary system-to-system.
```
	motorA.connect("/dev/ttyACM0", 57600);
	motorB.connect("/dev/ttyACM1", 57600);
```
A list of connected serial devices can be accesses via the terminal:
- Linux: `ls /dev/ttyACM*`
- OSX: `ls /dev/tty.*`

