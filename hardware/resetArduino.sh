#!/bin/bash
DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

if [ ${1:-foo} = "full" ]; then
    echo ERASING AND REBUILDING INO
    rm -r $DIR/arduino/stdFirmataPlusServo/ino 
    mkdir $DIR/arduino/stdFirmataPlusServo/ino 
    cd  $DIR/arduino/stdFirmataPlusServo/ino
    ino init
    cd ../../../
fi

cp $DIR/arduino/stdFirmataPlusServo/stdFirmataPlusServo.ino $DIR/arduino/stdFirmataPlusServo/ino/src/sketch.ino 

address=$(bash $DIR/getArd.sh)
echo ATTEMPTING CONNECTION WITH PORT $address
sleep 1

cd $DIR/arduino/stdFirmataPlusServo/ino
echo BUILDING FIRMATA
ino build -m mega2560

echo UPLOADING FIRMATA
ino upload -p $address
