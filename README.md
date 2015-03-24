##DUAL-MOTOR DRAWING MACHINE

<img src="https://40.media.tumblr.com/1f072dc075d0fd5d0a0e924f1a19a47d/tumblr_nlpybstm5a1r0bfx2o1_500.png"
align="left">

####Hardware
- Arduino Mega 2560 R3
- Two EasyDriver Stepper Motor Drivers
- Two 57BYGH420 unipolar stepper motors
- One HD-1600A micro servo

####Serial
To correctly communicate with the arduino, the serial address must be edited in ```machine.config```. By default it is set to ```/dev/ttyACM0```.
A list of connected serial devices can be accesses via the terminal:
- Linux: ```ls /dev/ttyACM*```
- OSX: ```ls /dev/tty.*```

####Software Dependencies
- [openFrameworks 0.8.4 +](http://openframeworks.cc/download/)
- Python 2.6 +
- [Arduino](http://arduino.cc/en/Main/Software)
- [Ino](https://github.com/amperka/ino)







####Setup
1. In the ```harware``` directory, make a copy of ```machine.config.template``` named ```machine.config``` and edit the values to match the perticular context.
2. Place ```data``` file in the ```bin/data/``` directory.
3. Run ```make``` to compile.
4. Run ```make run``` to run the code ~or~ ```cd bin``` then ```./drawingMachine v``` to run with visual debugging enabled.

This system can be seen in action [here.](https://youtu.be/FjZdq7ek0DU)
