#pragma once


#include "Arduino.h"
#include "SPI.h"

class ADXL357 {
  public:
    byte begin(byte pin_cs, int32_t cals[6]);
    void read_measurement();
    float x_g;
    float y_g;
    float z_g;
  private:
    byte cs;
    uint32_t read_reg(byte address, uint8_t num_bytes);
    uint32_t write_reg(byte addres, byte data);
    uint32_t spi_speed;
    int32_t calibrations[6];
};
