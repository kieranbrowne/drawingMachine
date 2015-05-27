#!/bin/bash
if [ -a /dev/ttyACM* ]
then 
    #echo `ls /dev/ttyACM* | head -1 | cut -d'/' -f3`
    echo `ls /dev/ttyACM* | head -1`
elif [ -a /dev/ttyUSB* ]
then
    #echo `ls /dev/ttyUSB* | head -1 | cut -d'/' -f3`
    echo `ls /dev/ttyUSB* | head -1`
fi
