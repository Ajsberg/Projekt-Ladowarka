#include <Arduino.h>
#define pinPRZEK 2
#define diodCzer 4
#define diodZol 5
#define diodZiel 6

int readV = 0;
int time = 0;
float batvol = 0;
int mrug = 0;
bool isCharged = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinPRZEK, OUTPUT);
  pinMode(A5, INPUT);
  pinMode(diodZiel, OUTPUT);
  pinMode(diodCzer, OUTPUT);
  pinMode(diodZol, OUTPUT);
  digitalWrite(pinPRZEK, HIGH);
}

void mierz(){
  digitalWrite(diodZiel, LOW);
  digitalWrite(diodZol, HIGH);
  
  while (time<3) {
      
      readV = analogRead(A5);
      batvol = readV * (5.0/1024.0);
      Serial.println(batvol);
      delay(1000);
      time++;
    }
  digitalWrite(diodZol, LOW);
  time = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if(isCharged){
    return;
  }
  mierz();
  mrug = 0;
  if(batvol < 3.0){
  while(mrug < 6){
    digitalWrite(diodZiel, LOW);
    digitalWrite(diodCzer, HIGH);
    delay(500);
    digitalWrite(diodCzer, LOW);
    digitalWrite(diodZol, HIGH);
    delay(500);
    digitalWrite(diodZol,LOW);
    digitalWrite(diodZiel, HIGH);
    delay(500);
    mrug++;
  }
  }else if(batvol > 3.0 && batvol < 3.68){
    digitalWrite(diodCzer, HIGH);
    time = 0;
    digitalWrite(pinPRZEK, LOW);
    delay(90000);
    digitalWrite(pinPRZEK, HIGH);
  }else if(batvol >= 3.68 && batvol <3.7){
    digitalWrite(diodCzer, HIGH);
    time = 0;
    digitalWrite(pinPRZEK, LOW);
    delay(30000);
    digitalWrite(pinPRZEK, HIGH);
  }else if(batvol >= 3.7){
    Serial.println("Osiagnieto wymagane napiecie. Bateria naladowana.");
    digitalWrite(diodCzer, LOW);
    digitalWrite(diodZol,LOW);
    digitalWrite(diodZiel, HIGH);
    delay(3000);
    isCharged = true;
    return;
  }
  
}