#include <Arduino.h>

#include <SoftwareSerial.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define pi 3.14159

SoftwareSerial BTserial(8, 9); //rx tx

const float defaultX = 132.95f; // default x value for the legs
const float defaultY = 80.0f; // default y value for the legs
float standingHeight = 90.0f; // current standing height (90 by default)

const float segment1 = 47.6f; // length of the first segment of the leg (2nd rotate pot to body)
const float segment2 = 85.35f; // length of the second segment of the leg (end point to 2nd rotate pot)

pwm0.begin();
pwm0.setPWMFreq(50); 

pwm1.begin();
pwm1.setPWMFreq(50);


pwm0.setOscillatorFrequency(27000000);
pwm1.setOscillatorFrequency(27000000);

#define sg90Min 150 // This is the 'minimum' pulse length count of sg90's (out of 4096)
#define sg90Max 600 // This is the 'maximum' pulse length count of sg90's (out of 4096)

#define miscMin 150 // This is the 'minimum' pulse length count of misc black servos (out of 4096)
#define miscMax 600 // This is the 'maximum' pulse length count of misc black servos (out of 4096)

#define oscilatorFreq 27000000 // change this value between 23-27MHz to properly calibrate it


static int angle(int tarAngle) {

tarAngle = round(map(tarAngle, 0, 180, sg90Min, sg90Max));
}


class JoystickClass {

  public:
    int[] cords;

    void update() { // update the joystick coordinates by reading data from Bluetooth
      String data = "0,0,0"; // String for storing incoming data from Bluetooth

      if (BTserial.available()) { // Check if there is data available to read
          data = BTserial.readStringUntil('\n'); // Read the incoming data as a string until a newline character is encountered
          Serial.println(data); // Print the received data to the serial monitor for debugging purposes
      }
      

      // Parse the received data into x, y, and z values
      int firstCommaIndex = data.indexOf(','); // Find the index of the first comma
      int secondCommaIndex = data.indexOf(',', firstCommaIndex + 1); // Find the index of the second comma  
      int thirdCommaIndex = data.indexOf(',', secondCommaIndex + 1); // Find the index of the third comma

      cords[0] = data.substring(0, firstCommaIndex).toInt(); // Extract the x value and convert it to an integer
      cords[1] = data.substring(firstCommaIndex + 1, secondCommaIndex).toInt(); // Extract the y value and convert it to an integer
      cords[2] = data.substring(secondCommaIndex + 1, thirdCommaIndex).toInt(); // Extract the z value and convert it to an integer
   
    }

    boolean atRest() { // check if the joystick is at rest


      update(); // Call the update() method to update the joystick coordinates

      return (cords[0] == 0 && cords[1] == 0); // Return true if the joystick is at rest (x and y coordinates are both 0), otherwise return false
    }

    getX() { // get the x value of the joystick
      update(); // Call the update() method to update the joystick coordinates
      return cords[0]; // Return the x coordinate of the joystick
    }

    getY() { // get the y value of the joystick
      update(); // Call the update() method to update the joystick coordinates
      return cords[1]; // Return the y coordinate of the joystick
    }

    getZ() { // get the z value of the joystick
      update(); // Call the update() method to update the joystick coordinates
      return cords[2]; // Return the z coordinate of the joystick
    }
};

class legClass {
  public:
    legClass(boolean groupIn, int legNumberIn, float[] defaultCords) { // constructor for the legClass
      group = groupIn; // set the group of the leg (0 or 1)
      legNumber = legNumberIn; // set the number of the leg (0, 1, or 2)
      x = defaultCords[0]; // set the x coordinate of the leg
      y = defaultCords[1]; // set the y coordinate of the leg
      z = defaultCords[2]; // set the z coordinate of the leg

      curX = x; // set the current x coordinate of the leg
      curY = y; // set the current y coordinate of the leg
      curZ = z; // set the current z coordinate of the leg

      if(group == false){ // if the leg is in group 0, set the servo pins for the leg
        if(legNumber == 0){
          close = 0;
          mid = 0;
          far = 1;
          angle = pi/6;
        }
        else if(legNumber == 1){
          close = 1;
          mid = 2;
          far = 3;
          angle = 3*pi/2;
        }
        else if(legNumber == 2){
          close = 2;
          mid = 4;
          far = 5;
          angle = 5*pi/6;
        }
      }
      else{ // if the leg is in group 1, set the servo pins for the leg
        if(legNumber == 0){
          close = 3;
          mid = 6;
          far = 7;
          angle = 11*pi/6;
        }
        else if(legNumber == 1){
          close = 4;
          mid = 8;
          far = 9;
          angle = pi/2;
        }
        else if(legNumber == 2){
          close = 5;
          mid = 10;
          far = 11;
          angle = 7*pi/6;
        }
      }




    }

    boolean group; // group of the leg (0 or 1)
    boolean inRange; // check for wether or not the leg's cords are in range of the leg's movement (true if in range, false if out of range)
    int legNumber; // number of the leg (0, 1, or 2)
    double angle; // angle of the leg relative to the front of the robot (in radians)

    float x;
    float y;
    float z;

    float curX;
    float curY;
    float curZ;
    
    byte close;
    byte mid;
    byte far;

    float closeAngle;
    float midAngle;
    float farAngle;

    boolean state = false; // state of the leg (true for up, false for down)

    void stateChange(){ // used to change the state of the leg (up or down) and adjust the z coordinate accordingly

      if(state){
        z -= 10; // if the leg is up, lower it by 10 units
      }
      else{
        z += 10; // if the leg is down, raise it by 10 units
      }

      z = curZ; // set the z coordinate of the leg to the current z coordinate
      state = !state; // toggle the state of the leg
    }

    void updateCords(){ // update the current coordinates of the leg to move towards the target coordinates (x, y, z)
      float xdiff = x - curX;
      float ydiff = y - curY;
      float zdiff = z - curZ;

      if(xdiff > 0){

        curX += sq(xdiff)/100; // if the x coordinate is less than the current x coordinate, increase the current x coordinate by square of the difference divided by 100
      }
      else if(xdiff < 0){
        curX -= sq(xdiff)/100; // if the x coordinate is greater than the current x coordinate, decrease the current x coordinate by square of the difference divided by 100  
      }


      if(ydiff > 0){
        curY += sq(ydiff)/100; // if the y coordinate is less than the current y coordinate, increase the current y coordinate by square of the difference divided by 100
      }
      else if(ydiff < 0){
        curY -= sq(ydiff)/100; // if the y coordinate is greater than the current y coordinate, decrease the current y coordinate by square of the difference divided by 100  
      }

      if(zdiff > 0){
        curZ += sq(zdiff)/100; // if the z coordinate is less than the current z coordinate, increase the current z coordinate by square of the difference divided by 100
      }
      else if(zdiff < 0){
        curZ -= sq(zdiff)/100; // if the z coordinate is greater than the current z coordinate, decrease the current z coordinate by square of the difference divided by 100  
      }

    }
  
    void updatePos(){ // update the servo positions based on the current coordinates of the leg
      
      double prevX = curX;
      double prevY = curY;

      updateCords(); // update the current coordinates of the leg to move towards the target coordinates (x, y, z)

      double relX = curX*cos(angle) - curY*sin(angle);
      double relY = curX*sin(angle) + curY*cos(angle);
  
      float angleA = (atan2(z,R) * 180 / PI);


      float angle1 = atan2(relY, relX) * 180 / PI; // calculate the angle for the close servo based on the current coordinates of the leg

      double R = sqrt(relX*relX + relY*relY); // calculate the target radius from the origin to the current coordinates of the leg

      float angle2 = (acos((segment1*segment1 + R*R - segment2*segment2) / (2*segment1*R)) * 180 / PI); // calculate the angle for the mid servo based on the current coordinates of the leg
      float angle3 = (acos((segment2*segment2 + segment1*segment1 - R*R) / (2*segment2*segment1)) * 180 / PI); // calculate the angle for the far servo based on the current coordinates of the leg


      angle2 -= angleA;
      angle2 = 90 - angle2;
      angle3 -= 90;

      if (angle1.constrain() != angle1 || angle2.constrain() != angle2 || angle3.constrain() != angle3) { // check if any of the angles are out of range
        inRange = false; // if any of the angles are out of range, set inRange to false

        curX = prevX; // if any of the angles are out of range, reset the current coordinates of the leg to the previous coordinates
        curY = prevY;
      }
      else {
        inRange = true; // if all of the angles are in range, set inRange to true

        closeAngle = angle1; // if all of the angles are in range, set the servo angles to the calculated angles
        midAngle = angle2;
        farAngle = angle3;

        applyServos();

    }
  
  
  
  
  
  
  
  }

    void applyServos(){ // apply the servo angles to the servos

      pwm1.setPWM(close, 0, (angle0(closeAngle)));// all the close servos are on the second pca9685 board (pwm1)
      pwm0.setPWM(mid, 0, (angle0(midAngle)));
      pwm0.setPWM(far, 0, (angle0(farAngle)));
    }
  
  
  
  }


JoystickClass joystick; // create an instance of the JoystickClass

legClass leg0_0(false, 0, {defaultX, defaultY, standingHeight}); // create an instance of the legClass for leg 0-0
legClass leg0_1(false, 1, {defaultX, defaultY, standingHeight}); // create an instance of the legClass for leg 0-1
legClass leg0_2(false, 2, {defaultX, defaultY, standingHeight}); // create an instance of the legClass for leg 0-2

legClass leg1_0(true, 0, {defaultX, defaultY, standingHeight}); // create an instance of the legClass for leg 1-0
legClass leg1_1(true, 1, {defaultX, defaultY, standingHeight}); // create an instance of the legClass for leg 1-1
legClass leg1_2(true, 2, {defaultX, defaultY, standingHeight}); // create an instance of the legClass for leg 1-2



/* leg setup

      front
    0-0   1-0   

  1-1       0-1

    0-2   1-2
       back

*/

void setup() {
  Serial.begin(9600);
  BTserial.begin(38400); // Required for Bluetooth communication

  Serial.println("bluetooth comm initialized");

  while(!BTserial.available()){
      Serial.println("waiting for bluetooth connection");
  }
  
}

void loop() {

  if(joystick.atRest()){ // if the joystick is at rest go to default or else, start moving
    reCenter(); // if the joystick is at rest, run the code to re-center the legs to the default position
  }

  else{

    if(movelegs()){ // if the joystick is not at rest, run the code to move the legs based on the joystick coordinates
      stateChange(); // if any of the legs are out of range, run the code to change the state of the legs (up or down)
    }

  }
  

}

void reCenter() { // run re-center the legs to the default position
  leg0_0.x = defaultX;
  leg0_0.y = defaultY;

  leg0_1.x = defaultX;
  leg0_1.y = defaultY;

  leg0_2.x = defaultX;
  leg0_2.y = defaultY;


  leg1_0.x = defaultX;  
  leg1_0.y = defaultY;

  leg1_1.x = defaultX;
  leg1_1.y = defaultY;

  leg1_2.x = defaultX;
  leg1_2.y = defaultY;

}

boolean moveLegs() { // move the legs based on the joystick coordinates
  float x = joystick.getX();
  float y = joystick.getY();
  float z = joystick.getZ();

  boolean outOfRange = false; // boolean to return if any of the legs are out of range

  if(leg0_0.state){
    leg0_0.x -= x;
    leg0_0.y -= y;
    leg0_0.z = z;
    leg0_0.updatePos();



    leg0_1.x -= x;
    leg0_1.y -= y;
    leg0_1.z = z;
    leg0_1.updatePos();

    leg0_2.x -= x;
    leg0_2.y -= y;
    leg0_2.z = z;
    leg0_2.updatePos();

    leg1_0.x += x;
    leg1_0.y += y;
    leg1_0.z = z;
    leg1_0.updatePos();

    leg1_1.x += x;
    leg1_1.y += y;
    leg1_1.z = z;
    leg1_1.updatePos();

    leg1_2.x += x;
    leg1_2.y += y;
    leg1_2.z = z;
    leg1_2.updatePos();
  }
  else{
    leg0_0.x += x;
    leg0_0.y += y;
    leg0_0.z = z;
    leg0_0.updatePos();

    leg0_1.x += x;
    leg0_1.y += y;
    leg0_1.z = z;
    leg0_1.updatePos();

    leg0_2.x += x;
    leg0_2.y += y;
    leg0_2.z = z;
    leg0_2.updatePos();

    leg1_0.x -= x;
    leg1_0.y -= y;
    leg1_0.z = z;
    leg1_0.updatePos();

    leg1_1.x -= x;
    leg1_1.y -= y;
    leg1_1.z = z;
    leg1_1.updatePos();

    leg1_2.x -= x;
    leg1_2.y -= y;
    leg1_2.z = z;
    leg1_2.updatePos();
  }
  

    if(!leg0_0.inRange || !leg0_1.inRange || !leg0_2.inRange || !leg1_0.inRange || !leg1_1.inRange || !leg1_2.inRange){
      outOfRange = true;// if any of the legs are out of range, set outOfRange to true
    }









}

void stateChange() {

  leg0_0.stateChange();
  leg0_1.stateChange();
  leg0_2.stateChange();
  leg1_0.stateChange();
  leg1_1.stateChange();
  leg1_2.stateChange();

}