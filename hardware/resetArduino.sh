#!/bin/bash
clear
cd arduino/stdFirmataPlusServo
echo BUILDING FIRMATA
ino build 
clear
echo UPLOADING FIRMATA
sleep 3
ino upload
