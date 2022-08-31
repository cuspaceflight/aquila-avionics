#include "Wire.h"

#define mpu6050_addr 0x68
#define reg_who_am_i 0x75

void setup() {
    Serial.begin(9600);
    Wire.begin();
    Wire.beginTransmission(mpu6050_addr);
    Wire.write(reg_who_am_i);
    Wire.endTransmission(false);
    Wire.requestFrom(mpu6050_addr, 1, true);
    //Serial.println(Wire.read(), BIN);

    
}

void loop() {
    Wire.beginTransmission(mpu6050_addr);
    Wire.write(0x41);
    Wire.endTransmission();
    Wire.requestFrom(mpu6050_addr, 2, true);
    int16_t temp_reading = (Wire.read() << 8) | Wire.read();
    float temp = temp_reading/340.0 + 36.53;
    //Serial.print(temp);

    //Serial.print(", ");

    Wire.beginTransmission(mpu6050_addr);
    Wire.write(0x75);
    Wire.endTransmission();
    Wire.requestFrom(mpu6050_addr, 6, true);
    int16_t accel_x_reading = (Wire.read() << 8) | Wire.read();
    int16_t accel_y_reading = (Wire.read() << 8) | Wire.read();
    int16_t accel_Z_reading = (Wire.read() << 8) | Wire.read();

    Serial.print(accel_x_reading/16384.0 * 8);
    Serial.print(", ");
    Serial.print(accel_y_reading/16384.0 * 8);
    Serial.print(", ");
    Serial.print(accel_Z_reading/16384.0 * 8);
    Serial.println();
}