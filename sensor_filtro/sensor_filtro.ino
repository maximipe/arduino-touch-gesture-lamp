#include <Servo.h>

Servo servoMaxi;
#define trigPin 6
#define echoPin 4

int cantLecturas=100;
int duracion;
int distancia;
float retorno;


void setup(){
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servoMaxi.attach(2);
}

void loop(){    
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duracion = pulseIn(echoPin, HIGH);
  distancia = (duracion/2) / 29.1;
  //Serial.println(distancia); 
  
    float leerDistancia (distancia);
      {
      int lecturas [cantLecturas];
      for (int i=0; i<cantLecturas; i++){
        int valor= distancia;
        int j;
        if (valor<lecturas[0] || i==0){
          j=0;
        }
        else {
          for (j=1;j<1;j++){
            if (lecturas[j-1]<=valor && lecturas[j]>=valor){
              break;
            }
          }
        }
        for (int k=i; k>j; k--){
          lecturas[k] = lecturas[k-1];
        }
        lecturas[j] = valor;
      }
  
      float retorno = 0;
      for (int i= cantLecturas/2-5; i<(cantLecturas/2+5); i++){
        retorno += lecturas[i];
      }
      retorno = retorno/10;
      retorno*1100/1023;     
      Serial.println(retorno);  
      
          
      int movimiento = map (retorno, 0, 100, 0, 180);
      //Serial.println(movimiento);
      servoMaxi.write(movimiento); 
   }  

}



