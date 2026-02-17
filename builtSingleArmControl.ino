#include <Servo.h>

Servo close;
Servo mid;
Servo far;

double cords[3]= {0, 50, 50}; //x y z


void setup() {

  close.attach(22);
  mid.attach(23);
  far.attach(24);

  Serial.begin(9600);
  
}

void loop() {

  for(int i = 0; i < 265; i++){
    
  cords[1] = i;

    
  mergedChek(cords);

  Serial.print("cords:"); Serial.print(cords[1]); Serial.print(cords[2]); Serial.print(cords[3]);
  Serial.println();
  Serial.println("close Servo pos");  Serial.print(close.read());
  Serial.println("mid Servo pos");  Serial.print(mid.read());
  Serial.println("far Servo pos");  Serial.print(far.read());
  } // test moving x to just max(ish) then back to 0
  
  for(int i = 265; i >= 0; i--){
    
  cords[1] = i;

    
  mergedChek(cords);

  Serial.print("cords:"); Serial.print(cords[1]); Serial.print(cords[2]); Serial.print(cords[3]);
  Serial.println();
  Serial.println("close Servo pos");  Serial.print(close.read());
  Serial.println("mid Servo pos");  Serial.print(mid.read());
  Serial.println("far Servo pos");  Serial.print(far.read());
  }

  
  
}

void mergedChek(double input[3]){ 

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







  
}


