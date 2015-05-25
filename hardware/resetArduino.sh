#!/bin/bash
if [ ${1:-foo} = "full" ]; then
    echo ERASING AND REBUILDING INO
    rm -r arduino/stdFirmataPlusServo/ino 
    mkdir arduino/stdFirmataPlusServo/ino 
    cd  arduino/stdFirmataPlusServo/ino
    ino init
    cd ../../../
fi
cp arduino/stdFirmataPlusServo/stdFirmataPlusServo.ino arduino/stdFirmataPlusServo/ino/src/sketch.ino 

address=$(cat machine.config | grep serialAddress | sed 's/\s\s*/ /g' | cut -d' ' -f3)
echo ATTEMPTING CONNECTION WITH PORT $address
sleep 1

cd arduino/stdFirmataPlusServo/ino
echo BUILDING FIRMATA
ino build -m mega2560

echo UPLOADING FIRMATA
ino upload -p $address
