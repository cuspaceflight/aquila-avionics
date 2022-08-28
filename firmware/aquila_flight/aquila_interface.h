#pragma once

#include "Arduino.h"
#include "SPI.h"
#include "rtc.h"
#include "adxl357.h"
#include "ms56_11_07.h"

#define pin_accel_cs 2
#define pin_accel_drdy 30

#define pin_baro_cs 3
#define pin_baro_ext_cs 4


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
  private:
    TEENSY_RTC rtc;
    ADXL357 accel;
    MS56_11_07 baro_ext;
    MS56_11_07 baro;
};
