#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    n = 8; // divisions per step

	ofSetVerticalSync(true);
	ofSetFrameRate(60);

	ofBackground(40,40,40);
    
	font.loadFont("franklinGothic.otf", 20);
    smallFont.loadFont("franklinGothic.otf", 14);

    dirPin = 7;
    stepPin = 6;

    MSEP = 152.0;
    AX   = 0.0;
    BX   = AX+MSEP;

    SPN = 12.5;
    /* N.B. 
     * each step is 0.225 degrees
     * there are 1600 steps to a full motor rotation
     * each motor is 100 notches from the pen at the start
     * there are 100 steps to a full notch turn
     */
    MASteps = 1250*n; // with these settings the pointer
    MBSteps = 1250*n; // will start at x=76, y=65.

	motorA.connect("/dev/ttyACM0", 57600);
	motorB.connect("/dev/ttyACM1", 57600);
	
	ofAddListener(motorA.EInitialized, this, &ofApp::setMicroSteps);
	ofAddListener(motorB.EInitialized, this, &ofApp::setupArduino);
	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
}
void ofApp::setMicroSteps(const int & version){
    // set required stepper pins to output 
    for(int i=6; i<=9; i++) motorA.sendDigitalPinMode(i, ARD_OUTPUT);
    for(int i=6; i<=9; i++) motorB.sendDigitalPinMode(i, ARD_OUTPUT);
}
//--------------------------------------------------------------
void ofApp::update(){
	updateArduino();
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(motorA.EInitialized, this, &ofApp::setMicroSteps);
	ofRemoveListener(motorB.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    

    // set pin D13 as digital output
	motorA.sendDigitalPinMode(13, ARD_OUTPUT);
	motorB.sendDigitalPinMode(13, ARD_OUTPUT);

    // draw on/off servo
//    motorA.sendServoAttach(10);

}

//--------------------------------------------------------------
float ofApp::getCurrentX(){
    float x;
    x = (pow((MASteps)/(SPN*n),2)-pow((MBSteps)/(SPN*n),2)-pow(AX,2)+pow(BX,2))/(2*(BX-AX));
    cout << "Current X is " << ofToString(x) <<endl;
    return x;
}
//--------------------------------------------------------------
float ofApp::getCurrentY(){
    float x,y;
    x = (pow((MASteps)/(SPN*n),2)-pow((MBSteps)/(SPN*n),2)-pow(AX,2)+pow(BX,2))/(2*(BX-AX));
    y =  pow(MASteps/(SPN*8),2)-pow(x-AX,2);
    if(y<=0){cout << "Y less than 0!!!!" << endl;}else{y=sqrt(y);}
    cout << "Current Y is " << ofToString(y) <<endl;
    return y;
}
//--------------------------------------------------------------
void ofApp::movePointerTo(float newX, float newY){
    ofSleepMillis(30);

    int newAsteps = floor(sqrt(pow(newY,2)+pow(newX-AX,2))*(SPN*n));
    int newBsteps = floor(sqrt(pow(newY,2)+pow(newX-BX,2))*(SPN*n));
    
    int changeA = newAsteps - MASteps;
    int changeB = newBsteps - MBSteps;

//    cout << "motor A changing " << ofToString(changeA) << " steps." << endl;
//    cout << "motor B changing " << ofToString(changeB) << " steps." << endl;

    if(changeA > 0){
        motorA.sendDigital(dirPin, ARD_HIGH); // CCW
    }else if(changeA < 0){
        motorA.sendDigital(dirPin, ARD_LOW);  // CW
    }

    for(int i=0; i<=abs(changeA); i++){
        motorA.sendDigital(stepPin,ARD_HIGH);
        ofSleepMillis(3);
        motorA.sendDigital(stepPin,ARD_LOW);
        ofSleepMillis(3);
    }

    if(changeB > 0){
        motorB.sendDigital(dirPin, ARD_HIGH); // CCW
    }else if(changeB < 0){
        motorB.sendDigital(dirPin, ARD_LOW);  // CW
    }
    for(int i=0; i<=abs(changeB); i++){
        motorB.sendDigital(stepPin,ARD_HIGH);
        ofSleepMillis(3);
        motorB.sendDigital(stepPin,ARD_LOW);
        ofSleepMillis(3);
    }

    MASteps = newAsteps;
    MBSteps = newBsteps;

}

// --------------------------------------------------
void ofApp::straightLineTo(float newX, float newY){
    ofVec2f start(getCurrentX(),getCurrentY());
    ofVec2f pos(getCurrentX(),getCurrentY());
    ofVec2f end(newX,newY);
    float dist = start.distance(end);
    cout << "Distance from current pos to new co-ords is " << ofToString(dist) << endl;
    float stepSize = 0.1/dist;
    for(float i=stepSize; i<=1; i+=stepSize){
        if(i>1) i=1;
        pos.interpolate(end, i);
        movePointerTo(pos.x,pos.y);
        //dist = pos.distance(end);
//        cout << ofToString(dist) << endl;
        pos.set(start.x,start.y);
    }
}

        
// --------------------------------------------------
void ofApp::drawing(bool d){
 //   if(d) motorA.sendServo(10,10,false);
 //   if(!d) motorA.sendServo(10,80,false);
}
    
//--------------------------------------------------------------
void ofApp::updateArduino(){

	motorA.update();
	motorB.update();
	
	// do not send anything until the arduino has been set up
	if (bSetupArduino) {
        // set steps to eigth    
        motorA.sendDigital(8, ARD_HIGH);
        motorA.sendDigital(9, ARD_HIGH);
        motorB.sendDigital(8, ARD_HIGH);
        motorB.sendDigital(9, ARD_HIGH);

        // DRAWING INSTRUCTIONS
        //float x,y;
        //x = getCurrentX();
        //y = getCurrentY();
        float newX = 50;
        float newY = 50;
        for (int i=0; i<=100; i++){
          straightLineTo(newX,newY);

          //x = getCurrentX();
          newX += ofRandom(-5,5);
          newY += ofRandom(-5,5);
          if(newX>60) newX-=5;
          if(newX<50) newX+=5;
          if(newY>60) newY-=5;
          if(newY<50) newY+=5;
          cout << "new target position is x:" << ofToString(newX) << " y:" << ofToString(newY) << endl;
          cout << "Pointer is " << ofToString(MASteps) <<" from motorA." <<endl;
          cout << "Pointer is " << ofToString(MBSteps) <<" from motorB." <<endl;

        }
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(0, 0, 0, 127);
    ofRect(510, 15, 275, 150);
    ofNoFill();
    ofSetColor(255,255,255);
    ofRect(510, 15, 275, 150);
    ofDisableAlphaBlending();
    
    ofSetColor(255, 255, 255);
	if (!bSetupArduino){
		font.drawString("arduino not ready...\n", 515, 40);
	} else {
		font.drawString("\nsending pwm: " + ofToString((int)(128 + 128 * sin(ofGetElapsedTimef()))), 515, 40);
        
        ofSetColor(64, 64, 64);
        smallFont.drawString("If a servo is attached, use the left arrow key to rotate " 
                             "\ncounterclockwise and the right arrow key to rotate clockwise.", 200, 550);
        ofSetColor(255, 255, 255);

	}
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
