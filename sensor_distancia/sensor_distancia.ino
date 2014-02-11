#include <Servo.h>

Servo servoMaxi;
#define trigPin 6
#define echoPin 5

int distMaxima=250;

void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoMaxi.attach(2);
}

void loop(){  
  int duracion, distancia;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion/2) / 29.1;
  Serial.println(distancia);
  
  int movimiento = map (distancia, 0, distMaxima, 0, 180);  
  servoMaxi.write(movimiento);
}

