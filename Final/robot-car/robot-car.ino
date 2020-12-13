#include <Servo.h>
Servo sensor;

float distancefront;
long duration, distance, cm;
long randNumber;

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

long checkDistance(){
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;

  Serial.println(distance);

  return distance;
}

int lookRight(){
  sensor.attach(servoPin);
  sensor.write(30); //rotate right
  delay(500);
  int distance = sensor.read();
  delay(100);
  sensor.write(105);  //look forward
  return distance;
}

int lookLeft(){
  sensor.attach(servoPin);
  sensor.write(180); //rotate left
  delay(500);
  int distance = sensor.read();
  delay(100);
  sensor.write(105);  //look forward
  return distance;
}

long lookAround(){
  sensor.attach(servoPin);
  sensor.write(105); 
  
  do{
    sensor.write(sensor.read()-2);
    distance = checkDistance();
  } while (sensor.read()>60);

  do{
    sensor.write(sensor.read()+2);
    distance = checkDistance();
  } while (sensor.read()<150);
  
  return distance;
}

void setup () {
  Serial.begin(9600);
  defineOutputOrInput();
  checkDistance();

//  turnLeft();
//  turnRight();
}

void loop () {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);
  
  goStraight();
  checkDistance();

  if(distance<=25){
    stopMoving();
    delay(100);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if(distanceR>=distanceL){
      turnRight();
      delay(1000);
      stopMoving();
    }else{
      turnLeft();
      delay(1000);
      stopMoving();
    }
    
  }else{
    goStraight(); 
  }

  distance = sensor.read();
}
