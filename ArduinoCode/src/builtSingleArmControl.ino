#include <Arduino.h>
#include <Servo.h>


Servo close;
Servo mid;
Servo far;

double cords[]= {132.95, 80, 90}; //x y z

boolean towards = true;

void setup() {

  close.attach(9);
  mid.attach(10);
  far.attach(11);


  


  Serial.begin(9600);
  
}

void loop() {
  



  }
  
  
 



