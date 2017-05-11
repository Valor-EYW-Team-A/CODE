#include <EYW.h>//access library 

EYW::Altimeter myaltimeter;//gives name

float current_height=0;//assaigns the value of 0. sets the global variable 




void setup ()

{
  Serial.begin(9600);//corresponds to steps 2-3, after caibrations- it sounds the alarm.
  myaltimeter.begin();
  myaltimeter.calibrate(50);//before this was 100, and we changed it to 50 to make it faster. the 50 means that it will only take 50 readings to make sure "zero"  is set correctly.
  myaltimeter.alarm();
  
}



void loop ()

{
  current_height = myaltimeter.getHeightAvg(20);
  Serial.print("Current Height: ");
  Serial.println(current_height);//loop portion of code. averages first 20 measurements and sets the variabe. 

  if(current_height>1) //if its larger than 1 it sounds alarm 
  {
    myaltimeter.alarm(6,2000,500);
  }
  
}

