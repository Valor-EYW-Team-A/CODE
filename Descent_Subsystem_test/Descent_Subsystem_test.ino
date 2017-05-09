#include <EYW.h>
EYW::RangeFinder rangeSensor;
int distance = 0;
void setup() {
  // put your setup code here, to run once:
Serial.begin (9600);
rangeSensor.begin();
rangeSensor.alarm();
rangeSensor.calibrate(10);
}

void loop() {
  // put your main code here, to run repeatedly:
distance = rangeSensor.getDistance();
Serial.print ("Current Distance: ");
Serial.println (distance);

  if (distance <60) {
    rangeSensor.alarm (2, 2000, 100);
  }
}
