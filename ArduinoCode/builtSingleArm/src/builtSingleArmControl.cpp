#include <Arduino.h>
#include <Servo.h>


Servo close;
Servo mid;
Servo far;

float cords[]= {0, 80, 90}; //x y z

boolean towards = true;

void setup() {

  close.attach(9);
  mid.attach(10);
  far.attach(11);

  Serial.begin(9600);
  
}

void loop() {







//////////////////////////////////////////////////////////////////////////////////////////////// 

  const float maxRadius = 132.95;


  float angle1;
  float angle2;
  float angle3;

  float x = maxRadius - cords[0];
  float y = cords[1];
  float z = cords[2];

  float tarRadiusT = sqrt(x*x + y*y);
  float finRadiusT;

  angle1 = (atan2(y, x) * 180 / PI);

    if (tarRadiusT > maxRadius) {
      


       x = maxRadius * cos(angle1);
       y = maxRadius * sin(angle1); 

       finRadiusT = maxRadius;
    } 
    else {
      finRadiusT = tarRadiusT;
    }

////////////////////////////////////////////////////////////////////////////////////////////////

 
  float R = finRadiusT;

  float finRadiusFB;

  float tarRadiusFB = sqrt(R*R + z*z);
  
  
  float angleA = (atan2(z,R) * 180 / PI);

    
  if (tarRadiusFB > maxRadius) {
    
    R = maxRadius * cos(angleA);
    z = maxRadius * sin(angleA);

    finRadiusFB = maxRadius;

  }
  else {
    finRadiusFB = tarRadiusFB;
  }

/////////////////////////////////////////////////////////////////////////////////////////////////  
  
float a = 47.6;
float b = 85.35;
float c = finRadiusFB;

angle2 = (acos((a*a + c*c - b*b) / (2*c*a)) * 180 / PI);
angle3 = (acos((b*b + a*a - c*c) / (2*a*b)) * 180 / PI);

angle2 -= angleA;
angle2 = 90 - angle2;

angle3 = angle3 - 90;


////////////////////////////////////////////////////////////////////////////////////////////////






close.write(angle1);
mid.write(angle2);
far.write(angle3);





Serial.print("x: ");
Serial.print(cords[0]);
Serial.print(" y: ");
Serial.print(cords[1]);
Serial.print(" z: ");
Serial.print(cords[2]);



Serial.print("      closeAngle: ");
Serial.print(angle1);
Serial.print(" midAngle: ");
Serial.print(angle2);
Serial.print(" farAngle: ");
Serial.println(angle3);


if (cords[0] <= 295){
  cords[0] += 1;
}




}