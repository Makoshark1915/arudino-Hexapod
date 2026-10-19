#include <Arduino.h>
#include <Servo.h>
#include <math.h>


Servo left;
Servo right;
Servo tilt;

double segmentLength = 75;
double Odist = 12.2;

double x = 50;
double y = 10;

bool up = false;


double aLeft;
double aRight;

double leftInternal;
double rightInternal;

double leftExternal;
double rightExternal;

void setup() {

  left.attach(9);
  right.attach(10);
  tilt.attach(11);

  Serial.begin(9600);
  
}

void loop() {


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
   aLeft / | x
        /__|
        y-Odist/2

       |\
      x| \aRight
       |__\
        y+Odist/2

aLeft/Right found using pythagorean theorem (squrt(a^2 + b^2) = c)
*/

aLeft = sqrt(sq(x)+ sq(y+Odist/2));
aRight = sqrt(sq(x)+ sq(y-Odist/2));

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
          /--------------\          
              Odist

      using cosine law to solve for internal angles (left/rightInternal)
*/

leftInternal = (acos((sq(aRight)+sq(Odist)-sq(aLeft))/
(2*aRight*Odist)))*180/PI;

rightInternal = (acos((sq(aLeft)+sq(Odist)-sq(aRight))/
(2*aLeft*Odist)))*180/PI;

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





*/






Serial.println(rightInternal);












}