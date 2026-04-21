#include <Arduino.h>

#include <SoftwareSerial.h>

boolean error = false; // Boolean for keeping track of communication errors

SoftwareSerial BTserial(8, 9); //rx tx

String data = "0,0,0"; // String for storing incoming data from Bluetooth
int x;
int y;
int z;
void setup() {
  BTserial.begin(38400); // Required for Bluetooth communication
  Serial.begin(9600); // Required for serial communication with the computer
}

void loop() {  

  if (BTserial.available()) { // Check if there is data available to read
    
    
      data = BTserial.readStringUntil('\n'); // Read the incoming data as a string until a newline character is encountered
      //Serial.println(data); // Print the received data to the serial monitor for debugging purposes
  }
  

  // Parse the received data into x, y, and z values
  int firstCommaIndex = data.indexOf(','); // Find the index of the first comma
  int secondCommaIndex = data.indexOf(',', firstCommaIndex + 1); // Find the index of the second comma  
  int thirdCommaIndex = data.indexOf(',', secondCommaIndex + 1); // Find the index of the third comma

  x = data.substring(0, firstCommaIndex).toInt(); // Extract the x value and convert it to an integer
  y = data.substring(firstCommaIndex + 1, secondCommaIndex).toInt(); // Extract the y value and convert it to an integer
  z = data.substring(secondCommaIndex + 1, thirdCommaIndex).toInt(); // Extract the z value and convert it to an integer

  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.println(z);





  


  if (x==0 && y==0) {
    // centered
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }else if (x > 0 && y >= 0) {
    // top right quad
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  } else if (x < 0 && y >= 0) {
    // top left quad
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  } else if (x >= 0 && y <= 0) {
    // bottom right quad
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5,HIGH);
    digitalWrite(6, LOW);
  } else if (x <= 0 && y <= 0) {
    // bottom left quad
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  }
  else{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
  }





}