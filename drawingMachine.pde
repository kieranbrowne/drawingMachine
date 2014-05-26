/*Drawing Machine alpha
  by: Kieran Browne
  date: 21st April 2014
  last modified: 23rd April 2014 


  Motor A on the left
  Motor B on the right
  
  this sketch uses identically named functions to visualise
  and plan the drawing machine output. When a satisfactory result
  is achieved copy everything inside the draw() function and 
  paste it into the loop() function in drawingMachine.ino
*/
/*float px, py; // where the system is drawing
final float MOTORSEPARATION =152.0; // motor separation (all values given in notches
final float AX = 0.0; // motor A x coord
final float BX = AX+MOTORSEPARATION; // motor B x coord
float mAr = 100.0 ; // dist between m1 and weight
float mBr = 100.0 ; // dist between m1 and weight
boolean draw = false;

void setup(){
  size(152,180); 
  background(255);
  noFill();
  px = (sq(mAr)-sq(mBr)-sq(AX)+sq(BX))/(2*(BX-AX));
  py =  sqrt(sq(mAr)-sq(px-AX));

  noStroke();
  noLoop();
}

void draw(){
  drawing(false); // dont draw until pointer is positioned
  movePointerTo(50,50);
  drawing(true);
  movePointerTo(60,90);
  drawing(false);
  movePointerTo(100,90);
  drawing(true);
  movePointerTo(50,20);
}

void movePointerTo(float newX, float newY){
  line(px,py,newX,newY);
  px = newX;
  py = newY;
}

void drawing(boolean d){
  if ((draw == false)&&(d == true)){
    stroke(0);
    draw = true;
  }else if((draw == true)&&(d == false)){
    noStroke();
    draw = false;
  }
}*/
