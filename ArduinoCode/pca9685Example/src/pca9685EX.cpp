//Sunfounder PCA9685 servo driver
//Arduino
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm;
#define NUM_SERVOS 5
#define SERVO_MIN 100
#define SERVO_MAX 600
#define SERVO_DELAY 1000 // Delay in milliseconds
int servoPins[NUM_SERVOS] = {0, 1, 2, 3};
void setup() {
Serial.begin(9600);
Serial.println("Alternate Servo Test");
pwm.begin();
pwm.setPWMFreq(50); // Set the PWM frequency for the PCA9685
// Initialize all servos to their minimum positions during setup
for (int i = 0; i < NUM_SERVOS; i++) {
pwm.setPWM(servoPins[i], 0, SERVO_MIN);
}
}
void loop() {
// Rotate all servos to one extreme position
for (int pos = SERVO_MIN; pos <= SERVO_MAX; pos += 1) {
for (int i = 0; i < NUM_SERVOS; i++) {
pwm.setPWM(servoPins[i], 0, pos);
}
delay(15);
}
delay(SERVO_DELAY);
// Rotate all servos back to their minimum position
for (int pos = SERVO_MAX; pos >= SERVO_MIN; pos -= 1) {
for (int i = 0; i < NUM_SERVOS; i++) {
pwm.setPWM(servoPins[i], 0, pos);
}
delay(15);
}
delay(SERVO_DELAY);
}