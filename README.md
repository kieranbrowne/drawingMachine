#DUAL-MOTOR DRAWING MACHINE
A dual stepper motor drawing machine.
The system can be seen in action [here.](http://youtu.be/ItNGdXCSbFE)

###Hardware
- Arduino Mega 2560 R3
- Two EasyDriver Stepper Motor Drivers
- Two 57BYGH420 unipolar stepper motors
- One HD-1600A micro servo
The basic setup for the system can seen in ```hardware/isometricSchematic.ai```

###Software
The arduino serial address in `ofApp::setup()` (see below) may vary system-to-system.
```
	ard.connect("/dev/ttyACM0", 57600);
```
A list of connected serial devices can be accesses via the terminal:
- Linux: `ls /dev/ttyACM*`
- OSX: `ls /dev/tty.*`

###Setup
1. In the ```harware``` directory, make a copy of ```machine.config.template``` named ```machine.config``` and edit the values to match the perticular context.
2. Place ```data``` file in the ```bin/data/``` directory.
3. Run ```make``` to compile.
4. Run ```make run``` to run the code ~or~ ```cd bin``` then ```./drawingMachine v``` to run with visual debugging enabled.
