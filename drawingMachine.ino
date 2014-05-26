/*Drawing Machine alpha
  by: Kieran Browne
  date: 21st April 2014
  last modified: 23rd April 2014 


  Motor A on the left
  Motor B on the right
*/
#include <Servo.h>
Servo servo;  

float px, py; // where the system is drawing
const float MOTORSEPARATION =152.0; // motor separation (all values given in notches
const float AX = 0.0; // motor A x coord
const float BX = AX+MOTORSEPARATION; // motor B x coord
float mAr = 100.0 ; // dist between m1 and weight
float mBr = 100.0 ; // dist between m1 and weight
// motors at full speed turn 81rpm, gears have 16 notches
const float NPM = 0.0216; // notches per millisecond
boolean draw = false;
// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define CW  0
#define CCW 1

// Motor definitions to make life easier:
#define MOTOR_A 0
#define MOTOR_B 1

// Pin Assignments //
// Don't change these! These pins are statically defined by shield layout
const byte PWMA = 10;  // PWM control (speed) for motor A
const byte PWMB = 11; // PWM control (speed) for motor B
const byte DIRA = 12; // Direction control for motor A
const byte DIRB = 13; // Direction control for motor B

void setup()
{
  setupArdumoto(); // set pins for dc motors
  // find initial pointer location
  px = (sq(mAr)-sq(mBr)-sq(AX)+sq(BX))/(2*(BX-AX));
  py =  sqrt(sq(mAr)-sq(px-AX));
  servo.attach(2); // set pin for servo standoff
  drawing(false); // dont draw until pointer is positioned
  delay(30000);
}

void loop()
{
  drawing(false); // dont draw until pointer is positioned
  movePointerTo(MOTORSEPARATION/2,40);
  drawing(true);
  movePointerTo(random(50,100),random(60,90));
}

void movePointerTo(float newX, float newY){
  
  float newAradius = sqrt(sq(newY)+sq(newX-AX));
  float newBradius = sqrt(sq(newY)+sq(newX-BX));
  
  float changeA = newAradius - mAr;
  float changeB = newBradius - mBr;
  
  
  if (changeA > 0) {
    driveArdumoto(MOTOR_A, CW, 255);
  }else if (changeA < 0){
    driveArdumoto(MOTOR_A, CCW, 255);
  }
  if (changeB > 0) {
    driveArdumoto(MOTOR_B, CCW, 255);
  }else if (changeB < 0){
    driveArdumoto(MOTOR_B, CW, 255);
  }
  float timeA = abs(changeA)/NPM;
  float timeB = abs(changeB)/NPM;
  if (timeA >= timeB){
    delay(timeB);
    stopArdumoto(MOTOR_B);
    delay(timeA-timeB);
    stopArdumoto(MOTOR_A);
  }else{
    delay(timeA);
    stopArdumoto(MOTOR_A);
    delay(timeB-timeA);
    stopArdumoto(MOTOR_B);
  }
  delay(500);
  
  mAr = newAradius; //update r values
  mBr = newBradius;
}

void drawing(boolean d){
  if ((draw == false)&&(d == true)){
    for(int pos = 90; pos>=10; pos-=1){                                
      servo.write(pos); delay(15); 
    }
    draw = true;
  }else if((draw == true)&&(d == false)){
    for(int pos = 10; pos < 90; pos += 1){
      servo.write(pos); delay(15);
    } 
    draw = false;
  }
}


/*
///////////////////////////// 

ARDUMOTO LIB
by Jim Lindblom

/////////////////////////////
*/

// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}

// setupArdumoto initialize all pins
void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}
