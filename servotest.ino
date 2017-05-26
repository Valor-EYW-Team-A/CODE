#include <EYW.h>
#include <Servo.h>
#include <Wire.h>

EYW::Camera myservo;

unsigned long timerstart=0;
unsigned long duration=0;

void setup() {
  // put your setup code here, to run once:
  myservo.begin();
  myservo.calibrate();
  beginTimer(10000);
  myservo.alarm(3, 400, 300);
  myservo.motor.write(90);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  if(checkTimer()==true){
    myservo.alarm(2, 1200, 200);
    myservo.motor.write(150);
    delay(500);
    myservo.motor.write(100);
    beginTimer(3000);
  }
}

void beginTimer(int dur)
{
  timerstart = millis();
  duration = dur;
}

bool checkTimer()
{
  if ((millis()-timerstart) > duration){
    return true;
  } else {
    return false;
  }
}

