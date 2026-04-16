#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>














const float defaultX = 132.95f; // default x value for the legs
const float defaultY = 80.0f; // default y value for the legs
const float defaultZ = 90.0f; // default z value for the 


float legsGroup1[3][3] // moving position for all 6 legs, will be updated every loop  in the format of legs{legnumber}{x,y,z}
= {
  {defaultX, defaultY, defaultZ},
  {defaultX, defaultY, defaultZ},
  {defaultX, defaultY, defaultZ}
};
float legsGroup2[3][3] // moving position for all 6 legs, will be updated every loop  in the format of legs{legnumber}{x,y,z}
= {
  {defaultX, defaultY, defaultZ},
  {defaultX, defaultY, defaultZ},
  {defaultX, defaultY, defaultZ}
};

const float mult = 5; // multiplier for how much the joystick input affects movement

static float joystickX; // variable to store the x value of the joystick input, will be updated every loop
static float joystickY; // variable to store the y value of the joystick input, will be updated every loop


/* leg setup

      front
    1-1   2-1   

  2-2       1-2

    1-3   2-3
       back

*/

void setup() {
  Serial.begin(9600);


}

void loop() {

  joystickInput(); // get the joystick input and store it in the joystickX and joystickY variables

  if(joystickAtRest()){ // if the joystick is at rest go to default or else, start moving

    reCenter(); // if the joystick is in the neutral position, run the code to re-center the legs to the default position

  }

  else{
    moving(joystickX, joystickY);// the code to move the legs according to the joystick input and the current scenario of which leg group is up (only runs if the joystick is not in the neutral position )
  }
  

}





static void moving(float joystickX, float joystickY) { // run the first step of walking cycle

    if(groupUp() == 0 || groupUp() == 1){

      legsGroup1[0][2] = defaultZ-10;
      legsGroup1[1][2] = defaultZ-10;
      legsGroup1[2][2] = defaultZ-10;
      applyChanges();


    do{ // while the legs are in range and the first leg group is up, move the legs according to the joystick input

      legsGroup1[0][0] += joystickX * mult;
      legsGroup1[0][1] += joystickY * mult; // joystickY for all of these might need to be flipped/have changed signs
 
      legsGroup1[1][0] += joystickX * mult;
      legsGroup1[1][1] += joystickY * mult; 

      legsGroup1[2][0] += joystickX * mult;
      legsGroup1[2][1] += joystickY * mult;


      legsGroup2[0][0] -= joystickX * mult;
      legsGroup2[0][1] -= joystickY * mult;

      legsGroup2[1][0] -= joystickX * mult;
      legsGroup2[1][1] -= joystickY * mult;

      legsGroup2[2][0] -= joystickX * mult;
      legsGroup2[2][1] -= joystickY * mult;

      joystickInput();
      applyChanges();
      
    }while(inRange() && joystickAtRest() == false);

      legsGroup2[0][2] = defaultZ-10;
      legsGroup2[1][2] = defaultZ-10;
      legsGroup2[2][2] = defaultZ-10;

      legsGroup1[0][2] = defaultZ;
      legsGroup1[1][2] = defaultZ;
      legsGroup1[2][2] = defaultZ;


      applyChanges();




  }
  else if(groupUp() == 2){

    do{ // while the legs are in range and the first leg group down, move the legs according to the joystick input

      legsGroup1[0][0] -= joystickX * mult;
      legsGroup1[0][1] -= joystickY * mult; // joystickY for all of these might need to be flipped/have changed signs
 
      legsGroup1[1][0] -= joystickX * mult;
      legsGroup1[1][1] -= joystickY * mult;

      legsGroup1[2][0] -= joystickX * mult; 
      legsGroup1[2][1] -= joystickY * mult;


      legsGroup2[0][0] += joystickX * mult;
      legsGroup2[0][1] += joystickY * mult;

      legsGroup2[1][0] += joystickX * mult;
      legsGroup2[1][1] += joystickY * mult;

      legsGroup2[2][0] += joystickX * mult;
      legsGroup2[2][1] += joystickY * mult;

      joystickInput();

    }while(inRange() && joystickAtRest() == false);

      legsGroup1[0][2] = defaultZ-10;
      legsGroup1[1][2] = defaultZ-10;
      legsGroup1[2][2] = defaultZ-10;

      legsGroup2[0][2] = defaultZ;
      legsGroup2[1][2] = defaultZ;
      legsGroup2[2][2] = defaultZ;



  }
  else{
    while (true){
    Serial.println("ERROR bad read on Scenario");
    }
  }








  }

static void reCenter() { // run re-center the legs to the default position
  legsGroup1[0][0] = defaultX;
  legsGroup1[0][1] = defaultY;
  legsGroup1[0][2] = defaultZ;

  legsGroup1[1][0] = defaultX;
  legsGroup1[1][1] = defaultY;
  legsGroup1[1][2] = defaultZ;

  legsGroup1[2][0] = defaultX;
  legsGroup1[2][1] = defaultY;
  legsGroup1[2][2] = defaultZ;


  legsGroup2[0][0] = defaultX;
  legsGroup2[0][1] = defaultY;
  legsGroup2[0][2] = defaultZ;

  legsGroup2[1][0] = defaultX;
  legsGroup2[1][1] = defaultY;
  legsGroup2[1][2] = defaultZ;

  legsGroup2[2][0] = defaultX;
  legsGroup2[2][1] = defaultY;
  legsGroup2[2][2] = defaultZ;

}

static void applyChanges() { // apply the changes to the legs

    
  float cords[3];
  boolean towards = true;



  for(int i = 0; i < 6; i++){
   
    if(i<=2){

      cords[0] = legsGroup1[i][0]-defaultX;
      cords[1] = legsGroup1[i][1];
      cords[2] = legsGroup1[i][2];

    }
    else{

      cords[0] = legsGroup2[i-3][0]-defaultX;
      cords[1] = legsGroup2[i-3][1];
      cords[2] = legsGroup2[i-3][2];

    }
    

    float angle1;
    float angle2;
    float angle3;

    float x = defaultX - cords[0];
    float y = cords[1];
    float z = cords[2];

    float tarRadiusT = sqrt(x*x + y*y);
    float finRadiusT;

    angle1 = (atan2(y, x) * 180 / PI);

      if (tarRadiusT > defaultX) {
        


        x = defaultX * cos(angle1);
        y = defaultX * sin(angle1); 

        finRadiusT = defaultX;
      } 
      else {
        finRadiusT = tarRadiusT;
      }

  ////////////////////////////////////////////////////////////////////////////////////////////////

  
    float R = finRadiusT;

    float finRadiusFB;

    float tarRadiusFB = sqrt(R*R + z*z);
    
    
    float angleA = (atan2(z,R) * 180 / PI);

      
    if (tarRadiusFB > defaultX) {
      
      R = defaultX * cos(angleA);
      z = defaultX * sin(angleA);

      finRadiusFB = defaultX;

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





    if(i==0){
      /*
      1-1close.write(angle1)
      1-1mid.write(angle2)
      1-1far.write(angle3)
      */
    }
    else if(i==1){
      /*
      1-2close.write(angle1)
      1-2mid.write(angle2)
      1-2far.write(angle3)
      */      
    }
    else if(i==2){
      /*
      1-3close.write(angle1)
      1-3mid.write(angle2)
      1-3far.write(angle3)
      */    
     }
    else if(i==3){
      /*
      2-1close.write(angle1)
      2-1mid.write(angle2)
      2-1far.write(angle3)
      */    
     }
    else if(i==4){
      /*
      2-2close.write(angle1)
      2-2mid.write(angle2)
      2-2far.write(angle3)
      */    
     }
    else if(i==5){
      /*
      2-3close.write(angle1)
      2-3mid.write(angle2)
      2-3far.write(angle3)
      */   
     }

}
}

static boolean inRange() { // check's if the given xyz values for all legs are in a reachable position
boolean inRangeOut = true;

double cords[3];


double R1;
double R2;

  for(int i = 0; i < 6; i++){
   
    if(i<=2){

      cords[0] = legsGroup1[i][0]-defaultX;
      cords[1] = legsGroup1[i][1];
      cords[2] = legsGroup1[i][2];

    }
    else{

      cords[0] = legsGroup2[i-3][0]-defaultX;
      cords[1] = legsGroup2[i-3][1];
      cords[2] = legsGroup2[i-3][2];




    }


    R1 = sqrt((cords[0]*cords[0]) + (cords[1]*cords[1]));
    R2 = sqrt((R1*R1) + (cords[2]*cords[2]));



    if(R1 > defaultX || R2 > defaultX){
      inRangeOut = false;
      break;
    }
    

  }



 
  return inRangeOut;
 
}

static boolean joystickAtRest() { // check if the joystick is in the neutral position


  boolean atRest = false;

  if(joystickX == 0 && joystickY == 0){
    atRest = true;
  }

  return atRest;
}

static int groupUp(){// checks which leg group is raised

  
  
  int scenario;
  
  if(legsGroup1[0][2]==defaultZ && legsGroup2[0][2]==defaultZ){//at default both groups are down, scenario 0

      scenario = 0;
      
  }
    else if(legsGroup1[0][2] == defaultZ-10 && legsGroup2[0][2] == defaultZ){ //group 1 is up and group2 is down, scenario 1

      scenario = 1;

    } 
    else if(legsGroup2[0][2] == defaultZ-10 && legsGroup1[0][2] == defaultZ){ //group 1 is down and group2 is up, scenario 2

      scenario = 2;

    }
    else
    {    
       while (true){

        Serial.println("ERROR bad Scenario");

        } // if in none of the previous options something broke run ERROR
    }



    return scenario;
}

static void joystickInput() { // get the joystick input also serves as a pause for the user to see the current leg positions before inputting new joystick values
  float joystickXin;
  float joystickYin;

  //code to get the joystick input and store it in the joystickX and joystickY variables
  


  joystickX = joystickXin;
  joystickY = joystickYin;
}




