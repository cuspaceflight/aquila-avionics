#pragma once

#include "Arduino.h"
#include "SPI.h"
#include "adxl357.h"
#include "ms5607_02ba03.h"

#define pin_accel_cs 2
#define pin_accel_drdy 30

#define pin_baro_ext_cs 4


class AQUILA {
  public:
    void begin();
    void update_accel();
    float get_accel_x();
    float get_accel_y();
    float get_accel_z();

    bool poll_baro_ext();
    float get_ext_pressure();
    float get_ext_temperature();
  private:
    ADXL357 accel;
    MS5607 baro_ext;
};
