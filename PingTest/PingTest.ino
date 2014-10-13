#include <NewPing.h>

const int TRIGGER = 13;
const int ECHO = 12;
const unsigned int BAUD_RATE = 9600;
const unsigned int CANDY_DISPENSE_DURATION = (1000 * 3);

const unsigned int MIN_DISTANCE_THRESHOLD = 10;
const unsigned int MAX_DISTANCE_THRESHOLD = 50;

NewPing sonar(TRIGGER, ECHO, 300);

void setup() {
  // put your setup code here, to run once:
//  pinMode(TRIGGER, OUTPUT);
//  pinMode(ECHO, INPUT);
  Serial.begin(BAUD_RATE);
 // NewPing sonar(TRIGGER_PIN, ECHO_PIN, 200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(2000);
////  d("Starting loop");
 execute();
 delay(200);
  //int x = getDistance();
 // Serial.println(x);
//  d("End of loop");
  
}

/*
  Main method that does it all.  Called via interrupt
 */
void execute() {
  //turn motors on to go forward
  goForward();
  
  int distance = (sonar.ping() / US_ROUNDTRIP_CM);
  
  while (!isCloseToTarget(distance)) {
    d("Not close enough");
    distance = (sonar.ping() / US_ROUNDTRIP_CM);
  } 
  
  //do nothing until we are close enough
  //turn motors off
  stopMovement();
  
  //wait for 1.5min
  delay(CANDY_DISPENSE_DURATION);
  
  //turn motors on to go backward
  goBackward();
  distance = (sonar.ping() / US_ROUNDTRIP_CM);
  while(!isFarFromTarget(distance)) {
     d("Not far enough");
     distance = getDistance();
  } 
  
  //do nothing until we are far away enough
  
  stopMovement();
  return;
}

boolean isCloseToTarget(int cm) {
  return cm <= MIN_DISTANCE_THRESHOLD;
}

boolean isFarFromTarget(int cm) {
  return cm >= MAX_DISTANCE_THRESHOLD;
}

int getDistance() {
  /*
  int dist1 = (sonar.ping());// / US_ROUNDTRIP_CM); 
  int dist2 = (sonar.ping());// / US_ROUNDTRIP_CM);
  int dist3 = (sonar.ping());// / US_ROUNDTRIP_CM); 
  
  int r = 0;
 
  if (abs(dist1 - dist2) < 2) {
    r = (dist1 + dist2) / 2;
  } 
  else {
    if (abs(dist1 - dist3) < 2) {
      r = (dist1 + dist3) / 2;
    }
    else {
      r = (dist2 + dist3) / 2;
    } 
  }
  */
  int r = sonar.ping_median(20);
  
  return r / US_ROUNDTRIP_CM;
}

void goForward() {
  d("Moving Forward");
}

void goBackward() {
  d("Moving Backward");
}

void stopMovement() {
  d("Stopping Movement");
}

//debug 
void d(String msg) {
  Serial.println(msg); 
}
