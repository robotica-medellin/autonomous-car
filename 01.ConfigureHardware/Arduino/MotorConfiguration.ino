#include <Wire.h>
#include <ZumoMotors.h>

#define I2C_SLAVE_ADDRESS  0x03

ZumoMotors motors;

union {
  byte rawData[2];
  int16_t value;
} motorLeft, motorRight;

void setup() {
  // I2C Configuration
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  

// Init motor Speed
  motorLeft.value = 0;
  motorRight.value = 0;

// Motor flip configuration if its required
//  motors.flipRightMotor(true);
//  motors.flipLeftMotor(false);
}

void loop() {
  motors.setSpeeds(motorLeft.value, motorRight.value);
}

void receiveData(int byteCount) {
  // discard the first byte. For some reason we are getting and extra one
  Wire.read();

  motorLeft.rawData[0] = Wire.read();
  motorLeft.rawData[1] = Wire.read();
  motorRight.rawData[0] = Wire.read();
  motorRight.rawData[1] = Wire.read();
}
