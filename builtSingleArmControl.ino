#include <Servo.h>

Servo close;
Servo mid;
Servo far;

double cords[3]= {0, 0, 0}; //x y z


void setup() {

  close.attach(22);
  mid.attach(23);
  far.attach(24);

  Serial.begin(9600);
  
}

void loop() {
  

  
}

void mergedChek(double input[3]){ 

  double x = input[1];
  double y = input[2];
  double z = input[3];

  
  double maxRadius = 132.95;
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
  
  double a = 47.6;
  double b = 85.35;
  
  
  angle2 = (180/3.14159) * (acos((sq(a) + sq(finRadius) - sq(b)) / (2*finRadius*a)));
  angle3 = (180/3.14159) * (acos((sq(b) + sq(a) - sq(finRadius)) / (2*a*b)));

  angle2 -= angle1;
  angle2 = 90 - angle2;







  
}


