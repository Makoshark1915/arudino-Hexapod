#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial(8, 9); // RX | TX

int BTserialprev = 0; // Variable to store the previous value read from BTserial
int BTserialcurrent = 0; // Variable to store the current value read from BTserial
int state = 1;

bool error = false; // Variable to track if a communication error has occurred

void setup() {
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW); // Turn LED OFF
    BTserial.begin(38400);
}

void loop() {
    
  if(Serial.available() > 4 && !error) {   
        // Assigns the 5 bytes transmitted from Bluetooth per frame to variables.
        int checkbyte = Serial.read(); // Checkbyte is always 255.
        int r = Serial.read(); // Radius of the joystick touch. Ranges from 0 - 251. 126 is added to r if theta is larger than 180.
        int checkr = Serial.read(); // Sums with r to make 252.
        int theta = Serial.read(); // Theta of the joystick touch. Ranges from 0 - 180. 180 is subtracted from theta if theta is larger than 180.
        int checktheta = Serial.read(); // Sums with theta to make 252.
        
        if (!(checkbyte == 255 && checkr + r == 252 && checktheta + theta == 252)) { // Communication error checking
        error = true;
        } else if (r > 125) {
            r = r - 126;  // reverts r to its displayed value on the app
            theta = theta + 180; // reverts theta to its displayed value on the app
        }
    }





    
}