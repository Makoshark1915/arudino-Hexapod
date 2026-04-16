#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm;





void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial.println("Alternate Servo Test");
pwm.begin();
pwm.setPWMFreq(50); // Set the PWM frequency for the PCA9685
// Initialize all servos to their minimum positions during setup



  
}

void loop() {
  // put your main code here, to run repeatedly:

  pwm.setPWM(0, 0, 100);
  delay(1000);
  pwm.setPWM(0, 0, 600);
  delay(1000);

}

