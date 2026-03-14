#include <Arduino.h>
#include <Servo.h>


Servo close;
Servo mid;
Servo far;

double cords[]= {0, 80, 50}; //x y z

boolean towards = true;

void setup() {

  close.attach(9);
  mid.attach(10);
  far.attach(11);


  


  Serial.begin(9600);
  
}

void loop() {
  int sernsorVal = analogRead(A1);

  if(sernsorVal > 0){
    close.write(0);
    mid.write(0);
    far.write(0);
  }
  else{


  if(cords[1] >= 265){
  towards = false;
  }
  else if(cords[1] <= 0){
    towards = true;
  }

  if(towards){
    cords[1] += 1;
  }
  else{
    cords[1] -= 1;
  }






  double x = cords[1];
  double y = cords[2];
  double z = cords[3];

  
  double maxRadius = 132.95; //overall length from point of rotation to point of rotation to end point
  double tarRadius;
  double finRadius;

  double angle1;
  double angle2;
  double angle3;


  
  boolean inRange = true;
  
  
  tarRadius = sqrt(sq(x) + sq(y));
  

  angle1 = (180/3.14159) * atan(y/x);


  if(tarRadius > maxRadius) {
    
       x = maxRadius * cos(angle1);
       y = maxRadius * sin(angle1); 

      tarRadius = maxRadius;
      
  }
  ////////////////////////////////////////////////////////////////////////////////////////
  
  finRadius = sqrt(sq(tarRadius) + sq(z));
    
  angle2 = (180/3.14159) * atan(z/tarRadius);


  if (finRadius > maxRadius) {
    
       tarRadius = maxRadius * cos(angle1);
       z = maxRadius * sin(angle1); 

       finRadius = maxRadius;

      
  } 

  ///////////////////////////////////////////////////////////////////////////////////////
  
  double a = 47.6; // first arm segment length (ignoring the rotating intitial segment)
  double b = 85.35;// second arm segment length
  
  
  angle2 = (180/3.14159) * (acos((sq(a) + sq(finRadius) - sq(b)) / (2*finRadius*a)));
  angle3 = (180/3.14159) * (acos((sq(b) + sq(a) - sq(finRadius)) / (2*a*b)));

  angle2 -= angle1;
  angle2 = 90 - angle2;

  close.write(angle1);
  mid.write(angle2);  
  far.write(angle3);





  Serial.print("x:"); Serial.print(cords[1]);
  Serial.print(" y:"); Serial.print(cords[2]);
  Serial.print(" z:"); Serial.print(cords[3]);

  Serial.print("  ");

  Serial.print("closePos:"); Serial.print(angle1);
  Serial.print(" midPos:"); Serial.print(angle2);
  Serial.print(" farPos:"); Serial.println(angle3);



  }
  }
  
 


String mergedChek(double input[3]){ 

  double x = input[1];
  double y = input[2];
  double z = input[3];

  
  double maxRadius = 132.95; //overall length from point of rotation to point of rotation to end point
  double tarRadius;
  double finRadius;

  double angle1;
  double angle2;
  double angle3;


  
  boolean inRange = true;
  
  
  tarRadius = sqrt(sq(x) + sq(y));
  

  angle1 = (180/3.14159) * atan(y/x);


  if(tarRadius > maxRadius) {
    
       x = maxRadius * cos(angle1);
       y = maxRadius * sin(angle1); 

      tarRadius = maxRadius;
      
  }
  ////////////////////////////////////////////////////////////////////////////////////////
  
  finRadius = sqrt(sq(tarRadius) + sq(z));
    
  angle2 = (180/3.14159) * atan(z/tarRadius);


  if (finRadius > maxRadius) {
    
       tarRadius = maxRadius * cos(angle1);
       z = maxRadius * sin(angle1); 

       finRadius = maxRadius;

      
  } 

  ///////////////////////////////////////////////////////////////////////////////////////
  
  double a = 47.6; // first arm segment length (ignoring the rotating intitial segment)
  double b = 85.35;// second arm segment length
  
  
  angle2 = (180/3.14159) * (acos((sq(a) + sq(finRadius) - sq(b)) / (2*finRadius*a)));
  angle3 = (180/3.14159) * (acos((sq(b) + sq(a) - sq(finRadius)) / (2*a*b)));

  angle2 -= angle1;
  angle2 = 90 - angle2;

  close.write(angle1);
  mid.write(angle2);  
  far.write(angle3);



 

  
}