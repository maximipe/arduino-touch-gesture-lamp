#include <Servo.h> 

const int buttonPin = A0;     // the number of the pushbutton pin
const int ledPin1 =  5;      // the number of the LED pin
const int ledPin2 =  6;
int distCalibracion;
int movServo;
int diamMax = 35;
int diamMin = 12;
int distActual;
int distTotal;
int angMaximo = 180;
int buttonState = 0; // variable for reading the pushbutton status
int contador = 0;
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int margen; 
int areaDer;
int areaIzq;

Servo servo;

#define echoPin 9 // Echo Pin
#define trigPin 8 // Trigger Pin

void setup() {
  servo.attach(4); 
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT);  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);  
}

void loop(){

  buttonState = analogRead(buttonPin);
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2); 
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration/58.2;  
  distActual = distance/2;
  
  margen = distActual - distCalibracion; //total active area
  distTotal = distCalibracion + margen;
  areaDer = (diamMax - diamMin)/2; //active are for right hand
  areaIzq = distCalibracion + diamMax/2 + diamMin/2; //active area for left hand
  
  //Cuando la mano pasa el punto central del haz de luz
  //el programa cambia de orientacion
  
  if (margen <= (diamMax - diamMin)/2){
    //interaccion mano derecha
    digitalWrite(ledPin1, HIGH);
    movServo = map (margen, distCalibracion, distCalibracion + areaDer, 0, angMaximo);
  } else if (margen <= distCalibracion + diamMax && margen >= distCalibracion + diamMax/2 + diamMin/2){
    //interaccion mano izquierda
    digitalWrite(ledPin1, HIGH);
    movServo = map (margen, areaIzq, distCalibracion + diamMax, angMaximo, 0);
  }
  
  servo.write(movServo); 
  
  /*
  Serial.print(distCalibracion);
  Serial.print("  ");
  Serial.print(buttonState);
  Serial.print("  ");
  Serial.println(contador);  
  */
  
  //pushbutton calibration
  if (buttonState > 1000) {
    contador++;
  }else if (buttonState == 0){
    contador = 0;
  }  
 
  if (contador == 60){
    //blink para indicar calibracion
    digitalWrite(ledPin2, HIGH);
    delay(500);
    digitalWrite(ledPin2, LOW);
    
    distCalibracion = distance/2;
  }
}
