#include <Arduino.h>
#include <Servo.h>
#include <math.h>

Servo left;
Servo right;


const double segmentLength = 75;
const double Odist = 12.2;

double x = 100;
double y = 100;

bool up = false;


double aLeft;
double aRight;

double leftInternal;
double rightInternal;

double leftExternal;
double rightExternal;

double leftFinal;
double rightFinal;

/*
x range = 224.4, -112.2 to 112.2
y range = 144, 0 to 144

input range = 0 to 1023
*/

const byte xIn = A0;
const byte yIn = A1;




void setup() {

  pinMode(xIn, INPUT);
  pinMode(yIn, INPUT);
  
  left.attach(10);
  right.attach(9);

  Serial.begin(9600);
  
}

void loop() {

x = analogRead(xIn)*(244.4 / 1023) - (244.4/2);
y = analogRead(yIn)*(144.0/1023);

Serial.print("cord:(");
Serial.print(x);

Serial.print(",");
Serial.print(y);

Serial.print(") leftfin: ");
Serial.print(leftExternal);

Serial.print("       rightfin: ");
Serial.println(rightExternal);


servoSet();

}

bool servoSet(){
/*find aLeft/Right

end point at coords (measured from center of Odist)
            v
            /\
     aLeft /  \ aRight
          /____\  
          Odist


done with 2 right triangles

          /|
   aLeft / | y
        /__|
        x-Odist/2

       |\
      y| \aRight
       |__\
        x+Odist/2

aLeft/Right found using pythagorean theorem (squrt(a^2 + b^2) = c)
*/

aLeft = sqrt(sq(y)+ sq(x+Odist/2.0));
aRight = sqrt(sq(y)+ sq(x-Odist/2.0));

/*find the left and right internal angle's

         end point of cords
                  v             
                 /\
                /  \             
               /    \
         aLeft/      \aRight
             /        \
            /          \
           /θleft θright\
          /______________\          
              Odist

      using cosine law to solve for internal angles (left/rightInternal)
*/

leftInternal = (acos((sq(aRight)+sq(Odist)-sq(aLeft))/
(2*aRight*Odist)))*180.0/PI;

rightInternal = (acos((sq(aLeft)+sq(Odist)-sq(aRight))/
(2*aLeft*Odist)))*180.0/PI;

/*find the external left and right angles

                /|             |\
               / |             | \
              /  |             |  \
segmentLength/   |             |   \segmentLength
            /    |aLeft  aRight|    \
           /     |             |     \
          /      |             |      \
          \      |             |      /
           \θleft|             |θrigt/
            \    |             |    /
segmentLength\   |             |   /segmentLength
              \  |             |  /
               \ |             | /
                \|             |/

external angles found with cosine law
*/


leftExternal = (acos((sq(aRight)+sq(segmentLength)-sq(segmentLength))/
(2*aRight*segmentLength)))*180.0/PI;

rightExternal = (acos((sq(aLeft)+sq(segmentLength)-sq(segmentLength))/
(2*aLeft*segmentLength)))*180.0/PI;


/*
by adding the internal and external angles we can find the total angle from
the front of the leg (facing out from the servos/towrds the arms)

and then arrange them for use to send to the 
servos (angle range measured from the same spot is 45 - 225)

by taking the total angle and minusing 45 we can determine the desired servo angle away from center

then by minusing 180 from one of the values (do the right servo)
we can determin the angle that both servos will be given



angleright = internal + external - 45 - 180
*/

leftFinal = leftExternal + leftInternal -45.0;
rightFinal = abs(rightExternal + rightInternal - 45.0 - 180.0);


if(isnan(leftFinal) || isnan(rightFinal)){

  //Serial.println("cords are out of arm range")
  return false;

}
else{


left.write(leftFinal);
right.write(rightFinal);

return true;

}
}