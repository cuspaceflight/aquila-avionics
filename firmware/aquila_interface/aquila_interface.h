#pragma once

#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Servo.h"
#include "rtc.h"
#include "adxl357.h"
#include "ms56_11_07.h"
#include "mpu6050.h"
#include "rfm95w.h"

//#define abs(a) ((a < 0) ? -a : a)

#define accel_x_sens 12541
#define accel_x_offset 71
#define accel_y_sens 12625
#define accel_y_offset 164
#define accel_z_sens 12154
#define accel_z_offset 1259

#define imu_ax_sens 2046
#define imu_ax_offset 148
#define imu_ay_sens 2048
#define imu_ay_offset -32
#define imu_az_sens 2100
#define imu_az_offset -52

#define imu_gx_offset -51
#define imu_gy_offset -22
#define imu_gz_offset 2

#define pin_accel_cs 2
#define pin_accel_drdy 30

#define pin_baro_cs 3
#define pin_baro_ext_cs 4

#define pin_batt_v 24

#define pin_pyro_arm 6
#define pin_pyro_cont1 41
#define pin_pyro1 40
#define pin_pyro_cont2 39
#define pin_pyro2 38
#define pin_pyro_cont3 37
#define pin_pyro3 36
#define pin_pyro_cont4 35
#define pin_pyro4 34

#define pin_servo1 9
#define pin_servo2 8
#define pin_servo3 7
#define pin_servo4 10

class AQUILA {
  public:
    void begin();

    void rtc_datetime(char* outstr);
    uint32_t rtc_unix();

    void update_accel();
    float get_accel_x();
    float get_accel_y();
    float get_accel_z();

    bool poll_baro_ext();
    float get_ext_pressure();
    float get_ext_temperature();

    bool poll_baro_int();
    float get_int_pressure();
    float get_int_temperature();

    void update_imu();
    float get_imu_accel_x();
    float get_imu_accel_y();
    float get_imu_accel_z();
    float get_imu_gyro_x();
    float get_imu_gyro_y();
    float get_imu_gyro_z();

    float get_batt_voltage();

    void arm_pyro();
    void disarm_pyro();
    bool pyro_is_armed();
    bool pyro_continuity(uint8_t pyro_number);
    bool fire_pyro(uint8_t pyro_number);

    void move_all_servos(uint8_t angle);

    void transmit_telem(uint8_t size, char* data);
    void start_listening();
    void receive_telec(char* cmd);

  private:
    TEENSY_RTC rtc;
    ADXL357 accel;
    MS56_11_07 baro_ext;
    MS56_11_07 baro;
    MPU6050 imu;
    RFM95W radio;
    Servo sv1;
    Servo sv2;
    Servo sv3;
    Servo sv4;

    bool pyro_armed;
};
