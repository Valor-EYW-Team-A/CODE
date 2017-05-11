#include <EYW.h> // access library that includes all needed commands 

EYW:: Camera payloadservo; // names servo payloadservo 

void setup()
{
payloadservo.begin(); 
payloadservo.calibrate();
                                  //after callibration it will sound an alarm then a a 10 second *changed to 15 second timer will commence 
payloadservo.alarm();
payloadservo.beginTimer(15000);
}

void loop() 
{
  if (payloadservo.timerExpired()==true||payloadservo.buttonPressed()==true);
  {
                                                          //camera needs to take pictures either before timer expires or botton is pressed, a timer of 5 seconds wiil begin, it will repeat inifinitly 
    payloadservo.getPicture();
    payloadservo.beginTimer(5000);
  }

}
