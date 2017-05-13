#include <EYW.h>


EYW::Altimeter myaltimeter; //myaltimeter is name of altimeter
EYW::RangeFinder rangeSensor; //range Sensor is the name of range finder
EYW::Camera payloadServo; //names servo payloadServo

int distance = 0; //global variable distance equals 0
float current_height = 0; //allows decimal variable, current_height
                          //set to 0




void setup() {
  Serial.begin(9600); //MR. Neill what is this?
  myaltimeter.begin(); //start calibrate with the myaltimeter
  myaltimeter.calibrate(150); //this will take 150 readings 
                  //to make sure that the new zero is set correctly
  myaltimeter.alarm (3, 262, 3000); //after calibration, will set
                      //an alarm with 3 tones at 262 hz each for 3 seconds
                      

  rangeSensor.begin(); //next thing to calibrate is the rangeSensor
  rangeSensor.alarm(6, 500, 500); //6 tones at 500 hz each a half second in duration,
            // will determine that we are now calibrating the rangeSensor and not the altimeter
  rangeSensor.calibrate(10); //alarm will sound until it detects object 10 cm away
                    //will detect something 10 cm away, when alarm
                    //stops, check the distance with a ruler


  payloadServo.begin(); //last thing to initiate and calibrate is servo
  payloadServo.calibrate();
  payloadServo.alarm(1, 700, 5000);// after calibration, alarm
                      //will sound for 1 tone at 700 hz for 5 seconds.
  //once 5 second alarm is over, we move on to the launch.

}

void loop() {
  current_height = myaltimeter.getHeightAvg (20); //will take average of 20 readings
                                 // and it will set the current_height to the average
  Serial.print("Current Distance: "); //will constantly display the height
  Serial.println(current_height);

  if (current_height > 3) {
    myaltimeter.alarm(6, 2000, 500); //when system is higher than 3 meters will set off 6 tones
                //at 2000 hz, very high pitched, at 1/2 second each.
    //When system is less than 3 meters it will stop high pitched alarm
  }

  if (current_height >= 50 && current_height <= 60) { //when the altimeter reads
    payloadServo.beginTimer(15000); //anything between 50 and 60 meters, it will start a 15 sec.
    //timer that will be used for later. This will ensure that the servo does not take any pictures
    //going up but when going down.
  }

  if (current_height < 45 && payloadServo.timerExpired()==true && current_height > 30) {
    payloadServo.getPicture(); //after 15 seconds, camera will take pictures between heights of
                      //45 meters and 30 meters
    payloadServo.beginTimer(5000); //timer starts over for 5 seconds
  }

  if (current_height < 2) { //when height is less than 2 meters it will start giving readings of 
           //the height from the ground through the serial monitor.
    distance = rangeSensor.getDistance();
    Serial.print("Current Distance: ");
    Serial.println(distance);
  }

  if (distance < 120) {
    delay (2000); //this set of code will set off an alarm of 2 tones at 2000 hz for 1/2 a second
        //each when the altimeter reads less than 120 cm. it will delay 2 seconds before repeating 
    rangeSensor.alarm(2, 2000, 500);
  }
}
