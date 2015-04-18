#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include <iostream>
#include <sstream>


class ofApp : public ofBaseApp{

public:

    bool visual; 

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);

	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


	ofTrueTypeFont	font;
    ofTrueTypeFont  smallFont;
	ofArduino	ard;
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
               dps;   // delay per step
        string sa;    // serial address
    } m;

    float distGraph[10];
    
private:
    
    float getCurrentX();
    float getCurrentY();
    float maxValueIn(float array[]);
    void movePointerTo(float newX, float newY);
    void straightLineTo(float newX, float newY);
    void updateDistGraph(int n);
    void readDatatoCoords(string filepath);
    void readLastPos(string filepath);
    void writeLastPos(string filepath);
    void calibrate();
    void drawing(int d);
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
	void updateArduino();
};

