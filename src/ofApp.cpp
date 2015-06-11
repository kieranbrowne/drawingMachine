#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // read machine.config file
    ifstream fin("../hardware/machine.config");
    int num; string name; string value;
    while (fin >> num >> name >> value)
    {
       switch (num)
       {
           case 1  : m.ms  = ofToFloat(value); break;
           case 2  : m.bl  = ofToFloat(value); break;
           case 3  : m.bp  = ofToFloat(value); break;
           case 4  : m.gr  = ofToFloat(value); break;
           case 5  : m.sr  = ofToFloat(value); break;
           case 6  : m.spr = ofToInt(value);   break;
           case 7  : m.npr = ofToInt(value);   break;
           case 8  : m.dps = ofToInt(value);   break;
           case 9  : m.dcd = ofToInt(value);   break;
           case 10 : m.sn  = ofToInt(value);   break;
           default : 
               cout << "ERROR: value " << name 
                    << " is missing." << endl;
               ofSleepMillis(2000); break;
       }
    }


    // get serial address of arduino
    FILE* script = popen("../hardware/getArd.sh","r");
    while(!feof(script)){
        char buffer[128];
        if(fgets(buffer,128,script) !=NULL)
            serialAddress = removeSpaces(ofToString(buffer));
        break;
    }
    pclose(script);


    count = 0; //instructions counter
    ofSetFrameRate(30);

    numCoords = 0;

    if(visual){
        ofSetVerticalSync(true);
        ofBackground(40,40,40);
        font.loadFont("franklinGothic.otf", 12);
        smallFont.loadFont("franklinGothic.otf", 10);
    }

    //arduino pins
    aDir = 12;  aStp = 13;
    bDir = 9;   bStp = 8;
    sbd1 = 3;   sbd2 = 4; // standoff binary digits

    currentDraw = 1;
    
    AX  = 0.0;
    BX  = AX+(m.ms/m.bp);
    cout << "dist between motors: " << BX << endl;
    ofSleepMillis(3000);

    SPN = m.spr/m.sr/m.gr/m.npr;
    positionFile = "lastPos";
	
    ard.connect(serialAddress, 57600);
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = false;

    readDatatoCoords("data/data");
}
//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();
}
//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino = true;

    ard.sendDigitalPinMode(aDir, ARD_OUTPUT);
    ard.sendDigitalPinMode(aStp, ARD_OUTPUT);
    ard.sendDigitalPinMode(bDir, ARD_OUTPUT);
    ard.sendDigitalPinMode(bStp, ARD_OUTPUT);
    // draw on/off servo
    ard.sendDigitalPinMode(sbd1, ARD_OUTPUT);
    ard.sendDigitalPinMode(sbd2, ARD_OUTPUT);
}
//--------------------------------------------------------------
float ofApp::getCurrentX(){
    return (
        (pow(MASteps/SPN,2)
        -pow(MBSteps/SPN,2)
        -pow(AX,2)+pow(BX,2))
        /(2*(BX-AX))
    );
}
//--------------------------------------------------------------
float ofApp::getCurrentY(){
    return (
        sqrt(pow(MASteps/SPN,2)-pow(getCurrentX()-AX,2))
    );
}
//--------------------------------------------------------------
bool ofApp::turnStepperMotor(char motor, int steps){
    int stpPin;
    switch (motor){
        case 'A':
            stpPin = aStp;
            if(steps > 0){
                ard.sendDigital(aDir, ARD_HIGH);  // CW
            }else{
                ard.sendDigital(aDir, ARD_LOW); // CCW
            }
            break;
        case 'B':
            stpPin = bStp;
            if(steps > 0){
                ard.sendDigital(bDir, ARD_LOW); // CCW
            }else{
                ard.sendDigital(bDir, ARD_HIGH);  // CW
            }
            break;
        default:
            return false;
    }

    for(int i=0; i<abs(steps); i++){
        ard.sendDigital(stpPin,ARD_LOW);
        ard.sendDigital(stpPin,ARD_HIGH);
        ofSleepMillis(m.dps);
    }
    return true;
}

//--------------------------------------------------------------
void ofApp::movePointerTo(float newX, float newY){
    int newAsteps = floor(sqrt(pow(newY,2)+pow(newX-AX,2))*SPN);
    int newBsteps = floor(sqrt(pow(newY,2)+pow(newX-BX,2))*SPN);
    
    int changeA = newAsteps - MASteps;
    int changeB = newBsteps - MBSteps;

    if(changeA != 0) {if(turnStepperMotor('A',changeA)) MASteps = newAsteps;}
    if(changeB != 0) {if(turnStepperMotor('B',changeB)) MBSteps = newBsteps;}
}
//--------------------------------------------------------------
void ofApp::straightLineTo(float newX, float newY){
    ofVec2f start(getCurrentX(),getCurrentY());
    ofVec2f pos(getCurrentX(),getCurrentY());
    ofVec2f end(newX,newY);
    float dist = start.distance(end);
    updateDistGraph(floor(dist));
    cout << " | d:" << ofToString(dist) << endl;
    float stepSize = (m.sr*m.gr)/dist;
    for(float i=stepSize; i<=1; i+=stepSize){
        if(i>1) i=1;
        pos.interpolate(end, i);
        movePointerTo(pos.x,pos.y);
        pos.set(start.x,start.y);
    }
}
//--------------------------------------------------------------
void ofApp::updateDistGraph(int n){
    for(int i=10;i>0;i--){
        distGraph[i] = distGraph[i-1];
    }
    distGraph[0] = n;
}
//--------------------------------------------------------------
void ofApp::drawing(int d){
    if(currentDraw != d){
        switch(d)
        {
            case 0:
                ard.sendDigital(sbd1,ARD_LOW);
                ard.sendDigital(sbd2,ARD_LOW);
                currentDraw = d;
                ofSleepMillis(m.dcd*1000);
                break;
            case 1:
                ofSleepMillis(m.dcd*1000);
                ard.sendDigital(sbd1,ARD_HIGH);
                ard.sendDigital(sbd2,ARD_LOW);
                currentDraw = d;
                break;
            case 2:
                ofSleepMillis(m.dcd*1000);
                ard.sendDigital(sbd1,ARD_LOW);
                ard.sendDigital(sbd2,ARD_HIGH);
                currentDraw = d;
                break;
            case 3:
                ofSleepMillis(m.dcd*1000);
                ard.sendDigital(sbd1,ARD_HIGH);
                ard.sendDigital(sbd2,ARD_HIGH);
                currentDraw = d;
                break;
            default:
                cout << "Error setting standoff" << endl;
                break;
        }
    }
}
//--------------------------------------------------------------
void ofApp::readDatatoCoords(string filepath){
    ifstream file(filepath.c_str());
    while (file)
    {
        string line;
        getline(file,line);
        istringstream row(line);
        int j=0;
        while (row)
        {
            switch(j){
                case 0: row >> coord[numCoords][0]; j++; break;
                case 1: row >> coord[numCoords][1]; j++; break;
                case 2: row >> coord[numCoords][2]; j++; break;
                default: break;
            }
            if(j>2)break;
        }
        numCoords++;
    }
}
//--------------------------------------------------------------
void ofApp::initialiseLocation(){
    if(readLastPos(positionFile)){}
    else if(readSetNotch()){}
    else calibrate(); 
}
//--------------------------------------------------------------
bool ofApp::readSetNotch(){
    int steps = m.sn*SPN;
    MASteps = steps;
    MBSteps = steps;
    return true;
}
//--------------------------------------------------------------
bool ofApp::readLastPos(string filepath){
    ifstream file(filepath.c_str());
    if (file.is_open()){
        string line;
        getline(file,line);
        MASteps = ofToInt(line);
        getline(file,line);
        MBSteps = ofToInt(line);
        file.close();
        remove(filepath.c_str());
        return true;
    }else{
        return false;
    }
}
//--------------------------------------------------------------
void ofApp::writeLastPos(string filepath){
    ofstream file(filepath.c_str());
    if (file.is_open()){
        file << MASteps << endl;
        file << MBSteps << endl;
        file.close();
    }
}
//--------------------------------------------------------------
void ofApp::calibrate(){
    cout << "CALIBRATING" << endl;
    int maxSteps = ((m.bl/2)/m.bp)*SPN;

    if(turnStepperMotor('A',maxSteps)) MASteps = maxSteps; 
    if(turnStepperMotor('B',maxSteps)) MBSteps = maxSteps; 
}
//--------------------------------------------------------------
void ofApp::updateArduino(){
    ard.update();
	
    if (bSetupArduino) {
        if(count ==0) initialiseLocation(); 

        // DRAWING INSTRUCTIONS
        float nx;
        float ny;

        if(count >= numCoords-1){
            drawing(false);
            writeLastPos(positionFile);
            ofExit();
        }
        nx = coord[count][0];
        ny = coord[count][1];
        drawing((int)coord[count][2]);
        straightLineTo(nx,ny);

        // log
        cout << ofToString(count) << ": "
             << "a:" << ofToString(MASteps,5,'0') 
             <<" b:" << ofToString(MBSteps,5,'0') 
             << " | x:" << ofToString(getCurrentX()) 
             << " y:" << ofToString(getCurrentY()) 
             << " -> " 
             << "x:" << ofToString(nx) 
             << " y:" << ofToString(ny);

        count++;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(visual){ // will only run if program run in visual mode
        int boxW = 304;
        int b = 50; // buffer
        ofFill();
        ofSetColor(20, 20, 20);
        ofRect(b*2 + boxW, 0,350, ofGetWindowHeight());
        
        ofNoFill();
        ofSetColor(200, 200, 200);
        ofRect(b,b,boxW,400);
        ofEllipse(ofMap(getCurrentX(),0,m.ms,b,boxW),
            ofMap(getCurrentY(),0,m.ms,b,boxW),10,10);
        
        
        if (!bSetupArduino){
            ofSetColor(40, 40, 40);
        } else {
            ofSetColor(164, 164, 255);
        }
        //Panel
        font.drawString("Distance",b*3 + boxW , b);
        ofBeginShape();
        for(int i=0;i<=10;i++){
            ofVertex(b*3 +boxW +i*25,b*2 -ofMap(distGraph[i],0,
            maxValueIn(distGraph),0,30));
        }
        
        //direction
        ofEndShape();
        font.drawString("Direction",b*3 + boxW , b*3);
        smallFont.drawString("Absolute",b*3 + boxW , b*3+15);
        smallFont.drawString("Relative",125+ b*3 + boxW , b*3+15);
        ofEllipse(62.5+b*3 +boxW, b*4 +15, 125,125);
        ofEllipse(187.5+b*3 +boxW, b*4 +15, 125,125);
       
        //graph    
        ofSetColor(164, 164, 255);
        smallFont.drawString(ofToString(MASteps,5,'0'), b, b-2);
        smallFont.drawString(ofToString(MBSteps,5,'0'), 9+boxW, b-2);
        smallFont.drawString("("+ofToString(getCurrentX(),1)+","+
            ofToString(getCurrentY(),1)+")", 
            b+5+getCurrentX()*2,
            b+getCurrentY()*2);
        ofSetColor(255, 255, 255);
    }
}
//--------------------------------------------------------------
float ofApp::maxValueIn(float array[]){
    float x = array[0];
    for(int i=0;i< sizeof array;i++){
        if(array[i]>x) x = array[i];
    }
    return x;
}
//--------------------------------------------------------------
string ofApp::removeSpaces(string input){
    input.erase(remove(input.begin(),input.end(),' '),input.end());
    input.erase(remove(input.begin(),input.end(),'\n'),input.end());
    return input;
}
