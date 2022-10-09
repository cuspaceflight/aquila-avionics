/* Daniel Fearn
 *  31/08/22
 *  
 *  This class communicates with an MPU6050 Inertial Measurement Unit on the I2C bus
 *  The accelerometers and gyroscopes are locked into their highest range settings
 *  No calibration data is included yet until I figure out the best place to store it
 */

// https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Register-Map1.pdf

#include "mpu6050.h"

byte MPU6050::begin() {
    // reset / wakeup
    write_reg(0x6B, 0);
    delay(100);

    // +/- 16g mode
    write_reg(0x1C, 3<<3);
    // +/- 2000deg/s mode
    write_reg(0x1B, 3<<3);

    return read_reg(0x75, 1);
}

void MPU6050::read() {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B);
    Wire.endTransmission();
    Wire.requestFrom(MPU6050_ADDR, 6, true);

    int16_t accel_x_reading = (Wire.read() << 8) | Wire.read();
    int16_t accel_y_reading = (Wire.read() << 8) | Wire.read();
    int16_t accel_z_reading = (Wire.read() << 8) | Wire.read();

    // scale for +/- 16g
    accel_x = accel_x_reading / 2048.0;
    accel_y = accel_y_reading / 2048.0;
    accel_z = accel_z_reading / 2048.0;

    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x43);
    Wire.endTransmission();
    Wire.requestFrom(MPU6050_ADDR, 6, true);

    int16_t gyro_x_reading = (Wire.read() << 8) | Wire.read();
    int16_t gyro_y_reading = (Wire.read() << 8) | Wire.read();
    int16_t gyro_z_reading = (Wire.read() << 8) | Wire.read();

    // scale for +/- 2000deg/s
    gyro_x = gyro_x_reading / 16.4;
    gyro_y = gyro_y_reading / 16.4;
    gyro_z = gyro_z_reading / 16.4;
}

uint32_t MPU6050::read_reg(byte address, uint8_t num_bytes) {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(address);
    Wire.endTransmission();
    Wire.requestFrom(MPU6050_ADDR, num_bytes, true);

    uint32_t reading = Wire.read();
    num_bytes--;
    while (num_bytes > 0) {
        reading = (reading << 8) | Wire.read();
        num_bytes--;
    }
    return reading;
}

uint32_t MPU6050::write_reg(byte address, byte data) {
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(address);
    Wire.write(data);
    Wire.endTransmission();
}