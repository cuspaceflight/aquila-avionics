#pragma once

#define accel_x_sens 12480
#define accel_x_offset 50
#define accel_y_sens 12610
#define accel_y_offset 120
#define accel_z_sens 12144
#define accel_z_offset 1244

#include "Arduino.h"
#include "SPI.h"

class ADXL357 {
  public:
    byte begin(byte pin_cs);
    void read_measurement();
    float x_g;
    float y_g;
    float z_g;
  private:
    byte cs;
    uint32_t read_reg(byte address, uint8_t num_bytes);
    uint32_t write_reg(byte addres, byte data);
    uint32_t spi_speed;
};
