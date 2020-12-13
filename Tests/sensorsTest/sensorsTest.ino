#include <Servo.h>
Servo sensor;

float distancefront;
long duration, distance;

//Ultrasonic Module pins
const int trigPin = 13; // 10 microsecond high pulse causes chirp , wait 50 us??
const int echoPin = 12; //distance
const int servoPin = 11; //meachanics

void checkDistance(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;

  Serial.print("Distance: ");
  Serial.println(distance);
}

void lookAround(char directions){
  sensor.attach(servoPin);

  switch(directions){
    case 'l':
      sensor.write (180);
      break;
    case 'r':
      sensor.write (20);
      break;
    case 's':
      sensor.write (105);
      break;
    default:
      Serial.println("Fault with sensor");
      break;
  }

  checkDistance();
}

void setup () {
  Serial.begin(9600);

  pinMode(trigPin , OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite ( trigPin , LOW);
  
  lookAround('s');
}
void loop () {
  
}
