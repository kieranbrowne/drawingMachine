#!/bin/bash
ln -s arduino/stdFirmataPlusServo/src/sketch.ino arduino/stdFirmataPlusServo/stdFirmataPlusServo
clear
address=$(cat machine.config | grep serialAddress | sed 's/\s\s*/ /g' | cut -d' ' -f3)
echo ATTEMPTING CONNECTION WITH PORT $address
sleep 1

cd arduino/stdFirmataPlusServo
echo BUILDING FIRMATA
ino build 

echo UPLOADING FIRMATA
ino upload -p $address
