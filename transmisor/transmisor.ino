#include <Manchester.h>

#define TX_PIN 5  //pin where your transmitter is connected
#define ledPin 2  
#define echoPin 3 // Echo Pin
#define trigPin 4 // Trigger Pin
#define inPin 5

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int pulsador = 0;
int contador;
int distCalibracion;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  man.workAround1MhzTinyCore(); //add this in order for transmitter to work with 1Mhz Attiny85/84
  man.setupTransmit(TX_PIN, MAN_2400);
}

void loop() {
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2); 
 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
 
  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration/58.2;
  
  man.transmit(man.encodeMessage(1, distance/2));
    
  // calibracion con pulsador
  // calibrar con diafragma abierto al maximo
  pulsador = digitalRead(inPin);
  if (pulsador == LOW){
    contador++;
    if (contador == 20){
      digitalWrite(ledPin, HIGH);
      distCalibracion = distance/2;
      //id diferentes para distinguir calibracion de data
      man.transmit(man.encodeMessage(2, distCalibracion));
    }
  } else {
    digitalWrite(ledPin, LOW);
  }  
}
