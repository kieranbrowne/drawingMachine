#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include <iostream>
#include <sstream>

using namespace std;

class ofApp : public ofBaseApp{

public:
    bool visual; 
    void setup();
    void update();
    void draw();

    ofTrueTypeFont font;
    ofTrueTypeFont smallFont;	
    ofArduino ard;
    bool   bSetupArduino;	// flag variable for setting up arduino once
    int    aDir, aStp, bDir, bStp, sbd1, sbd2;
    float  SPN; // steps per notch

    int count;

    int numCoords;
    float coord [9000000][3];

    float MSEP; // distance in notches between motors
    float AX; // motor co-ords
    float BX;
    int   MASteps; // number of steps away from motor
    int   MBSteps;
    
    string positionFile;
    string serialAddress;

    string removeSpaces(string input);

    int currentDraw;

    struct machine
    {
        float  ms,    // dist between stepper shafts (mm)
               bl,    // belt length (mm)
               bp,    // belt pitch (mm)
               gr,    // gear reduction
               sr;    // step reduction
        int    spr,   // steps per full stepper rotation
               npr,   // notches per full stepper rotation
               dps,   // delay per step
               dcd,   // delay per change in drawing state
               sn;    // set notches
    } m;

    float distGraph[10];
    
private:
    
    float getCurrentX();
    float getCurrentY();
    float maxValueIn(float array[]);
    bool turnStepperMotor(char motor, int steps);
    void movePointerTo(float newX, float newY);
    void straightLineTo(float newX, float newY);
    void updateDistGraph(int n);
    void readDatatoCoords(string filepath);
    void initialiseLocation();
    bool readSetNotch();
    bool readLastPos(string filepath);
    void writeLastPos(string filepath);
    void calibrate();
    void drawing(int d);
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
	void updateArduino();
};

