#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm0 = Adafruit_PWMServoDriver(0x40, Wire);// main servo board use for sg90's
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDriver(0x41, Wire);// secondary servo board use for misc black servo's


#define sg90Min 150 // This is the 'minimum' pulse length count of sg90's (out of 4096)
#define sg90Max 600 // This is the 'maximum' pulse length count of sg90's (out of 4096)

#define miscMin 150 // This is the 'minimum' pulse length count of misc black servos (out of 4096)
#define miscMax 600 // This is the 'maximum' pulse length count of misc black servos (out of 4096)

#define oscilatorFreq 27000000 // change this value between 23-27MHz to properly calibrate it


void setup() {

Serial.begin(9600);
Serial.println("Servo Test");


pwm0.begin();
pwm0.setPWMFreq(50); 

pwm1.begin();
pwm1.setPWMFreq(50);


pwm0.setOscillatorFrequency(oscilatorFreq);
pwm1.setOscillatorFrequency(oscilatorFreq);


  
}

void loop() {
  // sets all sg90's (board 1) and misc black servo's (board 2) to their minimum and maximum values with 1 second delay in between

  pwm0.setPWM(0, 0, angle0(0));
  pwm0.setPWM(1, 0, angle0(0));
  pwm0.setPWM(2, 0, angle0(0));
  pwm0.setPWM(3, 0, angle0(0));
  pwm0.setPWM(4, 0, angle0(0));
  pwm0.setPWM(5, 0, angle0(0));
  pwm0.setPWM(6, 0, angle0(0));
  pwm0.setPWM(7, 0, angle0(0));
  pwm0.setPWM(8, 0, angle0(0));
  pwm0.setPWM(9, 0, angle0(0));
  pwm0.setPWM(10, 0, angle0(0));
  pwm0.setPWM(11, 0, angle0(0));


  pwm1.setPWM(0, 0, angle1(0));
  pwm1.setPWM(1, 0, angle1(0));
  pwm1.setPWM(2, 0, angle1(0));
  pwm1.setPWM(3, 0, angle1(0));
  pwm1.setPWM(4, 0, angle1(0));
  pwm1.setPWM(5, 0, angle1(0));
  delay(1000);


  pwm0.setPWM(0, 0, angle0(180));
  pwm0.setPWM(1, 0, angle0(180));
  pwm0.setPWM(2, 0, angle0(180));
  pwm0.setPWM(3, 0, angle0(180));
  pwm0.setPWM(4, 0, angle0(180));
  pwm0.setPWM(5, 0, angle0(180));
  pwm0.setPWM(6, 0, angle0(180));
  pwm0.setPWM(7, 0, angle0(180));
  pwm0.setPWM(8, 0, angle0(180));
  pwm0.setPWM(9, 0, angle0(180));
  pwm0.setPWM(10, 0, angle0(180));
  pwm0.setPWM(11, 0, angle0(180));

  pwm1.setPWM(0, 0, angle1(180));
  pwm1.setPWM(1, 0, angle1(180));
  pwm1.setPWM(2, 0, angle1(180));
  pwm1.setPWM(3, 0, angle1(180));
  pwm1.setPWM(4, 0, angle1(180));
  pwm1.setPWM(5, 0, angle1(180));
  delay(1000);

  




}

static int angle0(int tarAngle) {

tarAngle = round(map(tarAngle, 0, 180, sg90Min, sg90Max));

return tarAngle;
}
static int angle1(int tarAngle) {

tarAngle = round(map(tarAngle, 0, 180, miscMin, miscMax));
return tarAngle;
}

