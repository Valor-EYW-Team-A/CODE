#include <EYW.h>

EYW::Altimeter myaltimeter;

float current_height=0;




void setup ()

{
  Serial.begin(9600);
  myaltimeter.begin();
  myaltimeter.calibrate(100);
  myaltimeter.alarm();
  
}



void loop ()

{
  current_height = myaltimeter.getHeightAvg(20);
  Serial.print("Current Height: ");
  Serial.println(current_height);

  if(current_height>1)
  {
    myaltimeter.alarm(6,2000,500);
  }
  
}

