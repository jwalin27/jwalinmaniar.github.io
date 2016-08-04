#include <sparki.h> 

int count = 0;

unsigned long startTime;
unsigned long endTime = 0;
int threshold = 500;
float theta = 0.0;
float x = 0.0;
float omegaR = 0.0278;
float wrr = 0.0;
float wrl = 0.0;
float d = 0.083;
float xpos = 0.0;
float ypos = 0.0;
float thetapos = 0.0;

unsigned long loopTime = 0;
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
//  sparki.clearLCD();
//  startTime = millis();
//  sparki.moveForward(30.0);
//  endTime = millis();
//
//  sparki.println(endTime - startTime);
//  sparki.updateLCD();
//  delay(15000);
  
  
  startTime = millis();

  int lineLeft   = sparki.lineLeft();   // measure the left IR sensor
  int lineCenter = sparki.lineCenter(); // measure the center IR sensor
  int lineRight  = sparki.lineRight();  // measure the right IR sensor
 
  if ( lineLeft < threshold ) // if line is below left line sensor
  {  
    sparki.motorRotate(MOTOR_RIGHT, DIR_CW, 100); // turn left
    sparki.motorRotate(MOTOR_LEFT, DIR_CW, 100);
    if(sparki.areMotorsRunning())
    {
      wrl = omegaR * 0.1;
      wrr = -omegaR * 0.1;
 //     thetapos += (wrl - wrr)/d;
    }
  }
 
  if ( lineRight < threshold ) // if line is below right line sensor
  {  
    sparki.motorRotate(MOTOR_RIGHT, DIR_CCW, 100); // turn right
    sparki.motorRotate(MOTOR_LEFT, DIR_CCW, 100);
    if(sparki.areMotorsRunning())
    {
      wrl = -omegaR * 0.1;
      wrr = omegaR * 0.1;
//      thetapos += (wrl - wrr)/d;
    }
  }
 
  // if the center line sensor is the only one reading a line
  if ( (lineCenter < threshold) && (lineLeft > threshold) && (lineRight > threshold) )
  {
    sparki.moveForward(); // move forward
    if(sparki.areMotorsRunning())
    {
      //x = omegaR;
//      xpos += x*cos(thetapos);
//      ypos += x*sin(thetapos);
        wrl = omegaR * 0.1;
        wrr = omegaR * 0.1;
    }
      
  }  
// If it hits the start line
  if ( (lineCenter < threshold) && (lineLeft < threshold) && (lineRight < threshold) )
  {
    sparki.moveForward(); // move forward
    if(sparki.areMotorsRunning())
    {
      //x = omegaR;
//      xpos += x*cos(thetapos);
//      ypos += x*sin(thetapos);
        wrl = omegaR * 0.1;
        wrr = omegaR * 0.1;
    }
  }

  thetapos += (wrl - wrr)/d;
  xpos += (wrr/2 + wrl/2) * cos(thetapos);
  ypos += (wrr/2 + wrl/2) * sin(thetapos);

  thetapos = fmod(thetapos, 2*PI);
  
  
  sparki.clearLCD(); // wipe the screen
  
  sparki.print("xpos: "); // show left line sensor on screen
  sparki.println(xpos);
 
  sparki.print("ypos: "); // show center line sensor on screen
  sparki.println(ypos);
 
  sparki.print("Orientation: "); // show right line sensor on screen
  sparki.println(thetapos);
 
  sparki.updateLCD(); // display all of the information written to the screen
  
  endTime = millis();
  loopTime = endTime - startTime;
  delay(100 - loopTime); // wait 0.1 seconds

}
