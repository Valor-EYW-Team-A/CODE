#include <EYW.h> //access library

EYW::RangeFinder rangeSensor; //rangeSensor is the name of the range sensor
int distance = 0; //This declares the integer named "distance" and the value of "0". This variable is called a "global variable"


void setup() { //This calibrates the sensor, so an alarm will sound when it reaches the designated heigth. 
  // put your setup code here, to run once:
Serial.begin (9600);
rangeSensor.begin();
rangeSensor.alarm();
rangeSensor.calibrate(10);
}

void loop() {
  // put your main code here, to run repeatedly:
// This code will take a measurement and set it equal to the distance. (Measured in cm) If the variable gets under 10cm, the alarm will sound. 
distance = rangeSensor.getDistance();
Serial.print ("Current Distance: ");
Serial.println (distance);

  if (distance <60) { // instead of alarming at 10 cm, changed to 60 cm which is 2 ft.
    rangeSensor.alarm (2, 2000, 100);
  }
}
