##DUAL-MOTOR DRAWING MACHINE

<img src="https://41.media.tumblr.com/269bf3102520f8b19f56dcfaaccf9131/tumblr_nlpybstm5a1r0bfx2o1_r1_540.png"
align="left" width="400">

####Hardware
1. 57BYGH420 unipolar stepper motor
2. HD-1600A micro servo
3. MDF (or other) mounting board
4. 2m timing belt
5. A3 paper

####Circuitry
- Two EasyDriver Stepper Motor Drivers
- Arduino Mega 2560 R3

####Serial
To correctly communicate with the arduino, the serial address must be edited in ```machine.config``` By default it is set to ```/dev/ttyACM0```.
A list of connected serial devices can be accessed via the terminal:

Linux: ```ls /dev/ttyACM*```
OSX: ```ls /dev/tty.*```

####Software Dependencies
- [openFrameworks 0.8.4 +](http://openframeworks.cc/download/)
- Python 2.6 +
- [Arduino](http://arduino.cc/en/Main/Software)
- [Ino](https://github.com/amperka/ino)

####Setup
1. In the ```harware``` directory, make a copy of ```machine.config.template``` named ```machine.config``` and edit the values to match the perticular context.
2. Place ```dataexample``` file to ```bin/data/data``` 
3. ```make``` to compile.
4. ```make run``` to run the code ~or~ ```cd bin``` then ```./drawingMachine v``` to run with visual debugging enabled.

This system can be seen in action [here.](https://youtu.be/FjZdq7ek0DU)
