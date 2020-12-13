#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

#define TRIG_PIN 13 
#define ECHO_PIN 12 
#define MAX_DISTANCE 200 
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(5, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
Servo myservo;  

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {
  Serial.begin(9600);
  myservo.attach(11);  
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);

  if(distance<=25){
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);
  
    if(distanceR>=distanceL){
      turnRight();
      moveStop();
    }else{
      turnLeft();
      moveStop();
    }
  }else{
    moveForward();
  }
   
  distance = readPing();
}

int lookRight()
{
    myservo.write(50); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(105);  //look forward
    return distance;
}

int lookLeft(){
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(105); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  Serial.println(cm);
  if(cm==0){
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
}

void moveForward() {
  
  if(!goesForward){
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
         
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2){
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward=false;
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
   
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2){
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    delay(5);
  }
} 

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);     
  delay(500);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);    
} 
 
void turnLeft() {
  motor1.run(BACKWARD);     
  motor2.run(BACKWARD);   
  delay(500);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
}  