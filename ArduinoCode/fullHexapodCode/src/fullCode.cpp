#include <Arduino.h>

#include <SoftwareSerial.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>



SoftwareSerial BTserial(8, 9); //rx tx

const float defaultX = 132.95f; // default x value for the legs
const float defaultY = 80.0f; // default y value for the legs
float standingHeight = 90.0f; // current standing height (90 by default)



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
        }
        else if(legNumber == 1){
          close = 1;
          mid = 2;
          far = 3;
        }
        else if(legNumber == 2){
          close = 2;
          mid = 4;
          far = 5;
        }
      }
      else{ // if the leg is in group 1, set the servo pins for the leg
        if(legNumber == 0){
          close = 3;
          mid = 6;
          far = 7;
        }
        else if(legNumber == 1){
          close = 4;
          mid = 8;
          far = 9;
        }
        else if(legNumber == 2){
          close = 5;
          mid = 10;
          far = 11;
        }
      }




    }

    boolean group; // group of the leg (0 or 1)
    int legNumber; // number of the leg (0, 1, or 2)

    float x;
    float y;
    float z;

    float curX;
    float curY;
    float curZ;
    
    byte close;
    byte mid;
    byte far;

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
  
    void updateServos(){ // update the servo positions based on the current coordinates of the leg




      
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
    moving(joystick.getX(), joystick.getY(), joystick.getZ());// the code to move the legs according to the joystick x,y,z
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



