#pragma once

#include "ofMain.h"
#include "ofEvents.h"


class ofApp : public ofBaseApp{

public:

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

	ofTrueTypeFont		font;
    ofTrueTypeFont      smallFont;
	ofArduino	motorA;
    ofArduino   motorB;
	bool		bSetupArduino;	// flag variable for setting up arduino once
    int    dirPin;
    int    stepPin;
    float  SPN; // steps per notch

    int n; // step divider (as in "8" for eighth steps)

    float MSEP; // distance in notches between motors
    float AX; // motor co-ords
    float BX;
    int   MASteps; // number of steps away from motor
    int   MBSteps;

    float distGraph[10] = {};
    
private:
    
    float getCurrentX();
    float getCurrentY();
    float maxValueIn(float array[]);
    void movePointerTo(float newX, float newY);
    void straightLineTo(float newX, float newY);
    void updateDistGraph(int n);
    void drawing(bool d);
    void setMicroSteps(const int & version);
    void setupArduino(const int & version);
	void updateArduino();
};

