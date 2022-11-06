#pragma once

#define MPU6050_ADDR 0x68

#include "Arduino.h"
#include "Wire.h"


class MPU6050 {
    public:
        byte begin(int32_t cals[9]);
        void read();
        void read_gyro();
        float accel_x;
        float accel_y;
        float accel_z;
        float gyro_x;
        float gyro_y;
        float gyro_z;
    private:
        uint32_t read_reg(byte address, uint8_t num_bytes);
        void write_reg(byte address, byte data);
        int32_t calibrations[9];
};