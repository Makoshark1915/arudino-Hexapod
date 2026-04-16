#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial BTserial(8, 9); // RX | TX

int BTserialprev = 0; // Variable to store the previous value read from BTserial
int BTserialcurrent = 0; // Variable to store the current value read from BTserial
int state = 1;

void setup() {
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW); // Turn LED OFF
    BTserial.begin(38400);
}

void loop() {
    if(BTserial.available() > 0){
    BTserialcurrent = BTserial.read();
    }

    if(BTserialcurrent != BTserialprev) { // Check if the current value read from BTserial is different from the previous value
        state = BTserialcurrent - '0'; // Update the previous value with the current value read from BTserial
        BTserial.write(state); // Print the current state to the Serial Monitor
    }
    

    if (state == 0) {
        digitalWrite(2, LOW); // Turn LED OFF
        
    }
    else if (state == 1) {
        digitalWrite(2, HIGH);
        
    }
    
    
    BTserialprev = BTserialcurrent;
}