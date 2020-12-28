#include <Servo.h>
Servo sensor;

long duration, distanceAhead;
long newDistanceRight, newDistanceLeft, newDistanceAhead;

//Ultrasonic Module pins
const int trigPin = 13; // 10 microsecond high pulse causes chirp , wait 50 us??
const int echoPin = 12; //distance
const int servoPin = 11; //meachanics

// Motor control pins : L298N H bridge
const int enAPin = 6; // Left motor PWM speed control
const int in1Pin = 7; // Left motor Direction 1 --> forwards
const int in2Pin = 5; // Left motor Direction 2 --> backwards
const int in3Pin = 4; // Right motor Direction 1 --> forwards
const int in4Pin = 2; // Right motor Direction 2 --> backwards
const int enBPin = 3; // Right motor PWM speed control

void defineOutputOrInput(){
  
  //motors
  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
  pinMode(enBPin, OUTPUT);

  //sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //it will always be low so that's why in this function
  digitalWrite ( trigPin , LOW);
}

void goStraight(){
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enAPin, 170); 
  analogWrite(enBPin, 160);
}

void goBack(){
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  analogWrite(enAPin, 170); 
  analogWrite(enBPin, 160);
}

void stopMoving(){
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
  analogWrite(enAPin, 0); 
  analogWrite(enBPin, 0);
}

void turnLeft(){
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, HIGH);
  digitalWrite(in4Pin, LOW);
  analogWrite(enAPin, 190); 
  analogWrite(enBPin, 160);
}

void turnRight(){
  digitalWrite(in1Pin, HIGH);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  analogWrite(enAPin, 190); 
  analogWrite(enBPin, 160);
}

long checkDistanceAhead(){
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distanceAhead = duration / 58;

//  Serial.print("distanceAhead: ");
//  Serial.println(distanceAhead);

  return distanceAhead;
}

int lookRight(){
  sensor.attach(servoPin);
  sensor.write(30); //rotate right
  delay(500);
  int distanceRight = checkDistanceAhead();
  delay(100);
  sensor.write(105);  //look forward

//  Serial.print("distanceRight: ");
//  Serial.println(distanceRight);
  
  return distanceRight;
}

int lookLeft(){
  sensor.attach(servoPin);
  sensor.write(180); //rotate left
  delay(500);
  int distanceLeft = checkDistanceAhead();
  delay(100);
  sensor.write(105);  //look forward
  
  return distanceLeft;
}

void setup () {
  Serial.begin(9600);
  defineOutputOrInput();
}

void loop () {
  
  goStraight();

  newDistanceAhead = checkDistanceAhead(); //output is var distanceAhead, gets written in newDistanceAhead

  if(newDistanceAhead<=25){
    stopMoving();
    delay(100);
    newDistanceRight = lookRight(); //distanceRight gets written in newDistanceRight
    delay(200); 
    newDistanceLeft = lookLeft(); //distanceLeft gets written in newDistanceLeft
    delay(200);
    
    if(newDistanceRight>=newDistanceLeft){
      turnRight();  
      delay(500);
      stopMoving();
    }else{
      turnLeft();
      delay(500);
      stopMoving();
    }
    
  }else{
    goStraight(); 
  }

  distanceAhead = sensor.read();
}
