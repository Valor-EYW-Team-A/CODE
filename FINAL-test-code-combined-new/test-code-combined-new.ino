#include <EYW.h>


EYW::Altimeter myaltimeter; //myaltimeter is name of altimeter
EYW::RangeFinder rangeSensor; //range Sensor is the name of range finder
EYW::Camera payloadServo; //names servo payloadServo

int c2 = 65;
int d2 = 73;
int e2 = 82;
int f2 = 87;
int g2 = 98;
int a2 = 110;
int b2 = 123;
int c3 = 131;
int d3 = 147;
int e3 = 165;
int f3 = 175;
int g3 = 196;
int a3 = 220;
int b3 = 247;
int c4 = 262;

int c4s = 277;

int d4 = 294;
int e4 = 330;
int f4 = 349;
int g4 = 392;
int a4 = 440;
int b4 = 494;
int c5 = 523;
int d5 = 587;
int e5 = 659;
int f5 = 698;
int g5 = 784;
int a5 = 880;
int b5 = 988;
int c6 = 1047;
int d6 = 1175;
int e6 = 1319;
int f6 = 1397;
int g6 = 1568;
int a6 = 1760;
int b6 = 1976;

// timings: 
int qt = 476; //this is the length of a quarter note transcribed to 355 ms
int eit = 238; //this is the length of a eighth note transcribed to 178 ms


int distance = 0; //global variable distance equals 0
float current_height = 0; //allows decimal variable, current_height
                          //set to 0
unsigned long timerstart = 0;
unsigned long duration = 0;

bool reachedAltitude = false;


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
  payloadServo.alarm(1, 700, 5000);
  payloadServo.motor.write(90);// after calibration, alarm
                      //will sound for 1 tone at 700 hz for 5 seconds.
  //once 5 second alarm is over, we move on to the launch.
 
  pinMode(5, OUTPUT); //pin 12 is an output for the music
  do {
   play_note(5, d5, eit);
   play_note(5, d6, eit);
   play_note(5, a5, eit);
   play_note(5, g5, eit);
   play_note(5, g6, eit);
   play_note(5, a5, eit);
   play_note(5, f6, eit);
   play_note(5, a5, eit);
  } while (payloadServo.buttonPressed() == false);
  delay (1000);
  myaltimeter.alarm(1, 1000, 2000); 
}

void loop() {
  current_height = myaltimeter.getHeightAvg (20); //will take average of 20 readings
                                 // and it will set the current_height to the average
  Serial.print("Current Distance: "); //will constantly display the height
  Serial.println(current_height);

  if (current_height > 1) {
    myaltimeter.alarm(6, 2000, 500); //when system is higher than 3 meters will set off 6 tones
                //at 2000 hz, very high pitched, at 1/2 second each.
    //When system is less than 3 meters it will stop high pitched alarm
  }

  if (current_height >= 2 && current_height <= 3) { //when the altimeter reads
    reachedAltitude = true; //anything between 50 and 60 meters, it will start a 15 sec.
    //timer that will be used for later. This will ensure that the servo does not take any pictures
    //going up but when going down.
    beginTimer(5000);
  }

  if (current_height < 8 && reachedAltitude==true && current_height > 4 && checkTimer() == true) {
    payloadServo.motor.write(150);
    delay(250);
    payloadServo.motor.write(90);
    beginTimer(500);
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


//function for a rest, the variable allows for the option of a quarter or eighth rest
void rest(int len) {
  delay(len);
}

//function for playing notes to make it more simple, plays the desired notes on pin 12 with the specific timing wanted
void play_note(int pin, int note, int len) {
    tone(pin, note);
    delay(len);
    noTone(pin);
    delay(qt/10);
}

//custom functions for the servo
void beginTimer (int dur) {
  timerstart = millis();
  duration = dur;
}

bool checkTimer() {
  if ((millis()-timerstart) > duration) {
    return true;
  } else {
    return false;
  }
}

