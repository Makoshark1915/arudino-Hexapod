#include <Arduino.h>

#include <SoftwareSerial.h>

boolean error = false; // Boolean for keeping track of communication errors

SoftwareSerial BTserial(1, 0); //rx tx

String data = ""; // String for storing incoming data from Bluetooth
String inbetString;
int x;
int y;
void setup() {
  BTserial.begin(9600); // Required for Bluetooth communication
}

void loop() {  

  if (BTserial.available() > 0 && !error) { // Check if there is data available to read
    
    
      data = BTserial.read(); // Add the read character to the data string

 
    }
    
  data.trim(); // Remove any leading or trailing whitespace from the data string

  inbetString = data.substring(0, data.indexOf(" ")); // Extract the x value from the data string

  x = inbetString.toInt(); // Convert the x value from a string to an integer
    
  inbetString = data.substring(data.indexOf(" ") + 1); // Extract the y value from the data string

  y = inbetString.toInt(); // Convert the y value from a string to an integer

  data = ""; // Clear the data string for the next incoming data

  


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