#include <Arduino.h>
#include <SoftwareSerial.h>

boolean error = false; // Boolean for keeping track of communication errors

SoftwareSerial BTserial(8, 9); //rx tx

String data = ""; // String for storing incoming data from Bluetooth
String inbetString;
int x =0;
int y =0;
void setup() {
  BTserial.begin(9600); // Required for Bluetooth communication
}

void loop() {  


  
  if (BTserial.available() > 3 && !error) { // Check if there is data available to read
    int Check = BTserial.read();
    x = BTserial.read();
    y = BTserial.read();


    }
    
  
    Serial.println(x);
    
/*
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


*/

  if (BTserial.available() > 0 && error) { // Dump Serial bytes until 255 is seen, indicating the start of the next Bluetooth frame.
    if (BTserial.peek() != 255) {
      BTserial.read();
    } else {
      error = false;
    }
  }
}