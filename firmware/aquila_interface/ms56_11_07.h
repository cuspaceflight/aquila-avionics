#pragma once

#include "Arduino.h"
#include "SPI.h"

enum MS56_type {
  MS5611,
  MS5607
};

class MS56_11_07 {
  public:
    uint32_t begin(byte pin_cs, MS56_type sensor_type);
    bool poll_measurement();
    int32_t pressure;
    int32_t temperature;
  private:
    byte cs;
    MS56_type type;
    float c[7];
    uint32_t D1;
    uint32_t D2;
    uint8_t measurement_stage;
    uint32_t wait_time;
    uint32_t read_reg(byte address, uint8_t num_bytes);
    uint32_t send_command(byte command);
    uint32_t spi_speed;
};
